#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int Somme = 0;
pthread_mutex_t lock;


void *threadrun(void *a){
        printf("hello I'm %d, and i'm of the thread number %d",getpid(),*(int *) a);

	for (int j = 0; j< 1000000; j++){
		pthread_mutex_lock(&lock);
		Somme += *(int *) a;
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}

int main(int argc, const char* argv[]){

        int nb = atoi(argv[1]);
        pthread_t threads[nb];
	int args[nb];
       
	
	if(pthread_mutex_init(&lock, NULL) !=0){
		printf("eror in the mutex");
		return 1;
	}
        for( int y; y < nb; y++){
		args[y] = y;
                pthread_create(&threads[y], NULL, threadrun, &args[y]);
        }
        for(int y; y < nb; y++){
                pthread_join(threads[y], NULL);
        }
        printf("-------THE END--------");
        return 0;
}
