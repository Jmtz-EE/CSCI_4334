//Name(s): Jesus Martinez
//Date 10/02/26

/* SMP1: Simple Shell */

/* LIBRARY Section */
#include <ctype.h>              /* Character types                          */    
#include <stdio.h>              /* Standard buffered input/output           */
#include <stdlib.h>             /* Standard library functions               */
#include <string.h>             /* String Operations                        */
#include <sys/types.h>          /* Data types                               */
#include <sys/wait.h>           /*                                          */
#include <unistd.h>             /* Standard symbolic constants and types    */ //My note: unisstd.h provides pid_t


#inlcude "smp1_tests.h"         /* Built-in test system                     */


/* DEFINE SECTION */
#define SHELL_BUFFER_SIZE 256   /* Size of the Shell input buffer     */
#define SHELL_MAX_ARGS 8        /* Maximum number of arguments parsed */

/* VARIABLE SECTION */
enum {STATE_SPACE, STATE_NON_SPACE }; /* Parser states */
//parser states 0 1

int imthechild(const char *path_to_exec, char *const args[]) // My note: paremeter types set to use int execv(const char *path, char *const argv[])
{
    //TO-DO P5.1: Resolve PATH/relative/absolute command to an execv path
    return execv(path_to_exec, args) ? -1 : 0; 

}


void imtheparent(pid_t, child_pid, int run_in_background)
{
    int child_return_val, child_error_code;

    /* fork returned a positive pid so we are the parent */
    fprintf(stderr, 
            "   Parent says 'child process has been forked wiht pid=%d'\n", 
            child_pid); 
    if (run_in_background) {
        fprintf(stderr,
                " Parrent says 'run_in_background=1 ... so we're not waiting for the child'\n");
        return; 
    }
    //TO-DO P5.5 
    wait(&child_return_val); 
    /* Use the WEXITSTATUS to extract the status code from the return value */
    child_error_code = WEXITSTATUS(child_return_val); 
    fprintf(stderr,
            "   Parent says 'wait() returned so the child with pid=%d is finished.'\n", 
             child_pid); 
    
//continue here after call 









}

/* MAIN PROCEDURE SECTION */
int main(int argc, char **argv)
{
    //My note: pid_t data type that represents process IDs
    pid_t shell_pid, pid_from_fork;
    int n_read, i, exec_argc, parser_state, run_in_background;
    /* buffer: The Shell's input buffer */
    char buffer[SHELL_BUFFER_SIZE]; // My note: 256


}/* end main() */

