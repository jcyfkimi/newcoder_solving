/* 运行时间：4ms 占用内存：348KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_STR_LEN            (1000)

int check_char_is_valid(char ch, char min, char max)
{
    int ret = 0;
    
    if(ch >= min && ch <= max)
    {
        // Only valid in range [min, max]
        ret = 1;
    }
    
    return ret;
}

int check_is_digi(char ch)
{
    return check_char_is_valid(ch, '0', '9');
}

int check_is_lowercase_char(char ch)
{
    return check_char_is_valid(ch, 'a', 'z');
}

int check_is_uppercase_char(char ch)
{
    return check_char_is_valid(ch, 'A', 'Z');
}

int check_is_space_char(char ch)
{
    return (ch == ' ')? 1 : 0;
}

// return 0 means not valid
int check_if_str_valid(char *str)
{
    int index = 0;
    char tmp_ch = str[index];
    
    while(tmp_ch != 0)
    {
        if(check_is_digi(tmp_ch) 
           || check_is_lowercase_char(tmp_ch) 
           || check_is_uppercase_char(tmp_ch) 
           || check_is_space_char(tmp_ch) )
        {
            // It's valid character, go next cycle;
            index ++;
            tmp_ch = str[index];
        }
        else
        {
            // Got a invalid character, just return -1
            return 0;
        }
    }
    
    return 1;
}

// return 0 means not valid
int check_if_single_char_valid(char tmp_ch)
{
    //printf("tmp_ch = %c, %d:%d:%d\n", tmp_ch, check_is_digi(tmp_ch) , check_is_lowercase_char(tmp_ch) , check_is_uppercase_char(tmp_ch));
    return check_is_digi(tmp_ch) 
           || check_is_lowercase_char(tmp_ch) 
           || check_is_uppercase_char(tmp_ch);
}

int do_count_character(char *str, char target_ch)
{
    int count = 0;
    int index = 0;
    int target_is_digi = 0;
    char tmp_str = str[index];
    
    if(check_is_digi(target_ch))
    {
        target_is_digi = 1;
    }
    else if(check_is_lowercase_char(target_ch))
    {
        // convert to uppercase
        target_ch -= 0x20;
    }
    
    while(tmp_str != 0)
    {
        if(target_is_digi)
        {
            if(check_is_digi(tmp_str))
            {
                if(target_ch == tmp_str)
                {
                    count ++;
                }
            }
            index ++;
            tmp_str = str[index];
            continue;
        }
        else
        {
            if(check_is_lowercase_char(tmp_str))
            {
                // convert to uppercase character
                tmp_str -= 0x20;
            }
            
            if(target_ch == tmp_str)
            {
                count++;
            }
            
            index ++;
            tmp_str = str[index];
            continue;
        }
    }
    
    return count;
}

int main(int argc, char *argv[])
{
    char input_str[MAX_INPUT_STR_LEN + 2];    // for fgets, need to consider \n and \0
    char target_ch = 0;
    int target_count = 0;
    
    memset(&input_str, 0, sizeof(input_str));
    
    // Get input strings
    if( fgets (input_str, MAX_INPUT_STR_LEN + 2, stdin)!=NULL )
    {
        input_str[strlen(input_str) - 1] = '\0';
    }

    // Get target ch
    scanf("%c", &target_ch);
    //printf("%c\n", target_ch);
    
    // Check if input string and target char valid
    if(!check_if_str_valid(input_str))
    {
        // Got a invalid character inside input str, just return -1
        return -1;
    }
    
    if(!check_if_single_char_valid(target_ch))
    {
        // Input target char invalid, just return -1
        return -1;
    }
    
    // count how many target character inside input string, did not care case
    target_count = do_count_character(input_str, target_ch);
    
    printf("%d\n", target_count);

    
    return 0;
}