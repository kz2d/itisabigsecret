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
    settings->maxIter = 0;
    settings->dumpFreq = 0;

    for (size_t i = 1; i < argc; i++)
    {
        printf("%s  ", argv[i]);
        printf("%d  ", strcmp(argv[i], "--input"));
        if (!strcmp(argv[i], "--input"))
        {
            i++;
            settings->inputFile = argv[i];
        }
        else if (!strcmp(argv[i], "--output"))
        {
            i++;
            settings->outputDir = argv[i];
        }
        else if (!strcmp(argv[i], "--max_iter"))
        {
            i++;
            settings->maxIter = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "--dump_freq"))
        {
            i++;
            settings->dumpFreq = atoi(argv[i]);
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
    printf("\ndumpFreq=%d\n", settings->dumpFreq);
    printf("inputFile=%s\n", settings->inputFile);
    printf("maxIter=%d\n", settings->maxIter);
    printf("outputDir=%s\n", settings->outputDir);
}