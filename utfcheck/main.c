#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] ="абвabc";
    unsigned long len = strlen(str);
    unsigned long iter; 
    printf("length of %s is %lu\n", str, len);
    for(iter=0; iter<len; iter++)
        printf("%c ",str[iter]);
        // printf("0x%x ",str[iter]);
    printf("\n");
}
