#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>



int main(){
    int server_fd, client_fd;  // server socket and client socket
    struct sockaddr_in server;  // store information of server's ip and port
    char buffer[512];


    server_fd = socket(AF_INET,SOCK_STREAM,0); // create a socket

    server.sin_family = AF_INET;
    server.sin_port = htons(6000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");


    bind(server_fd,(struct sockaddr *)&server,sizeof(server)); // bind socket to ip and port

    listen(server_fd,10); 

    printf("Waiting for client...\n");

    client_fd = accept(server_fd,NULL,NULL);


    read(client_fd,buffer,sizeof(buffer));

    printf("Client: %s\n", buffer);

    strcpy(buffer, "Hello Client");     

    write(client_fd,buffer, sizeof(buffer)+1);


    close(client_fd);
    close(server_fd);
}