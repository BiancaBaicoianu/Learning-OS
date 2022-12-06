#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void collatz(int x){
	while(x != 1){
		printf("%d ", x);
		if(x % 2 == 0)
			x = x / 2;
		else
			x = 3 * x + 1;
	}
}

int main(int argc, char *argv[]){
    if(argc<2)
	 return -1;

    printf("Starting parent %d\n", getppid());

    pid_t pids[argc];

    for(int i = 0;i < argc;++i){
	pids[i] = fork();
        if(pids[i] < 0)
            return errno;
        else if(pids[i] == 0){
            int n = atoi(argv[i+1]);
            printf("%d: ", n);
            collatz(n);
            printf("\n");
            exit(0);}
	}

    for(int i = 0;i < argc;++i){
        printf("Done Parent %d Me %d\n", getppid(), getpid());
        wait(NULL);
    }
    
    return 0;
}
