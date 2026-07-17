#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int checkError(char data_word[],int dw_len,int chunk_len){
    char w1[chunk_len+1], w2[chunk_len+1] , sum[chunk_len+1];
    int carry =0;
    
    strncpy(w1,data_word,chunk_len);
    w1[chunk_len] = '\0';

    for(int chunk = chunk_len; chunk < dw_len;chunk+=chunk_len){
        strncpy(w2,data_word+chunk,chunk_len);
        w2[chunk_len] = '\0';

        for(int i = chunk_len -1;i>=0;i--){
            int a = w1[i] -'0';
            int b = w2[i] -'0';
            int s = a+b+carry;

            sum[i] = (s%2) +'0';
            carry = s/2;
        }
        sum[chunk_len] = '\0';

        while(carry){
            for(int i = chunk_len -1;i>=0;i--){
                
                int a = sum[i] -'0';
                int s = a+carry;
    
                sum[i] = (s%2) +'0';
                carry = s/2;
            }
        }
        strcpy(w1,sum);
    }

    for(int i =0;i< chunk_len;i++){
        if(w1[i] != '1') return 0;
    }
    return 1;
    
}

int main(){
    
    char full_word[200];
    int chunk_len;

    printf("Enter chunk size    : ");
    scanf("%d", &chunk_len);
    
    printf("Enter full word (data+checksum): ");
    scanf("%199s", full_word);

    int total_len = strlen(full_word);

    if (total_len % chunk_len != 0) {
        printf("Error: word length not a multiple of chunk size\n");
        return 1;
    }

    int ok = checkError(full_word, total_len, chunk_len);
    printf(ok ? "No error detected\n" : "Error detected!\n");

    return 0;
}
