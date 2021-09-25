#ifndef UNARCHIVE_H
#define UNARCHIVE_H

typedef struct unarchive_struct
{
    int fileCount;
    char *inputFile;
} UNARCHIVE;

UNARCHIVE *createUnarchive(char *outputFile);

void unmakeArchive(UNARCHIVE *Unarchive);
void list(UNARCHIVE *Unarchive);
void printUnarchive(UNARCHIVE *Unarchive);

#endif