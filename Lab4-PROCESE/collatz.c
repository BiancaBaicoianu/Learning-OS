#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void collatz(int n){
	while( n != 1){
		printf("%d ", n);
		if (n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
		}
	printf("%d\n", 1);
}


int main(int argc, char *argv[]){
	if (argc < 2)
		printf("Eroare! Argumente insuficiente!");
	else{
		pid_t pid = fork();
		if(pid < 0)
			return errno;
		else{
			int n = atoi(argv[1]);
			if(pid == 0){
				// instructiuni copil
				printf("%d: ", n);
				collatz(n);
				}
			else{
				// instructiuni parinte
				wait(NULL);
				printf("Child %d finished\n", pid);
				}
		}
	}
	return 0;
}

