#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define INT_SHM_KEY 4444
#define STR_SHM_KEY 5555
#define STR_MAX_LEN 100

int main(){
    // Create integer shared memory segment and attach segment to data space 
    int intshm = shmget(INT_SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if(intshm < 0){
        perror("shmget1");
        exit(1); 
    }
    int *intptr = shmat(intshm, NULL, 0);
    if(intptr == (int*)-1){
        perror("shmat1");
        exit(1); 
    }

    // Create string shared memory segment and attach segment to data space
    int strshm = shmget(STR_SHM_KEY, STR_MAX_LEN, IPC_CREAT | 0666);
    if(strshm < 0){
        perror("shmget2");
        exit(1);
    }
    char *strptr = shmat(strshm, NULL, 0);
    if(strptr == (char*)-1){
        perror("shmat2");
        exit(1);
    }
    // Write 10 to integer shared memory and write string to shared memory segment
    *intptr = 10; 
    sprintf(strptr, "I am Process A");
    printf("%s\n", strptr);

    // Poll until B is complete and print once it is
    while(*intptr != 20){
        sleep(1);
    }
    printf("%s\n", strptr);
    
    // Poll until C is complete and print once it is
    while(*intptr != 30){
        sleep(1);
    }
    printf("%s\n", strptr);
    
    // Detach and remove shared memory segments
    shmdt(intptr);
    shmdt(strptr);
    shmctl(intshm, IPC_RMID, NULL);
    shmctl(strshm, IPC_RMID, NULL);

    printf("Goodbye!\n");

    return 0; 
}