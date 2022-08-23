/* 运行时间：3ms 占用内存：332KB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 0x7FFFFFFF
#define MAX_INPUT_STR_LEN                (10)

int check_char_range(char ch, char min, char max)
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
    return check_char_range(ch, '0', '9');
}

int check_char_is_hex_range(char ch)
{
    return (check_char_range(ch, 'a', 'f') || check_char_range(ch, 'A', 'F'));
}

int check_char_is_lowercase(char ch)
{
    return check_char_range(ch, 'a', 'z');
}

int check_input_valid(char *input_str)
{
    char tmp_str;
    int index = 0;
    int input_str_len = 0;
    int ret = 0;
    
    if(NULL == input_str)
    {
        // input string is null, just return -1
        printf("1\n");
        return -1;
    }
    
    input_str_len = strlen(input_str);
    
    // Check length of input string, the min will be 3, because input is hex value, which starting with 0x, and need at least 1 value
    if(input_str_len < 3 || input_str_len > MAX_INPUT_STR_LEN)
    {
        // input string length less than 3, or larget than 10, just return -1
        printf("2\n");
        return -1;
    }
    // Check if input is starting with 0x or 0X
    
    tmp_str = input_str[0];
    
    if(tmp_str != '0')
    {
        // It's not starting with 0x or 0X, just return -1
        printf("3\n");
        return -1;
    }
    else
    {
        tmp_str = input_str[1];
        // printf("%c\n",tmp_str);
        if(tmp_str != 'x')
        {
            // It's not starting with 0x or 0X, just return -1
            printf("4\n");
            return -1;
        }
        index = 2;
        tmp_str = input_str[index];
    }
    
    if(input_str_len == MAX_INPUT_STR_LEN)
    {
        // need to make sure the largest range.
        if(tmp_str > '7')
        {
            // It will overflow, just return -1
            printf("5\n");
            return -1;
        }
        index ++;
        tmp_str = input_str[index];
    }
    
    // Check the real value
    while(0 != tmp_str)
    {
        //printf("%02x\n", tmp_str);
        if(check_char_is_digi(tmp_str))        // If it's digi, continue directly
        {
            index ++;
            tmp_str = input_str[index];
            continue;
        }
        else
        {
            if(check_char_is_hex_range(tmp_str))    // It's not digi, but it's a - f
            {
                index ++;
                tmp_str = input_str[index];
                continue;
            }
            else                                    // Got non digi and non a - f range, quit the loop directly
            {
                printf("6\n");
                ret = -1;
                break;
            }
        }
    }
    
    return ret;
}

unsigned int do_hex_to_dec(char *str)
{
    unsigned int dec_sum = 0;
    unsigned int base = 0;
    int str_len = 0;
    int i = 0;
    int tmp_val = 0;
    
    str_len = strlen(str);
    
    for(i = str_len; i > 0; i--)
    {
        base = (unsigned int)pow(16, i - 1);
        if(check_char_is_digi(str[str_len - i]))
        {
            // It's a digi
            tmp_val = str[str_len -i] - '0';
        }
        else
        {
            // It's A - F
            tmp_val = str[str_len - i] - 'A' + 10;
        }
        dec_sum += tmp_val * base;
    }
    
    return dec_sum;
}

unsigned int hex_to_dec(char *str)
{
    char conv_str[MAX_INPUT_STR_LEN];
    int str_len = 0;
    int i = 0;
    
    memset(&conv_str, 0, sizeof(conv_str));
    str_len = strlen(str);
    // remove starting 0x or 0X, 
    // and if it's lowercase char, conver to uppercase char
    strncpy(conv_str, str + 2, str_len - 2);
    for(i = 0; i < str_len - 2; i++)
    {
        if(check_char_is_lowercase(conv_str[i]))
        {
            conv_str[i] -= 0x20;
        }
    }
    
    return do_hex_to_dec(conv_str);
}

int main(int argc, char *argv[])
{
    char input_str[MAX_INPUT_STR_LEN + 2];
    unsigned int result = 0;
    
    memset(&input_str, 0, sizeof(input_str));
    
    // Get 1 line input
    if(fgets(input_str, MAX_INPUT_STR_LEN + 2, stdin) != NULL)
    {
        input_str[strlen(input_str) - 1] = '\0';
    }
    
    // Check if input is valid
    if(check_input_valid(input_str))        // input invalid, return -1
    {
        return -1;
    }
    
    result = hex_to_dec(input_str);
    
    printf("%d\n", result);
    
    return 0;
}
