/* 运行时间：3ms 占用内存：328KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    // This code did not consider invalid input
    // ex: input is f.500
    float input_float;
    
    scanf("%f", &input_float);
    
    printf("%d", (int)(input_float + 0.5));
}