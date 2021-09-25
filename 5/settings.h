#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct settings_struct
{
    int dumpFreq;
    int maxIter;
    char *outputDir;
    char *inputFile;
} SETTINGS;

SETTINGS *createSettings(int argc, char *argv[]);
void printSettings(SETTINGS *settings);

#endif