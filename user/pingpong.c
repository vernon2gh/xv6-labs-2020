#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
	int pipefd[2];
	int pid;
	char tmp = 1;

	pipe(pipefd);
	pid = fork();

	if(pid == 0) { // the child process
		read(pipefd[0], &tmp, 1);
		printf("%d: received ping\n", getpid());

		write(pipefd[1], &tmp, 1);
	}
	else {         // the parent process
		write(pipefd[1], &tmp, 1);

		wait((int *)0);

		read(pipefd[0], &tmp, 1);
		printf("%d: received pong\n", getpid());
	}

	exit(0);
}
