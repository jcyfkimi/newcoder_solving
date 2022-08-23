/* 运行时间：2ms 占用内存：384KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input value range 1<= n <= 100000000
#define MAX_INPUT_STR_LEN            (9)

int check_char_in_range(char ch, char min, char max)
{
    int ret = 0;
    
    if(ch >= min && ch <= max)
    {
        ret = 1;
    }
    
    return ret;
}

int check_char_is_digi(char ch)
{
    return check_char_in_range(ch, '0', '9');
}

int check_if_str_all_digi(char *str)
{
    int ret = 1;
    int index = 0;
    char tmp_ch = 0;
    
    if(NULL == str)
    {
        ret = 0;
        return ret;
    }
    
    tmp_ch = str[index];
    while(tmp_ch != 0)
    {
        if(!check_char_is_digi(tmp_ch))
        {
            ret = 0;
            break;
        }
        index ++;
        tmp_ch = str[index];
    }
    
    return ret;
}

int check_repeated(char *str, char ch)
{
    int ret = 0;
    int index = 0;
    char tmp_ch;
    
    if(NULL == str)
    {
        ret = -1;
        return ret;
    }
    
    tmp_ch = str[index];
    
    while(0 != tmp_ch)
    {
        if(tmp_ch == ch)
        {
            ret = 1;
            break;
        }
        index ++;
        tmp_ch = str[index];
    }
    
    return ret;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int input_index = 0;
    int input_str_len = 0;
    int print_index = 0;
    char input_str[MAX_INPUT_STR_LEN + 2];
    char print_str[MAX_INPUT_STR_LEN];
    char tmp_ch = 0;
    
    
    memset(&input_str, 0, sizeof(input_str));
    memset(&print_str, 0, sizeof(print_str));
    
    if(fgets(input_str, MAX_INPUT_STR_LEN + 2, stdin) != NULL)
    {
        input_str[strlen(input_str) - 1] = '\0';
        input_str_len = strlen(input_str);
    }
    
    if(!check_if_str_all_digi(input_str) 
       || '0' == input_str[input_str_len - 1])
    {
        ret = 0;
        return ret;
    }
    
    input_index = input_str_len - 1;
    print_str[print_index] = input_str[input_index];
    input_index--;
    print_index++;
    tmp_ch = input_str[input_index];
    while(0 != tmp_ch)
    {
        if(!check_repeated(print_str, tmp_ch))
        {
            print_str[print_index] = tmp_ch;
            print_index ++;
        }
        input_index --;
        if(input_index < 0)
        {
            break;
        }
        else
        {
            tmp_ch = input_str[input_index];
        }
    }
    
    printf("%s\n", print_str);
    
    
    return ret;
}

