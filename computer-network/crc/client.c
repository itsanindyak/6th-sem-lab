#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

void generateCRC(char d[],char div[]){

    int data_len = strlen(d);
    int div_len = strlen(div);

    char temp[50];

    strcpy(temp,d);

    //append zero
    for(int i = data_len;i<data_len+div_len-1;i++)
        temp[i] = '0';

    // add delimeter 
    temp[data_len+div_len-1] = '\0';

    for(int i =0;i < data_len;i++){
        if(temp[i] == '1'){

            for(int j =0;j< div_len;j++){
                 temp[i + j] = (temp[i+j] == div[j]) ? '0' : '1' ;
            }
        }
    }

    //append crc to data

    for(int i = data_len;i< data_len+div_len-1;i++){
        d[i] = temp[i];
    }
    d[data_len+div_len-1] = '\0';
    
}

int main(){

    int client_fd;
    struct sockaddr_in server;
    char buffer[50];
    char divisor[20];
    char data[50];

    printf("Enter data : ");
    scanf("%s",data);
    
    printf("Enter divisor : ");
    scanf("%s",divisor);

    generateCRC(data,divisor);

    printf("Generate codeword : %s\n",data);

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr *)&server,sizeof(server));

    strcpy(buffer,data);
    
    send(client_fd,buffer,sizeof(buffer),0);
    close(client_fd);

    
    return 0;
}