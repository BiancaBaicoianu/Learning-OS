#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t pid = fork();
	if (pid < 0)
		return errno;
	else
		if(pid == 0){
			char *argv[] = {"ls", NULL};
			execve("/usr/bin/ls",argv, NULL);
			perror(NULL);
		}
		else{
			printf("my PID = %d Child PID = %d\n", getppid(), getpid());
			wait(NULL);
			printf("\nChild %d finished \n", pid);
		}
	return 0;
}
