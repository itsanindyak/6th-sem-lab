#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

void checkCRC(char dw[],char div[]){
    char temp[50];
    strcpy(temp,dw);

    for(int i =0;i< strlen(temp) - strlen(div)-1;i++){
        if(temp[i] == '1'){
            for(int j = 0;j< strlen(div);j++){
                temp[i+j] = (temp[i+j] == div[j]) ? '0' : '1';
            }
        }
    }

    int error = 0;

    for(int i = strlen(temp) - strlen(div) + 1;i<strlen(temp);i++){
        if(temp[i] == '1')
                {
                    error = 1;
                    break;
                }
    }
    if(error)
           printf("CRC Error Detected\n");
    else
           printf("No CRC Error\n");
}

int main(){

    int server_fd, client_fd;
    struct sockaddr_in server;
    char buffer[50];
    char divisor[20];

    printf("Enter divisor : ");
    scanf("%s",divisor);


    server_fd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_fd,(struct sockaddr *)&server, sizeof(server));

    listen(server_fd,10);

    printf("waiting for client....\n");

    client_fd = accept(server_fd,NULL,NULL);

    recv(client_fd,buffer,sizeof(buffer),0);


    //checking crc

    checkCRC(buffer,divisor);

    // end checking crc
    close(server_fd);
    close(client_fd);


    return 0;
}
