#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    int client_fd;
    struct sockaddr_in server;
    char buffer[50];

    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    connect(client_fd,(struct sockaddr *)&server,sizeof(server));

    do
    {
        printf("Enter your message : ");
        scanf("%s", buffer);
    
        send(client_fd, buffer, sizeof(buffer), 0);
    
        recv(client_fd, buffer, sizeof(buffer), 0);
    
        printf("From server : %s\n", buffer);
    
    } while(strcmp(buffer, "bye") != 0);



    close(client_fd);
    
    return 0;
}