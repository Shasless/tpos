#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct stack stack; 
 
struct stack { 
    int value; 
    stack *next; 
}; 
 
void push(stack **p, int value) { 
    stack *p_ptr = *p; 
    stack *new_stack = malloc(sizeof(stack)); 
    new_stack->value = value; 
    new_stack->next = p_ptr; 
    *p = new_stack; 
} 
 
int pop(stack **p) { 
    stack *p_ptr = *p; 
    if (p_ptr->next == NULL) { 
        return 0; 
    } 
    int value = p_ptr->value; 
    *p = p_ptr->next; 
    free(p_ptr); 
    return value; 
} 
 
void init_stack(stack **p) { 
    *p = malloc(sizeof(stack)); 
    (*p)->next = NULL; 
} 



int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;

    int addrlen = sizeof(address);
    char message[BUFFER_SIZE] = {0};
    int resultat;
    stack *p; 

    float result = 0;
    int cur_index = 0;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening\n");

    
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connection accepted\n");


        init_stack(&p);  

        while (message[0] != 'Q') { 
            memset(message, '\0', BUFFER_SIZE); 
            read(new_socket, message, BUFFER_SIZE); 
            switch (message[0]) { 
                case '-' : 
                    resultat = pop(&p) - pop(&p); 
                    push(&p, resultat); 
                    sprintf(message, "%d", resultat); 
                    write(new_socket, &message, strlen(message) + 1); 
                    break; 
                case '+' : 
                    resultat = pop(&p) + pop(&p); 
                    push(&p, resultat); 
                    sprintf(message, "%d", resultat); 
                    write(new_socket, &message, strlen(message) + 1); 
                    break; 
                case '*' : 
                    resultat = pop(&p) * pop(&p); 
                    push(&p, resultat); 
                    sprintf(message, "%d", resultat); 
                    write(new_socket, &message, strlen(message) + 1); 
                    break; 
                case '/' : 
                    resultat = pop(&p) / pop(&p); 
                    push(&p, resultat); 
                    sprintf(message, "%d", resultat); 
                    write(new_socket, &message, strlen(message) + 1); 
                    break; 
                case 'Q' : 
                    break; 
                default : 
                    push(&p, atoi(message)); 
                    write(new_socket, "Empilement OK", 14); 
            } 
    }

    printf("Conexion terminer\n");
    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);

    return 0;
}
