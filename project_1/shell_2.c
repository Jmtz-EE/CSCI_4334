//Name(s): Jesus Martinez
//Date 10/02/26

/* SMP1: Simple Shell */

/* LIBRARY Section */
#include <ctype.h>              /* Character types                          */    
#include <stdio.h>              /* Standard buffered input/output           */
#include <stdlib.h>             /* Standard library functions               */
#include <string.h>             /* String Operations                        */
#include <sys/types.h>          /* Data types                               */
#include <sys/wait.h>           /* Declarations for waiting                 */
#include <unistd.h>             /* Standard symbolic constants and types    */ //My note: unisstd.h provides pid_t


#include "smp1_tests.h"         /* Built-in test system                     */


/* DEFINE SECTION */
#define SHELL_BUFFER_SIZE 256   /* Size of the Shell input buffer     */
#define SHELL_MAX_ARGS 8        /* Maximum number of arguments parsed */

/* VARIABLE SECTION */
enum {STATE_SPACE, STATE_NON_SPACE }; /* Parser states */
//parser states 0 1

int imthechild(const char *path_to_exec, char *const args[]) // My note: paremeter types set to use int execv(const char *path, char *const argv[])
{
    //TO-DO P5.1: Resolve PATH/relative/absolute command to an execv path
    //4 given conditions for command 
    /*
    1. includes an absolute path: /bin/ls
    2. start with a dot: ./shell
    3. the commnad is somewhere in the PATH: ls 
    4. The command does not exist 
    */

    // Hint: char *getenv(const char *name): searches for an environmental variable with name name 
    // returns a pointer to the satring that is associated with the matched environment variable 


    //Hint int access(const char *path, int mode)
    int has_slash = 0; 
    //.1
    for(int j = 0; path_to_exec[j] != '\0'; j++)
    {
        if( path_to_exec[j] == '/')
        {
            has_slash =1; 
            break; //found / in the path 
        }
    }
    //.2
    if (has_slash || path_to_exec[0] == '.')
    {
        execv(path_to_exec, args); 
        // execv() only returns when it fials to make the child         
        fprintf(stderr, "Command %s does not exist\n", path_to_exec);
        return EXIT_FAILURE; 
    }

    char *path = getenv("PATH"); 

    if (path == NULL)
    {
        fprintf()


    }








    return execv(path_to_exec, args) ? -1 : 0;  //My note: Ternary revisit
    /* int execv(const char *pathname, char *const argv[]) takes two inputs the path and the exe to run and an array of string arguments to pass to the new program*/
    // execv() replaces the calling process wiht the executable passed inheriting the pid


}

void imtheparent(pid_t child_pid, int run_in_background)
{
    int child_return_val, child_error_code;

    /* fork returned a positive pid so we are the parent */
    fprintf(stderr, 
            "   Parent says 'child process has been forked wiht pid=%d'\n", 
            child_pid); 
    if (run_in_background) {
        fprintf(stderr,
                " Parent says 'run_in_background=1 ... so we're not waiting for the child'\n");
        return; 
    }
    //TO-DO P5.5 
    //My comment: pid_t wait(int *status)
    //My comment: pid_t waitpid(pid_t pid, int *status, int options)
    wait(&child_return_val); 
    /* Use the WEXITSTATUS to extract the status code from the return value */
    child_error_code = WEXITSTATUS(child_return_val); 
    fprintf(stderr,
            "   Parent says 'wait() returned so the child with pid=%d is finished.'\n", 
             child_pid); 
    if (child_error_code != 0)
    {
    /* Error: Child process failed. Most likely a failed exec */
    fprinf(stderr, 
            " Parent says 'Child process %d failed with code %d\n",
            child_pid, child_error_code); 
    }
}

/* MAIN PROCEDURE SECTION */
int main(int argc, char **argv) //My note: why is argv ** double pointer
{//My note 
    //My note: pid_t data type that represents process IDs
    pid_t shell_pid, pid_from_fork;
    int n_read, i, exec_argc, parser_state, run_in_background;
    /* buffer: The Shell's input buffer */
    char buffer[SHELL_BUFFER_SIZE]; // My note: char bufferArray[256]
    /* execv_argv: Arguments passed to the exec call including NULL terminator. */
    char *exec_argv[SHELL_MAX_ARGS + 1]; //My note: Assuming + 1 is for NULL terminator
    //TO-DO new variables for P5.2, P5.3, P5.7

    /* Entrypoint for the testrunner program */
    if (argc > 1 && !strcmp(argv[1], "-test")){ //My note: 
        return run_smp1_tests(argc - 1, argv + 1); 
    }

    /* Allow the Shell prompt to display the pid of this process */
    shell_pid = getpid(); 
    
    while(1){
    /* The Shell runs in an infinite loop, processing input. */

        //TO-DO P5.2: Prompt must include pid and command counter. 
        fprintf(stdout, "Shell(pid=%d)> ", shell_pid); 
        fflush(stdout); //My note: int fflush(FILE* stream) was is the assoicated output device

        /* Read a line of input. */
        if(fgets(buffer, SHELL_BUFFER_SIZE, stdin) == NULL ) //My note: char* fgets(char* str, int count, FILE* stream) = str on success and = null pointer on failure
                return EXIT_SUCCESS; //My note: EXIT_SUCCESS/EXIT_FAILURE 
        //My note: So fgets fails return Exitsuccess ? why success -> means that no line was read so cant continue so exit 
        //but since the logic to catch it worked its a success 

        n_read = strlen(buffer); //My note: size_t strlen(const char* str) returns the length of the given null-terminated byte string
        run_in_background = n_read > 2 && buffer[n_read -2] == '&'; //My note: results in run_in_background = 0/1 
        //My note: n>2 checks if more than 2 chars and buff[n-2] check 0 1 & /n /0 => 4-2 = & true 
        buffer[n_read - run_in_background -1] = '\n'; 


        //TO-DO P5.3


        /* Parse the arguments: the first argument is the file or command
            we want to run                                                  */

        parser_state = STATE_SPACE; 
        //My note: declared int exec_argc 
        //buffer doesnt reach \n good
        for (exec_argc = 0, i = 0; 
            (buffer[i] != '\n') && (exec_argc < SHELL_MAX_ARGS); i++)
            {//My note: Enters loop with exec_argc = 0 
            
            if (!isspace(buffer[i])) //My note: int isspace(int ch) returns non-zero value if the character is a whitespace character, zero otherwise 
            {//My note: Enters if when non white space character
                if(parser_state == STATE_SPACE) // My note: What is the significance of the StateSpace
                    exec_argv[exec_argc++] = &buffer[i]; //My note: Commands are passed from buffer to the exec_argv[exec_argc /w post increment] 
                parser_state = STATE_NON_SPACE; // Paser State = 1 
            }
            else 
            {
                buffer[i] = '\0'; 
                parser_state = STATE_SPACE; //My note: still dont follow the significance of state space 
            }
         }
         /* run in_background is 1 if the input line's last character 
          * is an ampersand (indicating background execution).          */
         buffer[i] = '\0'; /* Terminate input, overwritting the '&' if it exists */

         /* if no command was given (empty line) the Shell just prints the prompt again */
         if (!exec_argc)
            continue; 
        /* Terminate the list of the exec parameters with NULL */
        exec_argv[exec_argc] = NULL; // My note: Why are we indexing wiht argc
        
        /* If Shell runs 'exit' it exits the program */
        if (!strcmp(exec_argv[0], "exit")) //My note: int strcmp(const char* lhs, const char* rhs) compares if lexographical order  
        {//strcmp (-)if lhs appears before rhs in lexicographical order (0) if lhs ==rhs (+) if lhs appears after rhs 
            printf("Exiting process %d\n", shell_pid);
            return EXIT_SUCCESS; /* End Shell program */
        }
        else if(!strcmp(exec_argv[0], "cd") && exec_argc > 1)
        {/* Running 'cd' changes the Shell's working directory */
            /* Alternatively: try chdir inside a forked child: if(fork() == 0 */
            if (chdir(exec_argv[1]))
                /* Error: change the directory failed */
                fprintf(stderr, "cd: failed to chdir %s\n", exec_argv[1]);
            /* End alternative: exit(EXIT_SUCCESS); */

        }
        //TO-DO P5.4
        else
        {/* Execute commands */
            /* Try replacing fork() with '0'. What happens? */
            pid_from_fork = fork(); //My note: int fork() returns (-) ifargc child creation failed, 0 to child if child was created, 
            // parent gets (+) if child was created 

            if(pid_from_fork < 0)
            {/* Error: fork() failed. Unlikely but possible 
                eg OS kernel runs out of memory or process descriptors  */
                fprintf(stderr, "fork fialed\n");
                continue; 
            }
            if(pid_from_fork == 0)
            {   
                //TO-DO P5.6 and P5.7

                return imthechild(exec_argv[0], &exec_argv[0]);
                /* Exit from main */
            }
            else 
            {
                imtheparent(pid_from_fork, run_in_background);
                /* Parent will continue around the loop */
            }
        }/* end if */
    }/* end while loop */
    return EXIT_SUCCESS;
}/* end main() */

