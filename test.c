#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *file = fopen("/home/kz2d/Downloads/c/5/main.c", "rb");
    if (file == NULL)
    {
        printf("lol");
        exit(2);
    }
    char buf[50];
    fread(buf, 1, 50, file);
    printf("%s", buf);
    return 0;
}
