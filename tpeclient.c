#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
 

#define PORT 8080
#define BUL_LEN 100

int main(int argc, char const* argv[]) {
    char commande[1024] = {0}; 
    char message[1024] = {0}; 

    int client = socket(AF_INET, SOCK_STREAM, 0);
    if (!client) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address = {.sin_family = AF_INET,
                                  .sin_port = htons(PORT)};
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(client, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

     while (commande[0] != 'Q') { 
        printf("Entrez votre operation ou Q pour sortir.\n"); 
        scanf(" %1023s", commande); 
        write(client, commande, strlen(commande) + 1); 
        read(client, message, 1023); 
        printf("Message recu : %s\n", message); 
    } 
    
    shutdown(client, SHUT_RDWR); 
    close(client); 
    printf("Connection terminer");

    return 0;
}