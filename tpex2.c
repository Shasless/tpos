#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void *threadrun(void *a){
        printf("hello I'm %d",getpid());
	
}

int main(int argc, const char* argv[]){

        int nb = atoi(argv[1]);
        pthread_t threads;
	threads =malloc(nb * sizeof(pthread_t));

	if(argc =!2){
		printf("erreur");
		exit(0);
	}
       

        for( int y; y < nb; y++){
                pthread_create(&threads[y], NULL, threadrun, NULL);
        }
        for(int y; y < nb; y++){
                pthread_join(threads[y], NULL);
        }
        printf("-------THE END--------");
        free(threads);
        return 0;
}
