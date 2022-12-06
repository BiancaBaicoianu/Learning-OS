#include <stdio.h>
#include <pthread.h>		
#include <errno.h>
#include <stdlib.h>

void* rev(void *v){	// functie de reverse
    int len = 0;
    while(((char*)v)[++len]!='\0');
    
    char *rev = malloc(sizeof(char) * len);
    for(int i = 0;i < len;++i)
        rev[i] = ((char*)v)[len-i-1];
        
    return rev;
}

int main(int argc, char **argv){
    pthread_t thr;
    //cream pthread nou
    //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    if (pthread_create(&thr, NULL, rev, argv[1])) {
    // rev este functia care vrem sa fie executata
    //argv[1] este parametrul
        perror(NULL);
        return errno ;
    }
    
    void *result;
    //int pthread_join(pthread_t thread, void **retval);
    if(pthread_join(thr,& result)){		//pentru a astepta finalizarea executiei( explicit thread-ul din thr)
    	//daca result nu este NULL, va pune la adresa indicata rezultatul din rev
        perror(NULL);
        return errno;
    }
    printf("%s\n", result);
    return 0;
}
