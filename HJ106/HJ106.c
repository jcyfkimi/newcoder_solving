/* 运行时间：3ms 占用内存：352KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_STR_LEN            (10000)


int main(int argc, char *argv[])
{
    int ret = 0;
    int i = 0;
    int input_str_len = 0;
    char input_str[MAX_INPUT_STR_LEN + 2];
    char print_str[MAX_INPUT_STR_LEN];
    
    memset(&input_str, 0, sizeof(input_str));
    memset(&print_str, 0, sizeof(print_str));
    
    if(fgets(input_str, MAX_INPUT_STR_LEN + 2, stdin) != NULL)
    {
        input_str[strlen(input_str) - 1] = '\0';
    }
    
    input_str_len = strlen(input_str);
    
    if(input_str_len < 1 || input_str_len > MAX_INPUT_STR_LEN)
    {
        ret = -1;
        return ret;
    }
    
    for(i = input_str_len - 1; i >= 0; i--)
    {
        print_str[input_str_len - i - 1] = input_str[i];
    }
    
    printf("%s\n", print_str);
    
    return ret;
}