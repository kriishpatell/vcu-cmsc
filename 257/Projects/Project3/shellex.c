#include "csapp.h"
#include <signal.h>
#define MAXARGS 128

char *user = "sh257"; 

// Function prototypes
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 
void signalHandler(int sig);

// Built-in command calls 
void helpCommand(); 
void cdCommand(char **argv); 
void pidCommand();
void ppidCommand();
void exitCommand(); 

// Create the shell and continuously loop through it until loop is interrupted
int main(int argc, char *argv[]){
    char cmdline[MAXLINE];  // Command line argument 

    // Checks if there is an argument when running program and prompts correct format
    if (argc == 2){
        printf("%s -p <prompt>\n", argv[0]);
        exit(0);
    }
    
    // Checks if first argument is '-p', stating the next argument is the user-defined prompt
    if (argc == 3){
        if (strcmp(argv[1], "-p")){
            printf("%s -p <prompt>\n", argv[0]);
            exit(0);
        }
        user = argv[2]; 
    }

    signal(SIGINT, signalHandler);  // Handles the CTRL+C interrupt

    // Loop for shell and evalute the command line after each argument is passed
    while (1) {
        printf("%s> ", user);                   
        Fgets(cmdline, MAXLINE, stdin); 
        if (feof(stdin)){
            exit(0);
        }
	    eval(cmdline);
    } 
}

// Evaulate the command line
void eval(char *cmdline){
    char *argv[MAXARGS];    // Argument list
    char buf[MAXLINE];      // Holds modified command line
    int bg, exitStatus = 0;     // Determines whether job should run in the foreground or background         
    pid_t pid;              // Process ID variable      
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    // Ignore empty line arguments
    if (argv[0] == NULL){
        return;
    }   

    // If argument is not a built-in command, check for system commands and return accordingly
    if (!builtin_command(argv)) { 
        // Child runs the user job
        if ((pid = Fork()) == 0) {   
            // If argument is not a system command, recognize unsuccessful process
            if (execvp(argv[0], argv) < 0) {
                printf("Execution failed. In fork()\n");
                printf("%s: Command not found\n", argv[0]); 
                exit(1);
            } 
        } 

        // Parent waits for foreground job to terminate
        if (!bg) {
            int status, exitStatus; 
            if (waitpid(pid, &status, 0) < 0){
                unix_error("waitfg: waitpid error");    
            }  
            
            // Determine the exit code when the child is terminated and return the value
            if(WIFEXITED(status)){
                exitStatus = WEXITSTATUS(status);
                printf("Process exited with status code %d\n", exitStatus); 
            }
            
	    } else {
            printf("%d %s", pid, cmdline);
        }
    } 
    return;
}

// If the argument provided is a built-in command, run it and return true
int builtin_command(char **argv){
    int commandCount = 5, switchArg = 0, i; 
    char* commandList[commandCount];

    // List of built-in commands
    commandList[0] = "exit";
    commandList[1] = "pid"; 
    commandList[2] = "ppid";
    commandList[3] = "cd";
    commandList[4] = "help"; 
    
    // Check if argument provided is equal to a built-in command and increment counter by 1 if true
    for(i = 0; i < commandCount; i++){
        if(strcmp(argv[0], commandList[i]) == 0){
            switchArg = i + 1;
            break; 
        }
    }

    // Switch cases for each built-in command 
    switch(switchArg){
        case 1 : // exit command
            exitCommand(); 
        
        case 2 : // pid command
            pidCommand(); 
            return 1;
        
        case 3 : // ppid command
            ppidCommand(); 
            return 1;
        
        case 4 : // cd command
            cdCommand(argv);
            return 1; 
        
        case 5 : // help command
            helpCommand();
            return 1; 
        
        default :
            break; 
    }
    return 0; 
}

// Parse the command line and build the argv array 
int parseline(char *buf, char **argv){
    char *delim;    // Points to the first space delimiter      
    int argc;       // Number of args     
    int bg;         // Background job?       

    buf[strlen(buf)-1] = ' ';   // Replace trailing '\n' with space          
   
    // Ignore leading spaces
    while (*buf && (*buf == ' ')){
        buf++;
    }
    
    // Build the argv list
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;

        // Ignore spaces
        while (*buf && (*buf == ' ')){
            buf++; 
        }     
    }

    argv[argc] = NULL;
    
    // Ignore blank line
    if (argc == 0){
        return 1;
    }

    // Check if the job should run in the background
    if ((bg = (*argv[argc-1] == '&')) != 0){
        argv[--argc] = NULL;
    }

    return bg;
}

// Function to handle CTRL+C interrupt 
void signalHandler(int sig){
    signal(SIGINT, signalHandler);
    fflush(stdout);
}

// Function displaying information about the custom shell
void helpCommand(){
    printf("**********************************************************************");
    printf("\nA Custom Shell for CMSC 257");
    printf("\n - %s", user);
    printf("\nUsage:");
    printf("\n - When running the program, use ./<program> -p <prompt> to change prompt");
    printf("\n**********************************************************************");

    puts("\n\nBUILTIN COMMANDS:"
         "\n - exit: exits the shell"
         "\n - pid: prints the process ID of the shell"
         "\n - ppid: prints the parent process ID of the shell"
         "\n - cd: prints current working directory; cd <path> changes current directory"
         "\n - help: prints usage information and displays developer name for shell"
         "\n\nSYSTEM COMMANDS:"
         "\n - refer to 'man' pages for system commands\n");
}

// Function that sends a signal to itself to terminate the program
void exitCommand(){
    int ret; 
    ret = raise(SIGTERM);
    if(ret != 0){
        printf("Unable to terminate program using raise system call.\n");
        exit(1); 
    }
}

// Function to display the process ID of the shell
void pidCommand(){
    printf("Shell process ID: %d\n", getpid()); 
}

// Function to display the parent process ID of the shell
void ppidCommand(){
    printf("Parent process ID: %d\n", getppid());
}

// Function to display current working directory or change current directory to passed argument
void cdCommand(char **argv){
    if(argv[1] == NULL){
        char currentDirectory[100]; 
        if(getcwd(currentDirectory, sizeof(currentDirectory)) != NULL){
            printf("Current directory: %s\n", currentDirectory); 
        } else {
            printf("Could not retreive current working directory"); 
        }
    } else if (argv[1] != NULL){
        chdir(argv[1]);
    }
}