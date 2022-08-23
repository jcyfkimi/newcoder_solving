/* 运行时间：3ms 占用内存：332KB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_CNT_LEN            (500)
#define MAX_INPUT_IV_PAIR_LEN        (25)


typedef struct index_value_pair{
    unsigned int index;
    unsigned int value;
}iv_pair;

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

int check_if_all_digi(char *str)
{
    char tmp_ch = 0;
    int index = 0;
    int ret = 0;
    
    if(NULL == str)
    {
        return ret;
    }
    
    // before loop, set ret to 1
    ret = 1;
    
    tmp_ch = str[index];
    while(0 != tmp_ch)
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

int check_input_iv_format(char *str)
{
    // the input format is: xxxx yyyy, x, y needs to be all digi, and there's a
    // space character, and only 1 space can be exist
    char tmp_ch = 0;
    int index = 0;
    int space_count = 0;
    int ret = 0;
    
    if(NULL == str)
    {
        return ret;
    }
    
    // before loop, set ret to 1
    ret = 1;
    
    tmp_ch = str[index];
    
    while(tmp_ch != 0)
    {
        if(!check_char_is_digi(tmp_ch))
        {
            // check if it's a space
            if(!check_char_is_space(tmp_ch))
            {
                // input string contains non space and non digi
                ret = 0;
                break;
            }
            else
            {
                space_count++;
            }
        }
        if(space_count > 1)
        {
            // more than 1 space existed
            ret = 0;
            break;
        }
        
        index ++;
        tmp_ch = str[index];
    }
    
    return ret;
}

int combine_and_sort_iv_pair(iv_pair *pair, int count)
{
    int ret = 0;
    int i = 0;
    int j = 0;
    iv_pair tmp_pair;
    
    // combine iv pair
    for(i = 0; i < count - 1; i++)
    {
        for(j = i + 1; j < count; j++)
        {
            if(pair[j].value == 0)
            {
                // It's already combined, skip this pair
                continue;
            }
            if(pair[i].index == pair[j].index)
            {
                pair[i].value += pair[j].value;
                pair[j].value = 0;        // change the combined value to 0
            }
        }
    }
    
    // Sorting
    for(i = 0; i < count -1; i++)
    {
        for(j = i + 1; j < count; j++)
        {
            if(pair[j].value == 0)
            {
                continue;
            }
            
            if(pair[i].index > pair[j].index)
            {
                memset(&tmp_pair, 0, sizeof(tmp_pair));
                memcpy(&tmp_pair, &pair[i], sizeof(iv_pair));
                memcpy(&pair[i], &pair[j], sizeof(iv_pair));
                memcpy(&pair[j], &tmp_pair, sizeof(iv_pair));
            }
            
        }
    }
    
    // print
    for(i = 0; i < count; i++)
    {
        if(pair[i].value == 0)
        {
            continue;
        }
        printf("%d %d\n", pair[i].index, pair[i].value);
    }
    
    return ret;
}



int main(int argc, char *argv[])
{
    char input_cnt[MAX_INPUT_CNT_LEN + 2];
    char input_iv_pair[MAX_INPUT_IV_PAIR_LEN + 2];
    int ret = 0;
    int input_count = 0;
    int readed_count = 0;
    iv_pair input_pair[MAX_INPUT_CNT_LEN];
    
    
    memset(&input_cnt, 0, sizeof(input_cnt));
    memset(&input_iv_pair, 0, sizeof(input_iv_pair));
    
    // Reading the count
    if(fgets(input_cnt, MAX_INPUT_CNT_LEN + 2, stdin) != NULL)
    {
        input_cnt[strlen(input_cnt) - 1] = '\0';
    }
    
    if(!check_if_all_digi(input_cnt))
    {
        // input count contains non digi
        ret = -1;
        return ret;
    }
    input_count = atoi(input_cnt);
    
    memset(&input_pair, 0, sizeof(input_pair));

    // Reading the input key pair
    while(fgets(input_iv_pair, MAX_INPUT_IV_PAIR_LEN + 2, stdin) != NULL)
    {
        readed_count++;
        if(readed_count > input_count)
        {
            // input error
            ret = -1;
            break;
        }
        
        input_iv_pair[strlen(input_iv_pair) - 1] = '\0';

        if(!check_input_iv_format(input_iv_pair))
        {
            // check format failed
            ret = -1;
            break;
        }
        sscanf(input_iv_pair, "%d %d", &input_pair[readed_count - 1].index, &input_pair[readed_count - 1].value);
        
        // check input index and value range
        if(!(input_pair[readed_count - 1].index >= 0 && input_pair[readed_count - 1].index <= 11111111) 
           || !(input_pair[readed_count - 1].value >= 1 && input_pair[readed_count - 1].value <= 100000))
        {
            ret = -1;
            break;
        }
        
        memset(&input_iv_pair, 0, sizeof(input_iv_pair));
        
    }
    
    ret = combine_and_sort_iv_pair(&input_pair, input_count);
    
    return ret;
}

