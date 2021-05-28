#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>


void *threadrun(void *arg)
{
    printf("Hello i'm %d\n", getpid());
    return NULL;
}

int main(int argc, char *argv[])
{
    int nb;
    pthread_t *threads;

    if (argc != 2){
        perror("Need number of thread arg");
        return -1;}
    else
    {
        nb = atoi(argv[1]);
    }

    if ((threads = calloc(nb, sizeof(pthread_t))) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < nb; i++)
    {
      pthread_create(&(threads[i]), NULL,&threadrun, NULL);
    }


    for (int i = 0; i < nb; i++)
    {
        pthread_join(threads[i], NULL);
            
    }

    free(threads);
    exit(EXIT_SUCCESS);
}
