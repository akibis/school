#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	char buffer[2048];

	while (1) {
		dup2(fileno(stdout), fileno(stdout));
            	dup2(fileno(stdin), fileno(stdin));
		dup2(fileno(stderr), fileno(stderr));
            	printf("My Shell>");
		fgets(buffer, 2048, stdin);
		// Check that it is not exit command
		if (buffer[0] == 'e' && buffer[1] == 'x' && buffer[2] == 'i' && buffer[3] == 't' &&
			buffer[4] == '\n' && buffer[5] == 0) {
			break;
		}

		// the last character will be '\n' and we need to erase it before launching the command
		buffer[strlen(buffer) - 1] = 0;

		int cnt = 0;
		char* ptr;
		int out = -1;
		int redirect_stdin = 0;
		int redirect_stderr = 0;
		int redirect_stdout = 0;
		int pipe_out = 0;
		int fd[2];

		if (strstr(buffer, " > ")) {
			ptr = strstr(buffer, " > ");
			char* filename = ptr + 3;
			out = open(filename, O_WRONLY|O_CREAT | O_TRUNC, S_IRWXU);
			if (out == -1) { 
				printf("cannot open output file\n");
				continue;
			}
			redirect_stdout = 1;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " >> ")) {
			ptr = strstr(buffer, " >> ");
			char* filename = ptr + 4;
			out = open(filename, O_WRONLY|O_CREAT | O_APPEND, S_IRWXU);
			if (out == -1) { printf("cannot open output file\n"); continue; }
			redirect_stdout = 1;			
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " 2> ")) {
			ptr = strstr(buffer, " 2> ");
			char* filename = ptr + 4;
			out = open(filename, O_WRONLY|O_CREAT | O_TRUNC, S_IRWXU);
			if (out == -1) { printf("cannot open output file\n"); continue; }
			redirect_stderr = 1;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " 2>> ")) {
			ptr = strstr(buffer, " 2>> ");
			char* filename = ptr + 5;
			out = open(filename, O_WRONLY|O_CREAT | O_APPEND, S_IRWXU);
			if (out == -1) { printf("cannot open output file\n"); continue; }
			redirect_stderr = 1;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " < ")) {
			ptr = strstr(buffer, " < ");
			char* filename = ptr + 3;
			out = open(filename, O_RDONLY);
			if (out == -1) { printf("cannot open output file\n"); continue; }
			redirect_stdin = 1;
			cnt++;
			*ptr = 0;
		}
		int second_process_created = 0;
		char* process2_name;
		// phony array to not bother with memory allocation
		char myargv_temp1[2048][1048];
		char* myargv1[2048];
		int myargc1 = 0;
		

		if (strstr(buffer, " | ")) {
			ptr = 		strstr(buffer, " | ");	
			pipe(fd);
			process2_name = ptr + 3;
			cnt++;
			*ptr = 0;
			second_process_created = 1;
			pipe_out = 1;
			
			int i = 0;
			// parsing the arguments using spaces and NULL as deliminators
			while (process2_name[i]) {
				int j = 0;
				while (process2_name[i] && process2_name[i] != ' ') {
					myargv_temp1[myargc1][j] = process2_name[i];
					j++;
					i++;
				}
				myargv_temp1[myargc1][j] = 0;
				// copy to real argv array
				myargv1[myargc1] = myargv_temp1[myargc1];
				myargc1++;
				if (process2_name[i]) i++;
			}
			// we need to indicate the last arg
			myargv1[myargc1] = NULL;
		}


		int run_background = 0;
		if (strstr(buffer, "&")) {
			ptr = strstr(buffer, "&");
			cnt++;
			*ptr = 0;
			run_background = 1;
		}

		if (cnt > 1) {
			printf("Combinations of several special characters are not supported, try again.\n");
			continue;
		}


		// phony array to not bother with memory allocation
		char myargv_temp[2048][1048];
		char* myargv[2048];
		int myargc = 0;
		int i = 0;
		// parsing the arguments using spaces and NULL as deliminators
		while (buffer[i]) {
			int j = 0;
			while (buffer[i] && buffer[i] != ' ') {
				myargv_temp[myargc][j] = buffer[i];
				j++;
				i++;
			}
			myargv_temp[myargc][j] = 0;
			// copy to real argv array
			myargv[myargc] = myargv_temp[myargc];
			myargc++;
			if (buffer[i]) i++;
		}
		// we need to indicate the last arg
		myargv[myargc] = NULL;

		
		// launching the child processes
		pid_t child_pid;
		int status;
		child_pid = fork();
		if (child_pid == 0) {
			// child
			if (redirect_stdin) {
				if (-1 == dup2(out, fileno(stdin))) { printf("cannot redirect stdin\n"); exit(1); }
			}
			if (redirect_stdout) {
				if (-1 == dup2(out, fileno(stdout))) { printf("cannot redirect stdout\n"); exit(1); }
			}
			if (redirect_stderr) {
				if (-1 == dup2(out, fileno(stderr))) { printf("cannot redirect stderr\n"); exit(1); }
			}
			if (pipe_out) {
				if (-1 == dup2(fd[1], fileno(stdout))) { printf("cannot redirect pipe stdout\n"); exit(1); }
			}
			
			execvp(myargv[0], myargv);
			if (pipe_out) {
				close(fd[1]);			
			}
			exit(1);
			
		}
		else {
			// parent
			if (child_pid < 0) {
				printf("fork failed.\n");
				exit(1);
			}
			else if (!run_background) {
				waitpid(child_pid, 0, 0);
			}
			if (pipe_out) {
				close(fd[1]);			
			}
		}
		if (second_process_created) {
			child_pid = fork();
			if (child_pid == 0) {
				// child
				if (-1 == dup2(fd[0], fileno(stdin))) { printf("cannot redirect stdin\n"); exit(1); }
				execvp(myargv1[0], myargv1);
				exit(1);
			}
			else {
				// parent
				if (child_pid < 0) {
					printf("fork failed.\n");
					exit(1);
				}
				else {
					waitpid(child_pid, 0, 0);
					close(fd[0]);
					
				}
			}
		}

		if (out != -1) {
			close(out);
		}
	}

	return 0;
}

