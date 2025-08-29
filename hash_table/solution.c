#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct var
{
    int val;
    char *name;
};

struct var vars[256];

unsigned char hashf(const char key[])
{
    char *it;
    unsigned char hash = 0;
    for (it = (char*) key; *it; it++)
        hash = hash * 3 + *it;
    return hash;
}

void hash_push(const char key[], int val)
{
    unsigned char index = hashf(key);
    for(char *ch = vars[index].name; ch != 0 && ch[0] != -1; )
    {
        index++;
        ch = vars[index].name;
    }

    vars[index].name = malloc(strlen(key + 1));
    strcpy(vars[index].name, key);
    vars[index].val = val;
}

void print_val(const char key[])
{
    unsigned char index = hashf(key);
    printf("Cash of %s is %d$\n", key, vars[index].val);
}


int main(int argc, char *argv[])
{
    hash_push("Elena", 500);
    hash_push("Eva", 200);
    hash_push("Sergey", 1000000);
    hash_push("Aleksandra", 400000);
    print_val("Aleksandra");

    return 0;
}

