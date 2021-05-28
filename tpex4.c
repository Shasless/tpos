#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

 
int Somme = 0; 
pthread_mutex_t mutexT;

void *threadrun(void *a)
{
    printf("Hello i'm %d, et i'm from %d\n", getpid(),*(int *) a );
    
     for (int j = 0; j < 1000000; j++) { 
        pthread_mutex_lock(&mutexT); 
        Somme += *(int *) a; 
        pthread_mutex_unlock(&mutexT); 
    } 
 

    return NULL;
}

int main(int argc, char *argv[])
{
    int nb;
    pthread_t *threads;
    int *args = calloc(sizeof(int), nb);

    if (argc != 2){
        perror("Need number of thread arg");
        return -1;}
    else
    {
        nb = atoi(argv[1]);
    }
    
    if (pthread_mutex_init(&mutexT, NULL) != 0) { 
        printf("\n mutex init failed\n"); 
        return -1; 
    }
    if ((threads = calloc(nb, sizeof(pthread_t))) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < nb; i++)
    {
      args[i] = i;
      pthread_create(&(threads[i]), NULL,&threadrun, &args[i]);
    }


    for (int i = 0; i < nb; i++)
    {
        pthread_join(threads[i], NULL);
            
    }
    
    printf("Somme: %d \n", Somme);
    printf("------------THE END------------");
    free(threads);
    
    return 0;
    
}
