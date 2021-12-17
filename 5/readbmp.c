#include <stdio.h>
#include <stdlib.h>
#include "readbmp.h"

#define CELL_SIZE 1

BOARD *readBitmapImage(char *imageFileName);

void readBitmapFileHeader(FILE *file, IMAGE_INFO *image);

void readBitmapInfoHeader(FILE *file, IMAGE_INFO *image);

// int main(int argc, char const *argv[])
// {
//     printf("%d %d", 5, 8);
//     BOARD *b = readBitmapImage("new.bmp");

//     for (size_t i = 0; i < b->height; i++)
//     {
//         for (size_t z = 0; z < b->width; z++)
//         {
//             printf("%d ", b->board[i * b->height + z]);
//         }
//         printf("\n");
//     }

//     return 0;
// }

BOARD *readBitmapImage(char *imageFileName)
{

    FILE *imageFile = fopen(imageFileName, "rb");
    if (imageFile == NULL)
    {
        printf("open file error");
        exit(2);
    }
    IMAGE_INFO *image;
    image = malloc(sizeof(IMAGE_INFO));

    readBitmapFileHeader(imageFile, image);

    readBitmapInfoHeader(imageFile, image);
    if (!image->height || !image->width)
    {
        printf("cant read height or width\n");
        fflush(stdout);
        BOARD *b;
        b = malloc(sizeof(BOARD));
        b->height = 0;
        b->width = 0;
        return b;
    }
    image->widthInBytes = image->width * image->bytesPerColor;
    image->paddingSize = (4 - (image->widthInBytes) % 4) % 4;
    image->stride = (image->fileSize - image->startOfImage) / image->height;
    unsigned char d[image->height * image->stride];
    printf("stride =%d \n", image->stride);
    fflush(stdout);
    // d = malloc( sizeof(char)*(image->fileSize - image->startOfImage));
    fread(d, sizeof(char), image->fileSize - image->startOfImage, imageFile);
    image->data = d;
    image->width /= CELL_SIZE;
    image->height /= CELL_SIZE;
    printf("%d \n", image->data[13]);
    fflush(stdout);
    unsigned char *res;
    res = malloc(image->height * image->width * sizeof(char));
    int i;
    for (i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            // printf("lol=%d\n", image->data[(i * CELL_SIZE) * image->stride + (j * CELL_SIZE * image->bytesPerColor)]);
            if (image->data[(i * CELL_SIZE) * image->stride + (j * CELL_SIZE * image->bytesPerColor)] > 150)
            {
                res[i * image->height + j] = 0;
            }
            else
            {
                res[i * image->height + j] = 1;
            }
            printf("%d", res[i * image->height + j]);
        }
        printf("\n");
    }

    fclose(imageFile);
    printf("file closed\n");
    fflush(stdout);

    BOARD *b;
    b = malloc(sizeof(BOARD));
    b->board = res;
    b->height = image->height;
    b->width = image->width;
    // for (size_t i = 0; i < 3; i++)
    // {
    //     for (size_t z = 0; z < 3; z++)
    //     {
    //         printf("%d", b->board[i * 3 + z]);
    //     }
    //     printf("\n");
    // }
    return b;
}

void readBitmapFileHeader(FILE *file, IMAGE_INFO *image)
{
    // int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[10];
    fread(fileHeader, sizeof(char), 14, file);
    image->fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    image->startOfImage = fileHeader[10];
    printf("filesize=%d  startOfImage=%d\n", image->fileSize, image->startOfImage);
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%d ", fileHeader[i]);
    // }
    // fileHeader[0] = (unsigned char)('B');
    // fileHeader[1] = (unsigned char)('M');
    // fileHeader[2] = (unsigned char)(fileSize);
    // fileHeader[3] = (unsigned char)(fileSize >> 8);
    // fileHeader[4] = (unsigned char)(fileSize >> 16);
    // fileHeader[5] = (unsigned char)(fileSize >> 24);
    // fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
}

void readBitmapInfoHeader(FILE *file, IMAGE_INFO *image)
{
    static unsigned char infoHeader[] = {
        0, 0, 0, 0, // header size
        0, 0, 0, 0, // image width
        0, 0, 0, 0, // image height
        0, 0,       // number of color planes
        0, 0,       // bits per pixel
        0, 0, 0, 0, // compression
        0, 0, 0, 0, // image size
        0, 0, 0, 0, // horizontal resolution
        0, 0, 0, 0, // vertical resolution
        0, 0, 0, 0, // colors in color table
        0, 0, 0, 0, // important color count
    };
    fread(infoHeader, sizeof(char), image->startOfImage - 14, file);

    int width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
    int height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);

    image->headerSize = infoHeader[0] + (infoHeader[1] << 8) + (infoHeader[2] << 16) + (infoHeader[3] << 24);
    image->width = width;
    image->height = height;
    image->bytesPerColor = infoHeader[14] / 8;
    printf("width=%d  height=%d headerSize=%d bytesPerColor=%d\n", image->width, image->height, image->headerSize, image->bytesPerColor);

    // infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    // infoHeader[4] = (unsigned char)(width);
    // infoHeader[5] = (unsigned char)(width >> 8);
    // infoHeader[6] = (unsigned char)(width >> 16);
    // infoHeader[7] = (unsigned char)(width >> 24);
    // infoHeader[8] = (unsigned char)(height);
    // infoHeader[9] = (unsigned char)(height >> 8);
    // infoHeader[10] = (unsigned char)(height >> 16);
    // infoHeader[11] = (unsigned char)(height >> 24);
    // infoHeader[12] = (unsigned char)(1);
    // infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
}