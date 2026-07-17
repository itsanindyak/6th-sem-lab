#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void checkHamming(char ham[])
{
    int total = strlen(&ham[1]);   // Length from ham[1]

    int r = 0;
    while((1 << r) <= total)
        r++;

    int error = 0;
    
    ham[3] = (ham[3] == '0') ? '1' : '0';

    // Check parity bits
    for(int i = 0; i < r; i++)
    {
        int pos = 1 << i;
        int count = 0;

        for(int k = 1; k <= total; k++)
        {
            if(k & pos)
            {
                if(ham[k] == '1')
                    count++;
            }
        }

        if(count % 2 != 0)
            error += pos;
    }

    printf("\nReceived Hamming Code : ");

    for(int i = 1; i <= total; i++)
        printf("%c", ham[i]);

    printf("\n");

    if(error == 0)
    {
        printf("No Error\n");
    }
    else
    {
        printf("Error at Position : %d\n", error);

        // Correct the bit
        if(ham[error] == '1')
            ham[error] = '0';
        else
            ham[error] = '1';

        printf("Corrected Hamming Code : ");

        for(int i = 1; i <= total; i++)
            printf("%c", ham[i]);

        printf("\n");
    }

    // Print original data bits
    printf("Original Data : ");

    for(int i = 1; i <= total; i++)
    {
        // Skip parity positions (1,2,4,8,...)
        if((i & (i - 1)) != 0)
            printf("%c", ham[i]);
    }

    printf("\n");
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server;
    char ham[100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    listen(server_fd, 10);

    printf("Waiting for Client...\n");

    client_fd = accept(server_fd, NULL, NULL);

    recv(client_fd, ham, sizeof(ham), 0);

    checkHamming(ham);

    close(client_fd);
    close(server_fd);

    return 0;
}