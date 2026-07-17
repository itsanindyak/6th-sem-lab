#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    int client_fd;
    struct sockaddr_in server;
    char buffer[512];

    server.sin_family = AF_INET;
    server.sin_port = htons(6000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    connect(client_fd,(struct sockaddr *)&server, sizeof(server));

    //message 
    strcpy(buffer,"hello server");

    write(client_fd, buffer, sizeof(buffer));

    read(client_fd, buffer, sizeof(buffer));

    printf("server : %s\n", buffer);

    close(client_fd);

    
    return 0;

    
    

    
    printf("hello");
}