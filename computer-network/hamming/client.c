#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

void generateHamming(char ham[], char data[])
{
    int m = strlen(data);
    int r = 0;

    // Calculate parity bits
    while((1 << r) < (m + r + 1))
        r++;

    int total = m + r;

    int j = 0;

    // Place parity and data bits
    for(int i = 1; i <= total; i++)
    {
        if((i & (i - 1)) == 0)
            ham[i] = '0';
        else
            ham[i] = data[j++];
    }

    // Calculate parity
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

        ham[pos] = (count % 2) + '0';
    }

    // End of string
    ham[total + 1] = '\0';

    printf("\nGenerated Hamming Code : ");

    for(int i = 1; i <= total; i++)
        printf("%c", ham[i]);

    printf("\n");
}

int main()
{
    int client_fd;

    struct sockaddr_in server;

    char data[100];
    char ham[100];

    printf("Enter Data : ");
    scanf("%s", data);

    generateHamming(ham, data);

    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    connect(client_fd, (struct sockaddr *)&server, sizeof(server));

    // Send complete 1-based array
    send(client_fd, ham, sizeof(ham), 0);

    close(client_fd);

    return 0;
}