#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define r 3
#define c 3

int matrice1[r][c] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
};
int matrice2[r][c] = {
        {1,2,3},
        {2,3,4},
        {3,4,5}
};
int rez_matrice[r][c];

struct poz{
    int i, j;
};

void* inmultire(void* pozitie){
    struct poz * index = pozitie;
    int i = index->i;
    int j = index->j;

    rez_matrice[j][i] = 0;
    for(int k = 0;k < c;++k)
        rez_matrice[j][i] += matrice1[j][k] * matrice2[k][i];
    return NULL;
}

int main(){
    pthread_t threads[r*c];
    int cnt = 0;
    for(int i = 0;i < r;++i)
        for(int j = 0;j < c;++j){
            struct poz* index = calloc(1, sizeof(struct poz));
            index->i = i;
            index->j = j;
            if(pthread_create(&threads[cnt++], NULL, inmultire, index)){
                perror(NULL);
                return errno;
            }
        }

    for(int i = 0;i < cnt;++i)
        if(pthread_join(threads[i], NULL)){
            perror(NULL);
            return errno;
        }
    
    
    //afisare matrice 
    for(int i = 0;i < r;++i){
        for(int j = 0;j < c;++j)
            printf("%d ", rez_matrice[i][j]);
        printf("\n");
    }
    return 0;
}
