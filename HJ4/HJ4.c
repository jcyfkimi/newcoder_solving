/* 运行时间：3ms 占用内存：380KB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_STR_LEN            (100)
#define REQUIRED_STR_LEN             (8)

char append_0_str_array[][8] = {"","0", "00", "000", "0000", "00000", "000000", "0000000"};

void print_single_str(char *str, int str_len)
{
    char tmp_str[REQUIRED_STR_LEN];
    memset(&tmp_str, 0, sizeof(tmp_str));
    strcpy(tmp_str, str);
    strcat(tmp_str, append_0_str_array[REQUIRED_STR_LEN - str_len]);
    printf("%s\n", tmp_str);
}


void print_multi_str(char *str, int str_len)
{
    char tmp_str[REQUIRED_STR_LEN + 1];
    int remain_str_len = 0;
    int printed_str_len = 0;
    int i = 0;
    
    remain_str_len = str_len;
    printed_str_len = 0;
    for(i = 0; i < str_len; i = (i + REQUIRED_STR_LEN))
    {
        //printf("i = %d\n", i);
        memset(&tmp_str, 0, sizeof(tmp_str));
        //printf("%s\n", str + printed_str_len);
        snprintf(tmp_str, sizeof(tmp_str), "%s", str + printed_str_len);
        
        // Check if remain_str_len > 8 or not
        if(remain_str_len > 8)
        {
            // just print out tmp_str
            printf("%s\n", tmp_str);
        }
        else
        {
            print_single_str(tmp_str, strlen(tmp_str));
        }
        
        remain_str_len -= REQUIRED_STR_LEN;
        printed_str_len += REQUIRED_STR_LEN;
    }
    
}


int main(int argc, char *argv[])
{
    char input_str[MAX_INPUT_STR_LEN + 2];
    int input_str_len = 0;
    
    memset(&input_str, 0, sizeof(input_str));
    
    // Get input strings
    if( fgets (input_str, MAX_INPUT_STR_LEN + 2, stdin)!=NULL )
    {
        //printf("input_str: %s\n", input_str);
        input_str[strlen(input_str)-1] = '\0';
    }
    //printf("input_str: %s\n", input_str);
    
    input_str_len = strlen(input_str);
    
    if(input_str_len <= 0 || input_str_len > 100)
    {
        // input length error, return -1;
        return -1;
    }
    //printf("input_str_len = %d\n", input_str_len);
    if(input_str_len <= 8)            // No need to devide
    {
        print_single_str(input_str, input_str_len);
    }
    else
    {
        print_multi_str(input_str, input_str_len);
    }
    
    
    return 0;
}