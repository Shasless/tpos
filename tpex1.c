#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>


int main(int argc, const char* argv[]){
        int fd1[2];
       
        if(pipe(fd1) < 0 ){exit(1);}

        char base_string[] = " stringdebase";
        char new_string[100];

        pid_t pid;
        scanf("%s", new_string);
        pid = fork();
	
	if(pid < 0){
		printf("probleme");
		return 1;	
			
        }else if(pid == 0){

                char new_new_string[100];
                read(fd1[0], new_new_string, 100);
		int a = strlen(new_new_string);

		for( int i = 0; i < strlen(base_string);i++){
			new_new_string[a++] = base_string[i];
		}
		new_new_string[a] = '\0';
             

                write(fd1[1],new_new_string, strlen(new_new_string) +1);

                exit(0);

        }else{
                char new_new_string[100];
                write(fd1[1],new_string, strlen(new_string)+1);
                wait(NULL);
                read(fd1[0], new_new_string, 100);
                printf("Concatenated string : %s \n", new_new_string);
                
        
        }
        return 0;
}
