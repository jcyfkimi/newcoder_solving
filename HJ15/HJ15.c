/* 运行时间：3ms 占用内存：352KB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
#define MAX_INPUT_VAL                ((int)(pow(2,31) - 1))
#define MAX_INPUT_STR_LEN            (16)
 
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
 
int check_if_all_digi(char *str)
{
    char tmp_ch;
    int index = 0;
    int ret = 1;
     
    tmp_ch = str[index];
    while(tmp_ch != 0)
    {
        if(!check_char_is_digi(tmp_ch))
        {
            ret = 0;
            break;
        }
        index++;
        tmp_ch = str[index];
    }
     
    return ret;
}
 
 
 
int main(int argc, char *argv[])
{
    int ret = 0;
    int i = 0;
    int input_val = 0;
    int tmp_val = 0;
    int bit_one_count = 0;
    char input_str[MAX_INPUT_STR_LEN];
     
    if(fgets(input_str, MAX_INPUT_STR_LEN, stdin) != NULL)
    {
        input_str[strlen(input_str) - 1] = '\0';
    }
     
    if(!check_if_all_digi(input_str))
    {
        ret = -1;
        return ret;
    }
     
    input_val = atoi(input_str);
     
    if(input_val < 0 || input_val > MAX_INPUT_VAL)
    {
        ret = -1;
        return ret;
    }
     
    for(i = 0; i < 32; i++)
    {
        tmp_val = input_val >> i;
        if(tmp_val & 0x01 == 1)
        {
            bit_one_count++;
        }
    }
     
    printf("%d", bit_one_count);
     
    return ret;
}