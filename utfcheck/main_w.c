#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

int main(void)
{
    setlocale(LC_ALL,"");
    wchar_t str[] =L"абвabc";
    unsigned long len = wcslen(str);
    unsigned long iter; 
    wprintf(L"length of %ls is %lu\n", str, len);
    for(iter=0; iter<len; iter++)
        wprintf(L"%lc ",str[iter]);
        // printf("0x%x ",str[iter]);
    printf("\n");
}
