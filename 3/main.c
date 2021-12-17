#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "vector.h"
#include <time.h>

int calculateTime(char *log)
{
    struct tm tm;
    char *ptr = 1 + strstr(log, "[");
    char d[21];
    strncat(d, ptr, 20);
    strptime(d, "%d/%b/%Y:%H:%M:%S", &tm);
    return mktime(&tm);
}

int main(int argc, char *argv[])
{

    printf("%s\n", argv[argc - 1]);
    fflush(stdout);
    VECTOR *vector = createVector(50);
    char *fileName = argv[argc - 1];
    FILE *opendFile = fopen(fileName, "r");
    if (opendFile == NULL)
    {
        printf("Oops");
        exit(10);
    }
    printf("%c", fgetc(opendFile));
    fflush(stdout);
    int lineSize = 1;
    char *line = malloc(sizeof(char) * lineSize);
    int lastComma = 0;
    char ch;
    int iter = 0;
    int windowSize = atoi(argv[1]);
    int lines = 0;
    int maxItemsInWindow = 0;
    int startOfWindow = 0;
    int endOfWindow = 0;
    while ((ch = (char)fgetc(opendFile)) != EOF)
    {
        line[iter] = ch;
        if (iter >= lineSize - 1)
        {
            lineSize *= 2;
            char *buffer = malloc(lineSize * sizeof(char));
            strcpy(buffer, line);
            free(line);
            line = buffer;
        }
        if (ch == '\n')
        {
            line[iter + 1] = '\0';
            lines++;
            if (line[lastComma + 2] == '5')
            {
                printf("%s\n", line);
            }
            fflush(stdout);

            int time = calculateTime(line);
            while (len(vector) > 0 && (vector->data[vector->start] + windowSize < time || vector->data[vector->start] > time))
            {
                popVector(vector);
            }

            vector = pushToVector(vector, time);

            if (len(vector) > maxItemsInWindow)
            {
                maxItemsInWindow = len(vector);
                startOfWindow = vector->data[vector->start];
                endOfWindow = vector->data[vector->end - 1];
            }
            iter = -1;
        }
        if (ch == '\"')
            lastComma = iter;
        iter++;
    }
    time_t epoch = startOfWindow;
    time_t epochTwo = endOfWindow;
    printf("maximum items in window = %d\n", maxItemsInWindow);
    printf("start items in window = %s\n", ctime(&epoch));
    printf("end items in window = %s\n", ctime(&epochTwo));
    fclose(opendFile);
    return 0;
}