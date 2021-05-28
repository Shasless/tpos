#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>



typedef struct arg { 
    int nbrThread; 
    int *Somme; 
    pthread_mutex_t* mutexT; 
} arg;

void *threadrun(void *a)
{
    printf("Hello i'm %d, et i'm from %d\n", getpid(),((arg *) a)->nbrThread);
    pthread_mutex_lock(((arg *) a)->mutexT); 

     for (int j = 0; j < 1000000; j++) { 
        *((arg *) a)->Somme += ((arg *)a) ->nbrThread; 
    } 
    pthread_mutex_unlock(((arg *) a)->mutexT); 


    return NULL;
}

int main(int argc, char *argv[])
{
    int nb, somme =0;

    pthread_t *threads;
    int *args = calloc(sizeof(int), nb);
    arg *argObj = malloc(nb * sizeof(arg)); 


    if (argc != 2){
        perror("Need number of thread arg");
        return -1;}
    else
    {
        nb = atoi(argv[1]);
    }
    pthread_mutex_t mutexT;
    if (pthread_mutex_init(&mutexT, NULL) != 0) { 
        printf("\n mutex init failed\n"); 
        return -1; 
    }
    if ((threads = calloc(nb, sizeof(pthread_t))) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < nb; i++)
    {
      argObj[i].nbrThread = i; 
      argObj[i].Somme = &somme; 
      argObj[i].mutexT = &mutexT;
      pthread_create(&(threads[i]), NULL,threadrun, &argObj[i]);
    }


    for (int i = 0; i < nb; i++)
    {
        pthread_join(threads[i], NULL);

    }

    printf("Somme: %d \n", somme);
    printf("------------THE END------------");
    free(threads);
    free(argObj);

    return 0;
    
}