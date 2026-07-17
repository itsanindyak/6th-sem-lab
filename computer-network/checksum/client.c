#include <stdio.h>
#include <string.h>

char checks[10];

void genCheck(char data[], int data_len, int chunk_len) {
    char temp[200];
    memset(temp, '0', sizeof(temp));

    int padding_len = ((data_len + chunk_len - 1) / chunk_len) * chunk_len;
    strncpy(temp, data, data_len);
    temp[padding_len] = '\0';

    char w1[chunk_len + 1], w2[chunk_len + 1], sum[chunk_len + 1];
    int carry = 0;

    strncpy(w1, temp, chunk_len);
    w1[chunk_len] = '\0';          // fixed: was chunk_len+1

    for (int chunk = chunk_len; chunk < padding_len; chunk += chunk_len) {  // fixed: was <=
        strncpy(w2, temp + chunk, chunk_len);
        w2[chunk_len] = '\0';      // fixed: was chunk_len+1

        for (int i = chunk_len - 1; i >= 0; i--) {
            int a = w1[i] - '0';
            int b = w2[i] - '0';
            int s = a + b + carry;
            sum[i] = (s % 2) + '0';
            carry = s / 2;
        }
        sum[chunk_len] = '\0';

        while (carry) {
            for (int i = chunk_len - 1; i >= 0; i--) {
                int a = sum[i] - '0';
                int s = a + carry;
                sum[i] = (s % 2) + '0';
                carry = s / 2;
            }
        }
        strcpy(w1, sum);
    }

    // fixed: use w1 (the accumulated result), not sum (may be unset if only 1 chunk)
    for (int i = 0; i < chunk_len; i++) {
        checks[i] = (w1[i] == '0') ? '1' : '0';
    }
    checks[chunk_len] = '\0';
}

int main() {
    char data[10];
    printf("Enter data : ");
    scanf("%9s", data);   // fixed: bounded read
    genCheck(data, strlen(data), 4);
    printf("checksum :%s\n", checks);
    return 0;
}