#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])

{
    printf("My current process ID is %d\n", getpid());
    printf("My parent process ID is %d\n", getppid());
		return 0;
}
