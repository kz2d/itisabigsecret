#include "unarchive.h"
#include <stdlib.h>
#include <stdio.h>

UNARCHIVE *createUnarchive(char *outputFile)
{
    UNARCHIVE *Unarchive;
    Unarchive = malloc(sizeof(UNARCHIVE));
    // for (int i = 0; i < fileCount; i++)
    // {
    //     Unarchive->fileNames[i] = fileNames[i];
    // }

    Unarchive->inputFile = outputFile;
    return Unarchive;
}

void unmakeArchive(UNARCHIVE *Unarchive)
{
    FILE *output = fopen(Unarchive->inputFile, "rb");
    int fileCount;
    fread(&fileCount, sizeof(int), 1, output);
    printf("i=%d\n", fileCount);
    char *filesNames[fileCount];
    for (int i = 0; i < fileCount; i++)
    {
        int z;
        fread(&z, sizeof(int), 1, output);
        printf("index=%d , \n", z);

        char *s;
        s = calloc(z, sizeof(char));
        fread(s, sizeof(char), 1 * z, output);
        printf("index=%d , name=%s\n", z, s);
        filesNames[i] = s;
    }
    for (int i = 0; i < fileCount; i++)
    {
        FILE *tempfile = fopen(filesNames[i], "w");
        long sizeOfFile;
        fread(&sizeOfFile, sizeof(long), 1, output);
        char ch;
        while (sizeOfFile != 0)
        {

            sizeOfFile--;
            fread(&ch, sizeof(char), 1, output);
            printf("%d  %d\n", sizeOfFile, ch);

            fputc(ch, tempfile);
        }
        fclose(tempfile);
    }

    fclose(output);
}

void list(UNARCHIVE *Unarchive)
{
    FILE *output = fopen(Unarchive->inputFile, "rb");
    int fileCount;
    fread(&fileCount, sizeof(int), 1, output);
    printf("i=%d\n", fileCount);
    char *filesNames[fileCount];
    for (int i = 0; i < fileCount; i++)
    {
        int z;
        fread(&z, sizeof(int), 1, output);
        printf("index=%d , \n", z);

        char *s;
        s = calloc(z, sizeof(char));
        fread(s, sizeof(char), 1 * z, output);
        printf("index=%d , name=%s\n", z, s);
        filesNames[i] = s;
    }

    fclose(output);
}

void printUnarchive(UNARCHIVE *Unarchive)
{
    printf("%d\n", Unarchive->fileCount);
}