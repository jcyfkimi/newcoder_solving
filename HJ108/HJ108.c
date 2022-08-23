/* 运行时间：119ms 占用内存：384KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_STR_LEN               (13)
#define MAX_INPUT_VAL                   (100000)
#define MIN_INPUT_VAL                   (1)

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

int check_char_is_space(char ch)
{
    return check_char_in_range(ch, ' ', ' ');
}

int check_input_str_valid(char *str)
{
    int ret = 1;
    int index = 0;
    char tmp_ch;
    
    tmp_ch = str[index];
    while(tmp_ch != 0)
    {
        if(!check_char_is_digi(tmp_ch) && !check_char_is_space(tmp_ch))
        {
            ret = 0;
            break;
        }
        index ++;
        tmp_ch = str[index];
    }
    return ret;
}

int check_input_value_in_range(int input_val)
{
    int ret = 0;
    
    if(input_val >= MIN_INPUT_VAL && input_val <= MAX_INPUT_VAL)
    {
        ret = 1;
    }
    
    return ret;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int input_num_a = 0;
    int input_num_b = 0;
    int max_number = 0;
    char input_str[MAX_INPUT_STR_LEN + 2];
    
    memset(&input_str, 0, sizeof(input_str));
    
    if(fgets(input_str, MAX_INPUT_STR_LEN + 2, stdin) != NULL)
    {
        input_str[strlen(input_str) - 1] = '\0';
    }
    
    if(!check_input_str_valid(input_str))
    {
        ret = -1;
        return ret;
    }
    
    sscanf(input_str, "%d %d", &input_num_a, &input_num_b);
    
    if(!check_input_value_in_range(input_num_a) 
       || !check_input_value_in_range(input_num_b))
    {
        ret = -1;
        return ret;
    }
    
    max_number = (input_num_a > input_num_b) ? input_num_a : input_num_b;
    
    while(1)
    {
        if((max_number % input_num_a) == 0 
          && (max_number) % input_num_b == 0)
        {
            printf("%d\n", max_number);
            break;
        }
        max_number ++;
    }
    
    return ret;
}
