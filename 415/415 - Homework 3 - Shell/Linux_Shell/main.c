/* 
 * File:   main.c
 * Author: netdom
 *
 * Created on September 28, 2014, 7:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define BUFFER_SIZE 2048
#define MAX_ARGS 20

/*
 * 
 */
int main() {

    char input[BUFFER_SIZE]; // single string of user args
    const char s[2] = "\n "; // string delimiter
    char* token; // single token from string
    int myargc = 0; // number of args
    char** myargv;
    pid_t cpid = 0;
    int status = 0, error;

    // redirect vars
    int redir_stdout = 0;
    int redir_stdin = 0;
    int redir_stderr = 0;
    int pipe = 0;
    int compare;
    int fd;

    while (1) {
        dup2(fileno(stdout), fileno(stdout));
        dup2(fileno(stdin), fileno(stdin));
        dup2(fileno(stderr), fileno(stderr));
        // reset argument memory
        myargv = (char**) calloc(MAX_ARGS, sizeof (char*));
        myargc = 0;

        // start shell gui and get user input
        printf("netdom> ");
        fgets(input, BUFFER_SIZE, stdin);
        token = strtok(input, s); // tokenize user input

        // tokenize user input and load into arg array
        while (token != NULL) {
            myargv[myargc++] = token;

            // REDIRECTS
            if (compare = strcmp(token, ">") == 0) {
                //printf("check: \n");
                token = strtok(NULL, ">");
                while(token[0] == ' '){
                    token++;
                }
                //token = strtok(NULL, ">");
                dup2(open(token, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU), 1);
//                redir_stdout = 1;
            }
//            if (redir_stdout) 
//                printf("fd: %d\n", fd);
//                dup2(fd, 1);
//                break;
//            
            token = strtok(NULL, s);

        }


        // exit shell upon keyword
        if (strcmp(myargv[0], "exit") == 0) {
            printf("<3\n");
            exit(EXIT_SUCCESS);
        }

        // exit on fork failure
        if ((cpid = fork()) < 0) {
            perror("Error sporking process o_O\n");
            exit(EXIT_FAILURE);
        } // execute command
        if (cpid == 0) {



            if (error = execvp(myargv[0], myargv) < 0) {
                perror("EXEC ERROR\n");
                exit(EXIT_FAILURE);
            }

            // have parent wait for child to finish
        } else {
            while (wait(&status) != cpid);
        }

        // free memory
        free(myargv);
    }

    return (EXIT_SUCCESS);
}

