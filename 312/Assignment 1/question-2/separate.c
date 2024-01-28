#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

    *intptr = 10; 
    sprintf(strptr, "I am Process A");
    printf("%s\n", strptr);

    pid_t pid_b = fork();
    if(pid_b < 0){
        perror("fork1");
        exit(1);
    } else if (pid_b == 0){
        sprintf(strptr, "I am process B");
        *intptr = 20; 
        exit(0);
    }
    waitpid(pid_b, NULL, 0);
    printf("%s\n", strptr);

    pid_t pid_c = fork();
    if(pid_c < 0){
        perror("fork2");
        exit(1);
    } else if (pid_c == 0){
        sprintf(strptr, "I am process C");
        *intptr = 30;
        exit(0); 
    }
    waitpid(pid_c, NULL, 0);
    printf("%s\n", strptr);

    shmdt(intptr);
    shmdt(strptr);
    shmctl(intshm, IPC_RMID, NULL);
    shmctl(intshm, IPC_RMID, NULL);

    printf("Goodbye!\n");

    return 0; 
}