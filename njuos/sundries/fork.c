#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	pid = fork();

	if (pid < 0) {
		perror("Fork failed");
		return 1;
	} else if (pid == 0) {
		printf("[Child]	I am the child process. PID: %d\n", getpid());
		printf("[Child] My parent's PID is: %d\n", getppid());

		printf("[Child] Working...\n");
		sleep(2);

		printf("[Child] Task finished. Exiting.\n");
		exit(0);
	} else {
		printf("[Parent] I am the parent process. PID: %d\n", getpid());
		printf("[Parent] I created a child with PID: %d\n", pid);
		printf("[Parent] Waiting for my child process to finish...\n");
		
		wait(NULL);

		printf("[Parent] child has finished. Parent is now exiting.\n");
	}

	return 0;
}
