//Name(s): Jesus Martinez
//Date 10/04/26

/* SMP1: Simple Shell */

/* LIBRARY Section */
#include <ctype.h>              /* Character types                          */
#include <stdio.h>              /* Standard buffered input/output           */
#include <stdlib.h>             /* Standard library functions               */
#include <string.h>             /* String Operations                        */
#include <sys/types.h>          /* Data types                               */
#include <sys/wait.h>           /* Declarations for waiting                 */
#include <unistd.h>             /* Standard symbolic constants and types    */ //My note: unisstd.h provides pid_t
#include <errno.h>              //My note: checks if waitpid was interrupted

#include "smp1_tests.h"         /* Built-in test system                     */


/* DEFINE SECTION */
#define SHELL_BUFFER_SIZE 256   /* Size of the Shell input buffer     */
#define SHELL_MAX_ARGS 8        /* Maximum number of arguments parsed */

/* VARIABLE SECTION */
enum {STATE_SPACE, STATE_NON_SPACE }; /* Parser states */
//parser states 0 1

int shell_depth = 1; //My note: original shell is level 1 P5.7

int imthechild(const char *path_to_exec, char *const args[]) // My note: paremeter types set to use int execv(const char *path, char *const argv[])
{
    //TO-DO P5.1: Resolve PATH/relative/absolute command to an execv path
    //My note: 4 cases given

    int has_slash = 0;

    //My note: also checks paths such as folder/program
    for (int j = 0; path_to_exec[j] != '\0'; j++)
    {
        if (path_to_exec[j] == '/')
        {
            has_slash = 1;
            break;
        }
    }

    if (has_slash || path_to_exec[0] == '.')
    {
        execv(path_to_exec, args);

        fprintf(stderr, "Command %s does not exist\n", path_to_exec);
        return EXIT_FAILURE;
    }

    char *path = getenv("PATH");

    if (path == NULL)
    {
        fprintf(stderr, "Command %s does not exist\n", path_to_exec);
        return EXIT_FAILURE;
    }

    //My note: copy PATH since we will replace the colons with '\0'
    char *path_copy = malloc(strlen(path) + 1);

    if (path_copy == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    strcpy(path_copy, path);

    int start = 0;
    int end = 0;
    int last_directory = 0;

    while (!last_directory)
    {
        //My note: find where this directory ends
        while (path_copy[end] != ':' && path_copy[end] != '\0')
        {
            end++;
        }

        if (path_copy[end] == '\0')
        {
            last_directory = 1;
        }

        path_copy[end] = '\0';

        char *directory = &path_copy[start];

        //My note: an empty PATH directory means the current directory
        if (directory[0] == '\0')
        {
            directory = ".";
        }

        //My note: +2 gives space for '/' and the ending '\0'
        char *full_path = malloc(
            strlen(directory) + strlen(path_to_exec) + 2);

        if (full_path == NULL)
        {
            free(path_copy);
            fprintf(stderr, "Failed to allocate memory\n");
            return EXIT_FAILURE;
        }

        strcpy(full_path, directory);
        strcat(full_path, "/");
        strcat(full_path, path_to_exec);

        //My note: access returns 0 if the file can be executed
        if (access(full_path, X_OK) == 0)
        {
            execv(full_path, args);
        }

        //My note: successful execv never returns so this runs on failure
        free(full_path);

        if (!last_directory)
        {
            start = end + 1;
            end = start;
        }
    }

    free(path_copy);

    fprintf(stderr, "Command %s does not exist\n", path_to_exec);
    return EXIT_FAILURE;
}


void imtheparent(pid_t child_pid, int run_in_background)
{
    int child_return_val, child_error_code;

    /* fork returned a positive pid so we are the parent */
	fprintf(stderr,
			"  Parent says 'child process has been forked with pid=%d'\n",
			child_pid);

    if (run_in_background)
    {
        fprintf(stderr,
                " Parrent says 'run_in_background=1 ... so we're not waiting for the child'\n");
        return;
    }

    //TO-DO P5.5
    //My note: wait for this child instead of any child
    pid_t wait_result;

    do
    {
        wait_result = waitpid(child_pid, &child_return_val, 0);
    }
    while (wait_result == -1 && errno == EINTR);

    if (wait_result == -1)
    {
        perror("waitpid");
        return;
    }

	fprintf(stderr,
			"  Parent says 'wait() returned so the child with pid=%d is finished.'\n",
			child_pid);

    //My note: only get the exit code if the child exited normally
    if (WIFEXITED(child_return_val))
    {
        /* Use the WEXITSTATUS to extract the status code from the return value */
        child_error_code = WEXITSTATUS(child_return_val);

        if (child_error_code != 0)
        {
            /* Error: Child process failed. Most likely a failed exec */
            fprintf(stderr,
                    " Parent says 'Child process %d failed with code %d\n",
                    child_pid, child_error_code);
        }
    }
    else if (WIFSIGNALED(child_return_val))
    {
        //My note: the child was stopped by a signal instead of exiting normally
        fprintf(stderr,
                " Parent says 'Child process %d terminated by signal %d'\n",
                child_pid, WTERMSIG(child_return_val));
    }
}

/* MAIN PROCEDURE SECTION */
int main(int argc, char **argv) //My note: why is argv ** double pointer
{
    //My note: pid_t data type that represents process IDs
    pid_t shell_pid, pid_from_fork;
    int n_read, i, exec_argc, parser_state, run_in_background;

    /* buffer: The Shell's input buffer */
    char buffer[SHELL_BUFFER_SIZE]; // My note: char bufferArray[256]

    /* execv_argv: Arguments passed to the exec call including NULL terminator. */
    char *exec_argv[SHELL_MAX_ARGS + 1]; //My note: Assuming + 1 is for NULL terminator

    //TO-DO new variables for P5.2, P5.3, P5.7
    int command_counter = 0; //My note: Adding command counter P5.2
    char history[10][SHELL_BUFFER_SIZE] = {0};
    int history_count = 0;

    char command_copy[SHELL_BUFFER_SIZE];
    int history_index;
    int input_start;
    int extra_character;

    /* Entrypoint for the testrunner program */
    if (argc > 1 && !strcmp(argv[1], "-test")) //My note:
    {
        return run_smp1_tests(argc - 1, argv + 1);
    }

    /* Allow the Shell prompt to display the pid of this process */
    shell_pid = getpid();

    while (1)
    {
        /* The Shell runs in an infinite loop, processing input. */

        //My note: clean up finished background children without waiting
        while (waitpid(-1, NULL, WNOHANG) > 0)
        {
        }

        //TO-DO P5.2: Prompt must include pid and command counter.
        fprintf(stdout, "Shell(pid=%d)%d> ", shell_pid, command_counter);
        fflush(stdout); //My note: int fflush(FILE* stream) was is the assoicated output device

        /* Read a line of input. */
        if (fgets(buffer, SHELL_BUFFER_SIZE, stdin) == NULL) //My note: char* fgets(char* str, int count, FILE* stream) = str on success and = null pointer on failure
        {
            //My note: NULL can also mean a read error so check that first
            if (ferror(stdin))
            {
                perror("fgets");
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS; //My note: EXIT_SUCCESS/EXIT_FAILURE
        }

        //My note: So fgets fails return Exitsuccess ? why success -> means that no line was read so cant continue so exit
        //but since the logic to catch it worked its a success

        n_read = strlen(buffer); //My note: size_t strlen(const char* str) returns the length of the given null-terminated byte string

        //My note: reject a line that is too long and clear its remaining input
        if (n_read > 0 && buffer[n_read - 1] != '\n')
        {
            if (n_read == SHELL_BUFFER_SIZE - 1)
            {
                extra_character = getchar();

                while (extra_character != '\n' && extra_character != EOF)
                {
                    extra_character = getchar();
                }

                fprintf(stderr, "Command too long\n");
                continue;
            }

            //My note: allow a final input line that does not have a newline
            buffer[n_read] = '\n';
            buffer[n_read + 1] = '\0';
            n_read++;
        }

        //My note: remove leading spaces so a history request can start after spaces
        input_start = 0;

        while (buffer[input_start] != '\n' &&
               isspace((unsigned char)buffer[input_start]))
        {
            input_start++;
        }

        if (input_start > 0)
        {
            memmove(buffer, &buffer[input_start],
                    strlen(&buffer[input_start]) + 1);
        }

        //My note: remove trailing spaces but keep the newline for the parser
        n_read = strlen(buffer);

        while (n_read > 1 &&
               isspace((unsigned char)buffer[n_read - 2]))
        {
            buffer[n_read - 2] = '\n';
            buffer[n_read - 1] = '\0';
            n_read--;
        }

        //TO-DO P5.3
        if (buffer[0] == '!')
        {
            if (n_read != 3 ||
                buffer[1] < '0' || buffer[1] > '9')
            {
                fprintf(stderr, "Not valid\n");
                continue;
            }

            //My note: subtracting '0' changes the digit character to an int
            history_index = buffer[1] - '0';

            if (history_index >= history_count)
            {
                fprintf(stderr, "Not valid\n");
                continue;
            }

            strcpy(buffer, history[history_index]);
        }

        //My note: save the full command before parsing changes its spaces
        strcpy(command_copy, buffer);

        n_read = strlen(buffer);

        run_in_background = n_read > 2 && buffer[n_read - 2] == '&'; //My note: results in run_in_background = 0/1
        //My note: n>2 checks if more than 2 chars and buff[n-2] check 0 1 & /n /0 => 4-2 = & true
        buffer[n_read - run_in_background - 1] = '\n';

        /* Parse the arguments: the first argument is the file or command
            we want to run                                                  */

        parser_state = STATE_SPACE;
        //My note: declared int exec_argc
        //buffer doesnt reach \n good
        for (exec_argc = 0, i = 0;
             buffer[i] != '\n' && buffer[i] != '\0'; i++)
        { //My note: Enters loop with exec_argc = 0

            if (!isspace((unsigned char)buffer[i])) //My note: int isspace(int ch) returns non-zero value if the character is a whitespace character, zero otherwise
            { //My note: Enters if when non white space character
                if (parser_state == STATE_SPACE) // My note: What is the significance of the StateSpace and why is not reset it only works once
                {
                    //My note: stop at the start of an extra argument
                    if (exec_argc == SHELL_MAX_ARGS)
                    {
                        break;
                    }

                    exec_argv[exec_argc++] = &buffer[i]; //My note: Commands are passed from buffer to the exec_argv[exec_argc /w post increment]
                }

                parser_state = STATE_NON_SPACE; // Paser State = 1
            }
            else
            {
                buffer[i] = '\0'; //My note Null terminating the buffer if it is white space character
                parser_state = STATE_SPACE;
            }
        }

        /* run_in_background is 1 if the input line's last character
            is an ampersand (indicating background execution).          */
        buffer[i] = '\0'; /* Terminate input, overwritting the '&' if it exists */

        /* If no command was given (emnpty line) the Shell just prints the prompt again */
        if (!exec_argc)
            continue;

        //My note: store in the current slot before increasing the counter
        strcpy(history[command_counter], command_copy);

        if (history_count < 10)
        {
            history_count++;
        }

        command_counter++; //My note: Incrementing did not add to if since checks for empty lines

        //My note: circular history goes back to slot 0 after slot 9
        if (command_counter == 10)
        {
            command_counter = 0;
        }

        /* Terminate the list of the exec parameters with NULL */
        exec_argv[exec_argc] = NULL;

        /* If Shell runs 'exit' it exits the program. */
        if (!strcmp(exec_argv[0], "exit"))
        {
            printf("Exiting process %d\n", shell_pid);
            return EXIT_SUCCESS; /* End Shell program */
        }
        else if (!strcmp(exec_argv[0], "cd"))
        {
            /* Running 'cd' changes the Shell's working directory. */
            /* Alternative: try chdir inside a forked child: if(fork() == 0) { */

            if (exec_argc < 2)
            {
                fprintf(stderr, "cd: missing directory\n");
            }
            else if (chdir(exec_argv[1]))
            {
                /* Error: change directory failed */
                fprintf(stderr, "cd: failed to chdir %s\n", exec_argv[1]);
            }

            /* End alternative: exit(EXIT_SUCCESS);} */
        }
        // TO-DO P5.4
        else if (!strcmp(exec_argv[0], "history"))
        {
            //My note: history already includes this history command
            for (int j = 0; j < history_count; j++)
            {
                //My note: the stored command already has a newline
                printf("%d. %s", j, history[j]);
            }
        }
        else
        {
            /* Execute Commands */
            /* Try replacing 'fork()' with '0'. What happens? */

            //My note: check depth before creating another subshell
            if (!strcmp(exec_argv[0], "sub") && shell_depth >= 3)
            {
                fprintf(stderr, "Too deep!\n");
                continue;
            }

            //My note: flush output before fork copies the process
            fflush(NULL);

            pid_from_fork = fork(); // 0 -> fork();

            if (pid_from_fork < 0)
            {
                /* Error: fork() failed.  Unlikely, but possible (e.g. OS *
                 * kernel runs out of memory or process descriptors).     */
                fprintf(stderr, "fork failed\n");
                continue;
            }

            if (pid_from_fork == 0)
            {
                // TO-DO P5.6 and P5.7
                if (!strcmp(exec_argv[0], "sub"))
                {
                    //My note: child is already running the shell so reset its values
                    shell_pid = getpid();
                    shell_depth++;
                    command_counter = 0;
                    history_count = 0;

                    for (int j = 0; j < 10; j++)
                    {
                        history[j][0] = '\0';
                    }

                    //My note: return to the while loop as the new subshell
                    continue;
                }

                return imthechild(exec_argv[0], &exec_argv[0]);
                /* Exit from main. */
            }
            else
            {
                imtheparent(pid_from_fork, run_in_background);
                /* Parent will continue around the loop. */
            }
        } /* end if */
    } /* end while loop */

    return EXIT_SUCCESS;
} /* end main() */