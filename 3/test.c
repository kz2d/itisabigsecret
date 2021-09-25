#include "vector.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    VECTOR *vector = createVector();
    printVector(vector);
    pushToVector(vector, 5);
    pushToVector(vector, 6);
    pushToVector(vector, 7);
    printVector(vector);
    printf("lol=%d\n", popVector(vector));
    printVector(vector);
    vector->start = 98;
    vector->end = 98;
    for (int i = 0; i < 5; i++)
    {
        pushToVector(vector, i);
        printVector(vector);
    }
    int z = atoi("68 ");
    printf("lol=%d\n", atoi("054s"));

    printf("lol=%d\n", z);

    char *a = "205.189.154.54 - - [01/Jul/1995:01:02:06 -0400] \" GET / cgi - bin / imagemap / countdown ? 99, 176 HTTP / 1.0 \" 302 110";
    char *index = strpbrk(a, ":") + 1;
    char buffer[4];
    strncpy(buffer, index, 3);
    printf("%s\n", buffer);
    buffer[3] = '\0';
    int time = atoi(buffer);
    printf("ss=%d\n", time);

    index += 3;
    strncpy(buffer, index, 3);
    printf("%s\n", buffer);
    buffer[3] = '\0';
    time = time * 60 + atoi(buffer);
    printf("ss=%d\n", time);

    return 0;
}
