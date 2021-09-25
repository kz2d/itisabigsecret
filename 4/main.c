#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct FRAME_HEADER
{
    char id[4];
    int size;
    short int flag;
    char *content;
} FrameHeader;

FrameHeader *takeHeader(char data[10])
{
    FrameHeader *f;
    f = malloc(sizeof(FrameHeader));
    for (size_t i = 0; i < 4; i++)
    {
        f->id[i] = data[i];
    }
    f->size = data[7] + (data[6] << 8) + (data[5] << 16) + (data[4] << 24);
    f->flag = (data[8] << 8) + data[9];
    printf("id=%s\n", f->id);
    printf("%d\n", f->size);
    fflush(stdout);
    return f;
}

int main(int argc, char const *argv[])
{
    FILE *opendFile = fopen("examples_mp3_rheeeeet.mp3", "rb");
    if (opendFile == NULL)
    {
        printf("Error file missing\n");
        exit(-1);
    }
    char data[10];
    fread(data, sizeof(char), 10, opendFile);
    typedef struct something
    {
        char name[3];
        int veersion;
        char flag;
        int size;
    } ID3HEADER;
    ID3HEADER *d;
    d = malloc(sizeof(ID3HEADER));
    for (size_t i = 0; i < 3; i++)
        d->name[i] = data[i];
    d->veersion = data[3] + (data[4] << 8);
    d->flag = data[5];
    d->size = data[6] + (data[7] << 8) + (data[8] << 16) + (data[9] << 24);

    printf("%s\n", d->name);
    printf("%d\n", d->veersion);
    printf("%d\n", d->size);
    int size = d->size + 10;

    for (size_t i = 0; ftell(opendFile) < d->size; i++)
    {
        fread(data, sizeof(char), 10, opendFile);
        FrameHeader *f = takeHeader(data);
        char longData[f->size];
        fread(longData, sizeof(char), f->size, opendFile);
        printf("%s\n", longData);
        printf("%c", longData[2]);
        f->content = longData;
        if (strcmp(f->id, "TIT2") == 0)
        {
            printf("found\n");
        }
    }

    return 0;
}
