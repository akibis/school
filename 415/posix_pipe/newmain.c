/* MCM 615 Lab2 Demo #2
**	See 615 Notes slide #48 for details!
**	Compile/execute under Linux using gcc
**
**	Usage (note that this program is implementing a
**	simple shell pipe:  'ps aux | grep mcm'
**	> ./lab2demo2 ps aux grep mcm
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

main(int argc, char *argv[]) {
	int	pid1,pid2;
	int	pipeID[2];
	int	status;

	if ((status = pipe(pipeID)) == -1) { /* error exit - bad pipe */
		perror("Bad pipe");
		exit(-1);
	}
	if ((pid1 = fork()) == -1) {  /* error exit - bad fork */
		perror("Bad fork");
		exit(-1);
	}
	if (pid1 == 0) { /* The first child process */
	/* make sure you start the last process in the pipeline first! */
		printf("The first child is starting: %s %s\n",argv[3],argv[4]);
		close (0);
		dup (pipeID[0]);
		close (pipeID[0]);
		close(pipeID[1]);
		execlp(argv[3],argv[3],argv[4],0); 
		/* error exit - exec returned */
		perror("Execl returned");
		exit(-1);
	}
	/* this is the parent again */
	if ((pid2 = fork()) == -1) { /* error exit - bad fork */
		perror("Bad fork");
		exit(-1);
	}
	if (pid2 == 0) { /* the second child process */
		printf("The second child is starting: %s %s\n",argv[1],argv[2]);
		close (1);
		dup(pipeID[1]);
		close(pipeID[0]);close(pipeID[1]);
		execlp(argv[1],argv[1],argv[2],0); 
		/* error exit - exec returned */
		perror("Execl returned");
		exit(-1);
	}
	/* back to the parent again */
	close(pipeID[0]);
	close(pipeID[1]);
	wait(pid1,0,0);
	wait(pid2,0,0);
	printf("The parent is exiting\n");
}