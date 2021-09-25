#include "settings.h"
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main(int argc, char const *argv[])
// {
//     SETTINGS *s;
//     s = createSettings(argc, argv);
//     printSettings(s);
//     return 0;
// }

SETTINGS *createSettings(int argc, char *argv[])
{
    SETTINGS *settings;
    settings = malloc(sizeof(SETTINGS));

    for (size_t i = 1; i < argc; i++)
    {
        printf("%s  ", argv[i]);
        printf("%d  ", strcmp(argv[i], "--file"));
        if (!strcmp(argv[i], "--file"))
        {
            i++;
            settings->inputFile = argv[i];
        }
        else if (!strcmp(argv[i], "--create"))
        {
            settings->CREATE = 1;
        }
        else if (!strcmp(argv[i], "--extract"))
        {
            settings->EXTRACT = 1;
        }
        else if (!strcmp(argv[i], "--list"))
        {
            settings->LIST = 1;
        }
        else if (argv[i][0] != '-')
        {
            printf("%d\n", settings->fileCount);
            settings->fileNames[settings->fileCount] = argv[i];
            settings->fileCount++;
        }
        else
        {
            printf("invalid argv");
            exit(10);
        }
    }

    return settings;
}

void printSettings(SETTINGS *settings)
{
    printf("CREATE=%d\n", settings->CREATE);
    printf("EXTRACT=%d\n", settings->EXTRACT);
    printf("LIST=%d\n", settings->LIST);
    printf("input file=%d\n", settings->fileCount);

    for (size_t i = 0; i < settings->fileCount; i++)
    {
        printf("fileName=%s\n", settings->fileNames[i]);
    }
    printf("input file=%s\n", settings->inputFile);
}