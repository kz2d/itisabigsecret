#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "vector.h"

int calculateTime(char *log, int day)
{
    // fflush(stdout);
    // printf("  line=%s     \n", log);

    char *index = strpbrk(log, ":") + 1;
    char buffer[4];
    strncpy(buffer, index, 3);
    buffer[3] = '\0';
    int time = atoi(buffer);

    index += 3;
    strncpy(buffer, index, 3);
    buffer[3] = '\0';
    time = time * 60 + atoi(buffer);
    // printf("ss=%d     \n", time);
    // printf("line = %s\n", log);
    time += day * 24 * 60;
    return time;
}

int main(int argc, char *argv[])
{

    printf("%s\n", argv[argc - 1]);
    VECTOR *vector = createVector();
    char *fileName = argv[argc - 1];
    FILE *opendFile = fopen("access_log_Jul95", "r");
    char line[1000];
    int lastComma = 0;
    char ch;
    int iter = 0;
    int windowSize = 2;
    int lines = 0;
    int day = 0;
    int maxItemsInWindow = 0;
    while ((ch = (char)fgetc(opendFile)) != EOF)
    {
        line[iter] = ch;
        if (ch == '\n')
        {
            line[iter + 1] = '\0';
            lines++;
            if (line[lastComma + 2] == '5')
            {
                char subbuff[iter + 1];
                memcpy(subbuff, &line, iter);
                subbuff[iter] = '\0';
                printf("%s\n", subbuff);
            }
            // printf("%d\n", lines);

            int time = calculateTime(line, day);
            if (time < vector->data[vector->end - 1])
            {
                day++;
                time = calculateTime(line, day);
            }
            // printf("%d\n", time);
            // if (len(vector) > 400)
            //     printVector(vector);

            while (len(vector) > 0 && (vector->data[vector->start] + windowSize < time || vector->data[vector->start] > time))
            {
                popVector(vector);
            }

            pushToVector(vector, time);

            if (len(vector) > maxItemsInWindow)
                maxItemsInWindow = len(vector);

            iter = -1;
        }
        if (ch == '\"')
            lastComma = iter;
        iter++;
    }
    printf("maximum items in window = %d\n", maxItemsInWindow);
    fclose(opendFile);
    return 0;
}