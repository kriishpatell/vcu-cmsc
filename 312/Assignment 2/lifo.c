#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <unistd.h>
#include <signal.h> 
#include <time.h>

#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SIZE 20
 
typedef struct PrintRequest {
    int job_id;
    int size;
    clock_t start, end;
} buffer_t;
buffer_t buffer[SIZE];

int global_buffer, shm_full, shm_empty, shm_mutex, shm_index; 
int *global_ptr; 

float totalWaitTime, averageWaitTime, totalExecutionTime = 0; 
int buffer_index = 0, num_job, totalNumJobs;
int producer_count, consumer_count;   
 
pthread_mutex_t *buffer_mutex;
sem_t *full_sem;  
sem_t *empty_sem; 
 
 void signal_handler(int signal){    
    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&full_sem);
    sem_destroy(&empty_sem);
    
    shmdt(&global_ptr);
    shmdt(&full_sem);
    shmdt(&empty_sem);
    shmdt(&buffer_mutex);
    shmdt(buffer_index);

    shmctl(shm_full, IPC_RMID, NULL);
    shmctl(shm_empty, IPC_RMID, NULL);
    shmctl(shm_mutex, IPC_RMID, NULL);
    shmctl(shm_index, IPC_RMID, NULL);
    shmctl(global_buffer, IPC_RMID, NULL);

    exit(0);
}
 
void insertbuffer(int value) {
    if (buffer_index < SIZE) {
        buffer[buffer_index++].start = clock();
        buffer[buffer_index].size = value;
    } else {
        printf("Buffer overflow\n");
    }
}
 
int dequeuebuffer() {
    if (buffer_index > 0) {
        buffer[buffer_index].end = clock();
        totalWaitTime += (double)(buffer[buffer_index].end - buffer[buffer_index].start) / CLOCKS_PER_SEC;
        --buffer_index;
        return buffer[buffer_index+1].size; 
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}
 
void *producer(int num_job) {
    int value;
    int i=0;
    srand(time(NULL));
    
    printf("Number of Jobs: %d\nTotal Number: %d\n", num_job, totalNumJobs);
    
    while (i++ < num_job) {
        usleep((rand() % 1000000) + 100000);
        value = rand() % 901 + 100;

        sem_wait(&full_sem); 

        pthread_mutex_lock(buffer_mutex); 
        insertbuffer(value);
        pthread_mutex_unlock(buffer_mutex);
        
        sem_post(&empty_sem); 
        printf("Producer %d added %d to buffer\n", getpid(), value);
    }
}
 
void *consumer(void *thread_n) {
    printf("abc\n");
    int thread_numb = *(int *)thread_n + 1;
    int value;
    int i=0;
    while (i++ < num_job) {
        sem_wait(&empty_sem); 

        pthread_mutex_lock(buffer_mutex);;
        value = dequeuebuffer(value);
        pthread_mutex_unlock(buffer_mutex);

        sem_post(&full_sem);
        printf("Consumer %d dequeue %d from buffer\n", thread_numb, value);
   }
    pthread_exit(0);
}
 
int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    clock_t start, end;
    start = clock();

    while (argc != 3) {
        fprintf(stderr, "Usage: ./<outfile> <producer_count> <consumer_count>\n");
        exit(1);
    }
    producer_count = atoi(argv[1]);
    consumer_count = atoi(argv[2]);
    
    pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&full_sem, 0, SIZE); 
    sem_init(&empty_sem, 0, 0);
    
    global_buffer = shmget(2345, sizeof(buffer_t) * SIZE, IPC_CREAT | 0666);
    global_ptr = (int*) shmat(global_buffer, NULL, 0);
    
    shm_full = shmget(2346, sizeof(sem_t), IPC_CREAT | 0666);
    full_sem = (sem_t*)shmat(shm_full, NULL, 0);

    shm_empty = shmget(2347, sizeof(sem_t), IPC_CREAT | 0666);
    empty_sem = (sem_t*)shmat(shm_empty, NULL, 0);

    shm_mutex = shmget(2348, sizeof(pthread_mutex_t), IPC_CREAT | 0666);
    buffer_mutex = (pthread_mutex_t*)shmat(shm_mutex, NULL, 0);
    
    pthread_t thread[consumer_count];
    int thread_numb[consumer_count];
    
    pid_t pids[producer_count];
    int i;

    for(i = 0; i < producer_count; i++){
        srand(time(NULL));
        num_job = rand() % 20 + 1; 
        totalNumJobs += num_job; 
        pids[i] = fork();
        if(pids[i] == 0){  
            producer(num_job);
            exit(0);
        }
        waitpid(pids[i]);
    } 
    
    sleep(5);
    for (i = 0; i < consumer_count; ) {
        thread_numb[i] = i;
        pthread_create(&thread[i],  NULL, consumer,  &thread_numb[i]);  
    }

    for (i = 0; i < consumer_count; i++){
        pthread_join(thread[i], NULL);
    }    

    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&full_sem);
    sem_destroy(&empty_sem);

    shmdt(&global_ptr);
    shmdt(&full_sem);
    shmdt(&empty_sem);
    shmdt(&buffer_mutex);
    shmdt(buffer_index);

    shmctl(shm_full, IPC_RMID, NULL);
    shmctl(shm_empty, IPC_RMID, NULL);
    shmctl(shm_mutex, IPC_RMID, NULL);
    shmctl(shm_index, IPC_RMID, NULL);
    shmctl(global_buffer, IPC_RMID, NULL);
    
    end = clock();

    totalExecutionTime = ((double)end - start)/CLOCKS_PER_SEC; 
    averageWaitTime = (totalWaitTime / totalNumJobs);

    printf("\nTotal execution time: %f\n", totalExecutionTime); 
    printf("Average waiting time: %f\n", averageWaitTime);

    printf("Total jobs: %.0f\n", totalNumJobs);

    return 0;
}