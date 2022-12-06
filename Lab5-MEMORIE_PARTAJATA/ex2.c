#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <errno.h>

//IDEE: impartim spatiul de memorie parinte in mai multe spatii de memorie

int main(int argc, char **argv){
    if(argc < 2) 
    	return -1;
    printf("Starting parent %d\n", getppid());
   //getpid() => parent process
   //getppid() => child process with parent id
    
    char shm_name[] = "myshm";
    int shm_fd;
    //se creeaza obiectele de memorie partajata
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    //s_irusr, s_iwusr sunt permisiunile pentru utilizatori
    //rezultatul este  un descriptor shm_fd care daca nu exista -> eroare
    if(shm_fd < 0){
    	perror(NULL);
    	return errno;
    	}
    	
    size_t shm_size = 1000;	
    
    //folosim ftruncate pentru a-i defini dimensiunea
    if(ftruncate(shm_fd, shm_size) == -1){
    	perror(NULL);
    	shm_unlink(shm_name);	//sterge ob cu numele shm_name creat cu sch_open
    	return errno;
    	}
    	
        int *shm_ptr = mmap(0, shm_size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0); //prin mmap accesezi memoria
    //PROT_READ = doar scrisa
    if(shm_ptr == MAP_FAILED)
    {
    //shm_ptr indica spre zona de memorie din shm_fd, incepand cu byte-ul 0
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    
    for(int i = 1;i < argc;++i){	
    	pid_t pid = fork();
    	if(pid < 0)
            return errno;
        else if( pid == 0){ 	//child
    		printf("Done Parent %d Me %d \n", getppid(), getpid());
    		int x = atoi(argv[i]);
            	char *mem = shm_ptr + (i-1)*(shm_size/(argc-1));
            	int aux = sprintf(mem, "%d: %d ", x, x);	//sprintf retine intr-un char buffer
            	//in continuare avem practic functia collatz
            	while(x != 1)
         	{
                	if(x % 2 == 0) 
                		x /= 2;
                	else x = x*3 + 1;
                	aux += sprintf(mem+aux, "%d ", x);
            	}
            	*(mem+aux)="NULL";	//face pointerul null
            	exit(0);
        }
    }

    //for(int i = 0; i < argc; ++i)
    	//wait(NULL);
    for(int i = 1; i < argc; ++i)
    	printf("%s\n", shm_ptr + (i-1)*(shm_size/(argc-1)));
    printf("Done Parent %d Me %d\n", getppid(), getpid());
    
    // int shm_unlink(const char *name);
    shm_unlink(shm_name);	//sterge obiectele create cu shm_open
    
    // int munmap(void *addr, size_t length);
    //folosim cand nu mai e nevoie de zona de memorie 
    munmap(shm_ptr, shm_size);
     
    return 0;
}




