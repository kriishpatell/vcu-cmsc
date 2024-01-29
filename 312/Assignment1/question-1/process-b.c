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
    int intshm = shmget(INT_SHM_KEY, sizeof(int), 0666);
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
    int strshm = shmget(STR_SHM_KEY, STR_MAX_LEN, 0666);
    if(strshm < 0){
        perror("shmget2");
        exit(1);
    }
    char *strptr = shmat(strshm, NULL, 0);
    if(strptr == (char*)-1){
        perror("shmat2");
        exit(1);
    }
    
    // Continue to loop while intptr 10 and update it to indicate process B is complete
    while(*intptr == 10){
        sprintf(strptr, "I am Process B");
        *intptr = 20; 
    }

    shmdt(intptr);
    shmdt(strptr);

    return 0; 
}