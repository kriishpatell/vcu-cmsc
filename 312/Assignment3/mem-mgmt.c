#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void *nofree_malloc(size_t size) {
    void *p = sbrk(0);
    void *request = sbrk(size);
    
    if (request == (void *)-1) {
        return NULL;
    } else {
        assert(p == request);
    }
}

struct block_meta {
    size_t size;                // Size of allocated block
    struct block_meta *next;    // Pointer to next block in heap
    struct block_meta *prev;    // Pointer to prev block in heap
    int free;                   // Check if memory space is occupied
    int magic;                  // For debugging only. TODO: remove this in non-debug mode.
};

#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;

/* 
    Keep track of best fit block and if there is a free block that is smaller,
    then update best fit block to free block. After search through all blocks,
    return best fit block. Double while loop accommodates for doubly linked
    lists and is capable of traversing both directions 
*/
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
    struct block_meta *current = global_base;
    struct block_meta *best = NULL;
    
    // Traverse forward in list
    while(current){
        if(current->free && current->size >= size){
            if(!best || current->size < best->size){
                best = current;
            }
        }
        *last = current;
        current = current->next;
    }

    // Traverse backward in list
    current = *last; 
    while(current){
        if(current->free && current->size >= size){
            if(!best || current->size < best->size){
                best = current; 
            }
        }
        *last = current;
        current = current->prev; 
    }

    return best; 
}

/*  
    Request additional memory from operating system using sbrk() call to create
    a new block of memory for the heap. Initialize with block_meta struct and 
    assign values of block accordingly. 
*/
struct block_meta *request_space(struct block_meta *last, size_t size) {
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void*) block == request);

    if(request == (void*) -1){
        return NULL;
    }

    if(last){
        last->next = block;
    }

    block->size = size;
    block->prev = last;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;

    return block; 
}

/*
    Check if size is greater than requested size, if so split block into two. 
    Then update metadata of split block
*/ 
void split_block(struct block_meta *block, size_t size){
    if(block->size > size + META_SIZE){
        struct block_meta *new_block = (void*) (block + 1) + size;
        new_block->size = block->size - size - META_SIZE;
        new_block->next = block->next;
        new_block->prev = block;
        new_block->free = 1;
        new_block->magic = 0x12345678;

        block->size = size;
        block->next = new_block;

        if(new_block->next){
            new_block->next->prev = new_block; 
        } 
    }
}

void *malloc(size_t size) {
    struct block_meta *block;

    if (size <= 0) {
        return NULL;
    }

    if (!global_base) {
        block = request_space(NULL, size);
        
        if (!block) {
            return NULL;
        }

        global_base = block;
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);
        
        if (!block) {
            block = request_space(last, size);
            
            if (!block) {
                return NULL;
            }
        } else {
            block->free = 0;
            block->magic = 0x77777777;
            split_block(block, size);
        }
    }
    return (block + 1);
}

void *calloc(size_t nelem, size_t elsize) {
    size_t size = nelem * elsize;
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

struct block_meta *get_block_ptr(void *ptr) {
    return (struct block_meta *)ptr - 1;
}

/* 
    The function checks if the previous memory block in the heap is free. If it 
    is, the function merges the current memory block with the previous memory block 
    by updating the size and pointer fields in the metadata blocks.

    The function then checks if the next memory block in the heap is also free. 
    If it is, the function merges the current memory block with the next memory 
    block by updating the size and pointer fields in the metadata blocks.
 */
void free(void *ptr) {
    if (!ptr) {
        return;
    }

    struct block_meta *block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
    block_ptr->free = 1;
    block_ptr->magic = 0x55555555;

    struct block_meta *prev_block = block_ptr->prev;
    struct block_meta *next_block = block_ptr->next;

    // Merge with previous block if free
    if(prev_block && prev_block->free){
        prev_block->size += block_ptr->size + META_SIZE;
        prev_block->size = next_block;

        if(next_block){
            next_block->prev = prev_block;
        }
        block_ptr = prev_block;
    }

    // Merge with next block if free
    if(next_block && next_block->free){
        block_ptr->size += next_block->size + META_SIZE;
        block_ptr->next = next_block->next;

        if(next_block->next){
            next_block->next->prev = block_ptr; 
        }
    }
}

void *realloc(void *ptr, size_t size) {
    if (!ptr) {
        return malloc(size);
    }

    struct block_meta *block_ptr = get_block_ptr(ptr);
    
    if (block_ptr->size >= size) {
        return ptr;
    }

    void *new_ptr;
    new_ptr = malloc(size);
    
    if (!new_ptr) {
        return NULL; 
    }
    
    memcpy(new_ptr, ptr, block_ptr->size);
    free(ptr);
    return new_ptr;
}

size_t check_memory_leak() {
    size_t total_bytes_lost = 0;

    // Traverse the list of allocated memory blocks and sum their sizes
    struct block_meta *current = global_base;
    while (current) {
        if (current->free == 0) {
            total_bytes_lost += current->size;
        }
        current = current->next;
    }

    return total_bytes_lost;
}