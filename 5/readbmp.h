#ifndef READBMP_H
#define READBMP_H
typedef struct image_settings
{
    unsigned int width;
    unsigned int height;
    int stride;
    int fileSize;
    int widthInBytes;
    unsigned int bytesPerColor;
    unsigned int headerSize;
    unsigned int startOfImage;
    int paddingSize;
    unsigned char *data;
} IMAGE_INFO;

typedef struct game_of_life
{
    unsigned char *board;
    int width;
    int height;
} BOARD;

BOARD *readBitmapImage(char *imageFileName);

void readBitmapFileHeader(FILE *file, IMAGE_INFO *image);

void readBitmapInfoHeader(FILE *file, IMAGE_INFO *image);

#endif