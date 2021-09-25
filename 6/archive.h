#ifndef ARCHIVE_H
#define ARCHIVE_H

typedef struct archive_struct
{
    int fileCount;
    char *fileNames[100];
    char *outputFile;
} ARCHIVE;

ARCHIVE *createArchive(int fileCount, char **fileNames, char *outputFile);
void printArchive(ARCHIVE *archive);
void makeArchive(ARCHIVE *archive);

#endif