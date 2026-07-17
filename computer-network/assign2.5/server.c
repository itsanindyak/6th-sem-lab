#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){

    int server_fd, client_fd;
    struct sockaddr_in server;
    char buffer[50];

    server_fd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_fd,(struct sockaddr *)&server,sizeof(server));

    listen(server_fd,10);
    
    printf("Waiting for client...\n");

    client_fd = accept(server_fd,NULL,NULL);

    do
       {
           recv(client_fd, buffer, sizeof(buffer), 0);
   
           printf("From Client : %s\n", buffer);
   
           printf("Enter your message : ");
           scanf("%s", buffer);
   
           send(client_fd, buffer, sizeof(buffer), 0);
   
       } while(strcmp(buffer, "bye") != 0);



    close(server_fd);
    close(client_fd);
    
    return 0;
}