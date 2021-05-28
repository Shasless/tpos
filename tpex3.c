#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void *threadrun(void *a){
        printf("hello I'm %d, and i'm of the thread number %d",getpid(),*(int *) a);
}

int main(int argc, const char* argv[]){

        int nb = atoi(argv[1]);
        pthread_t threads[nb];
       

        for( int y; y < nb; y++){
                pthread_create(&threads[y], NULL, threadrun, y);
        }
        for(int y; y < nb; y++){
                pthread_join(threads[y], NULL);
        }
        printf("-------THE END--------");
        free(threads);
        return 0;
}
