#include <string.h>
#include "bigintNorm.h"
#include <stdlib.h>
#include <stdio.h>

uint_1024 *createBigInt(unsigned int inp)
{
    uint_1024 *s = initBigInt();
    s->data[0] = inp;

    return s;
}

uint_1024 *initBigInt()
{
    uint_1024 *s;
    s = malloc(sizeof(uint_1024));

    return s;
}

uint_1024 *sum(uint_1024 *inpF, uint_1024 *inpS)
{
    uint_1024 *s = initBigInt();
    long long buf = 0;
    for (int i = 0; i < INT_IN_STRUCT; i++)
    {
        buf += inpF->data[i] + inpS->data[i];
        s->data[i] = buf;
        buf = buf >> sizeof(unsigned int) * 8;
    }
    if (buf)
    {
        printf("OVERLOAD");
    }
    return s;
}

uint_1024 *minus(uint_1024 *inpF, uint_1024 *inpS)
{
    uint_1024 *s = initBigInt();
    signed long long buf = 0;
    int over = 0;
    for (int i = 0; i < INT_IN_STRUCT; i++)
    {

        buf = inpF->data[i] - inpS->data[i];
        if (over)
        {
            buf -= 1;
            over = 0;
        }
        if (buf < 0)
        {
            buf += 0xffffffff;
            over = 1;
        }
        s->data[i] = buf;
    }
    if (over)
    {
        printf("under minus");
    }
    return s;
}

uint_1024 *mul(uint_1024 *inpF, uint_1024 *inpS)
{
    uint_1024 *s = initBigInt();
    int buf = 0;
    for (int z = 0; z < INT_IN_STRUCT * sizeof(int) * 8; z++)
    {

        if (1 << z % INT_IN_STRUCT & inpS->data[z / sizeof(int) * 8])
        {
            printBigIntBinary(s);
            s = sum(s, sdvig(inpF, z));
            printBigIntBinary(s);
        }
    }
    return s;
}

uint_1024 *sdvig(uint_1024 *inp, int sddvig)
{
    uint_1024 *s = createBigInt(0);
    long long buf = 0;
    const int bitsInInt = 8 * sizeof(int);
    int intSdvig = sddvig / bitsInInt;
    int dopSdvig = sddvig - intSdvig * bitsInInt;
    for (int i = 0; i < INT_IN_STRUCT; i++)
    {
        buf = inp->data[i];
        // printf(" %d %d\n", buf << dopSdvig, buf >> (8 - dopSdvig));

        s->data[i + intSdvig] += buf << dopSdvig;
        if (i + intSdvig < INT_IN_STRUCT)
            s->data[i + intSdvig + 1] += buf >> (bitsInInt - dopSdvig);
    }
    // printBigIntBinary(s);
    return s;
}

void printBigInt(uint_1024 *s)
{
    uint_1024 *z = createBigInt(0);
    uint_1024 *zero = createBigInt(0);
    char otp[404];
    memset(otp, '\0', 404);
    do
    {
        long long trans_reg = 0;
        for (int i = INT_IN_STRUCT - 1; i >= 0; i--)
        {
            long long value = (long long)s->data[i] + trans_reg * 4294967296;
            z->data[i] = value / 10;
            trans_reg = value % 10;
        }
        otp[strlen(otp)] = trans_reg + '0';
        s = z;
    } while (memcmp(&s->data, &zero->data, sizeof(int) * INT_IN_STRUCT) != 0);
    for (int i = strlen(otp) - 1; i >= 0; i--)
        printf("%c", otp[i]);
    printf("\n");
}

void printBigIntBinary(uint_1024 *s)
{
    int started = 0;
    for (int z = INT_IN_STRUCT; z >= 0; z--)
    {
        for (int bit = sizeof(int) * 8 - 1; bit >= 0; bit--)
        {
            if (1 << bit & s->data[z])
            {
                started = 1;
                printf("1");
            }
            else if (started)
            {
                printf("0");
            }
        }
    }
    printf("\n");
}

uint_1024 *scanBigInt()
{
    char s[1000];
    scanf("%s", s);
    int len = strlen(s);
    uint_1024 *res = initBigInt(0);
    uint_1024 *ten = createBigInt(10);
    uint_1024 *power = createBigInt(1);
    fflush(stdout);
    for (int i = len - 1; i >= 0; i--)
    {
        res = sum(res, mul(createBigInt(s[i] - '0'), power));
        // printBigIntBinary(res);
        power = mul(power, ten);
    }
    return res;
}

int main(int argc, char const *argv[])
{
    // uint_1024 *d = createBigInt(5);
    // uint_1024 *dd = createBigInt(32);

    // uint_1024 *ddd = scanBigInt();
    uint_1024 *dd = createBigInt(1024 * 1024 * 1024 + 1);
    // // printBigIntBinary(mul(dd, dd));
    // printBigIntBinary(dd);
    // printBigInt(dd);
    printBigInt(dd);
    dd = mul(dd, dd);
    printBigIntBinary(dd);
    // printBigIntBinary(dd);
    return 0;
}
