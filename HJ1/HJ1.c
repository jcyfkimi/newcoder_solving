/* 运行时间：2ms 占用内存：344KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_STR_LEN         (5000)
#define MAX_READ_LEN        (128)

int main(int argc, char *argv[])
{
    char input_str[MAX_STR_LEN];
    char read_buf[MAX_READ_LEN];
    char *ptr;
    int str_len = 0;
    int rd_size = 0;
    int total_size = 0;
    
    
    memset(&input_str, 0, sizeof(input_str));
    memset(&read_buf, 0, sizeof(read_buf));
    
    while((rd_size = read(0, read_buf, MAX_READ_LEN)) != 0)
    {
        if(total_size + rd_size > MAX_STR_LEN)
        {
            // input size error, just return -1
            return -1;
        }
        // we have readed data from stdin
        strncpy(input_str+total_size, read_buf, rd_size);
        total_size += rd_size;
    }
    
    if(total_size > 0)
    {
        input_str[total_size - 1] = '\0';    // remove the \n at the end of string.
    }
    
    // check str length, range 0 - 5000
    str_len = strlen(input_str);
    if(str_len <= 0 || str_len > MAX_STR_LEN)
    {
        printf("sorry, input string invalid\n");
        return -1;
    }
    
    ptr = strrchr(input_str, ' ');
    if(NULL == ptr)
    {
        // No space in input string, just print out the length
        printf("%d\n", strlen(input_str));
    }
    else
    {
        printf("%d\n", strlen(ptr) - 1);
    }
    
    return 0;
}
