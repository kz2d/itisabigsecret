#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct settings_struct
{
    int EXTRACT;
    int LIST;
    int CREATE;
    int fileCount;
    char *fileNames[100];
    char *inputFile;
} SETTINGS;

SETTINGS *createSettings(int argc, char **argv);
void printSettings(SETTINGS *settings);

#endif