#include "mem-mgmt.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Heap start address: %p\n\n", sbrk(0));
    int** heap = malloc(1000 * sizeof(int));

    for(int i = 0; i < 10; i++){
        heap[i] = malloc(i+1 * sizeof(int));
        printf("Malloc'ed %d at %p\n", i, sbrk(0));
    }
    printf("Heap end address after malloc: %p\n", sbrk(0));

    printf("\nFreeing allocated memory\n\n");
    for(int i = 0; i < 10; i++){
        free(heap[i]);
    }

    for(int i = 0; i < 10; i++){
        heap[i] = calloc(10*i, sizeof(int));
        printf("Calloc'ed %d at %p\n", i, sbrk(0)); 
    }
    printf("Heap end address after calloc: %p\n\n", sbrk(0));

    for(int i = 0; i < 10; i++){
        realloc(heap[i], sizeof(int)); 
        printf("Reallocing value %d\n", i);
    }

    printf("\nFreeing allocated memory\n");
    for(int i = 0; i < 10; i++){
        free(heap[i]);
    } 
    
    free(heap);
    
    size_t bytes_lost = check_memory_leak();
    printf("\nTotal bytes lost: %d\n", bytes_lost);

    printf("\nHeap end address: %p\n", sbrk(0));
    return 0;
}