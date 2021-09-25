#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bpc.h"
#include "readbmp.h"
#include "settings.h"

int main(int argc, char const *argv[])
{
    SETTINGS *s = createSettings(argc, argv);
    printSettings(s);
    BOARD *b = readBitmapImage(s->inputFile);
    unsigned char *res;
    int maxIter = 1000000000;
    if (s->maxIter > 0)
        maxIter = s->maxIter;
    if (s->dumpFreq == 0)
        s->dumpFreq = 1;
    for (int iter = 0; iter < 10; iter++)
    {
        res = malloc(b->height * b->width * sizeof(char));

        for (int y = 0; y < b->height; y++)
        {
            for (int x = 0; x < b->width; x++)
            {
                int prevX = x - 1;
                int prevY = y - 1;
                int nextX = x + 1;
                int nextY = y + 1;
                if (prevY == -1)
                    prevY = 0;
                if (prevX == -1)
                    prevX = 0;
                if (nextX == b->width)
                    nextX = 0;
                if (nextY == b->height)
                    nextY = 0;

                int buf = b->board[y * b->height + nextX] + b->board[y * b->height + prevX] +
                          b->board[prevY * b->height + nextX] + b->board[nextY * b->height + nextX] +
                          b->board[prevY * b->height + prevX] + b->board[nextY * b->height + prevX] +
                          b->board[prevY * b->height + x] + b->board[nextX * b->height + x];
                res[y * b->height + x] = 0;
                if (b->board[y * b->height + x])
                {
                    if (buf == 2 || buf == 3)
                        res[y * b->height + x] = 1;
                }
                else if (buf == 3)
                    res[y * b->height + x] = 1;
            }
        }

        b->board = res;
        printf("lol\n");
        if (1)
        {
            char dst[118];
            sprintf(dst, "/home/kz2d/Downloads/c/5/%s/lol%d.bmp\0", s->outputDir, iter);
            printf(dst);
            fflush(stdout);
            saveImage(b, dst);
        }
    }

    // printf("test\n");
    // for (size_t i = 0; i < b->height; i++)
    // {
    //     for (size_t z = 0; z < b->width; z++)
    //     {
    //         printf("%d ", b->board[i * b->height + z]);
    //     }
    //     printf("\n");
    // }

    return 0;
}
