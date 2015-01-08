#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFSIZE 2048
#define DELIM "\n "

int main()
{
    char *token;
    char buff[BUFFSIZE];
    int argc = 0;
    char *argv[100];
    pid_t pid = 0;
    int status = 0;

    
    printf("\nMyShell> ");
    
    while (fgets(buff,BUFFSIZE,stdin))
    {
        
        //for new iteration:
        //clear argc,argv
        memset(&argv[0], 0, sizeof(argv));
        argc = 0;
        
        
        token = strtok(buff,DELIM);
        
        //parse and tokenize into argv
        while( token != NULL )
        {
            argv[argc] = token;
            token = strtok(NULL, DELIM);
            argc++;
        }
        
        if (strcmp(argv[0], "exit")==0)
        {
            return 0;
        }
        
        
        if ((pid = fork()) < 0)
        {
            printf("ERROR: forking child process failed\n");
            return (1);
        }
        else if (pid == 0)
        {
            if (execvp(*argv, argv) < 0)
            {
                printf("ERROR: exec failed\n");
                return (1);
            }
        }
        else
        {
            while (wait(&status) != pid);
        }
        
        
        
        //DEBUGGING--------------------
        //for (int i = 0; i < argc; i++)
            //printf("argv: %s\n", argv[i]); //check argv
        
        //printf("argc: %d", argc); //check argc
        //-----------------------------

        
        printf("MyShell> ");
    }
    

    return 0;
}