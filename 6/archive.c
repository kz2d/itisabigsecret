#include "archive.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ARCHIVE *createArchive(int fileCount, char *fileNames[], char *outputFile)
{
    ARCHIVE *archive;
    archive = malloc(sizeof(ARCHIVE));
    archive->fileCount = fileCount;
    for (int i = 0; i < fileCount; i++)
    {
        archive->fileNames[i] = fileNames[i];
    }
    char *outFile;
    outFile = malloc(strlen(outputFile) + 5);
    sprintf(outFile, "%s.arc", outputFile);
    archive->outputFile = outFile;
    printf("%s\n", outFile);
    return archive;
}

void makeArchive(ARCHIVE *archive)
{
    FILE *output = fopen(archive->outputFile, "wb");
    fwrite(&archive->fileCount, sizeof(int), 1, output);
    for (int i = 0; i < archive->fileCount; i++)
    {
        int z = strlen(archive->fileNames[i]);
        fwrite(&z, sizeof(int), 1, output);
        fwrite(archive->fileNames[i], sizeof(char) * z, 1, output);
    }

    for (int i = 0; i < archive->fileCount; i++)
    {
        printf("dsd");
        fflush(stdout);
        FILE *tempfile = fopen(archive->fileNames[i], "rb");
        long sizeOfFile;
        fseek(tempfile, 0, SEEK_END);
        sizeOfFile = ftell(tempfile);
        printf("size=%d\n", sizeOfFile);
        fwrite(&sizeOfFile, sizeof(long), 1, output);
        fseek(tempfile, 0, SEEK_SET);
        char ch;
        while (sizeOfFile > 0)
        {
            sizeOfFile -= 1;
            ch = fgetc(tempfile);
            fputc(ch, output);
        }
        fclose(tempfile);
    }

    fclose(output);
}

void printArchive(ARCHIVE *archive)
{
    printf("%d\n", archive->fileCount);
    printf("%s\n", archive->outputFile);
    for (int i = 0; i < archive->fileCount; i++)
    {
        printf("%d - %s\n", i, archive->fileNames[i]);
    }
}