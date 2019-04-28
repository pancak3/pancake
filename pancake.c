#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

int password_random();
int rand_int(int lower, int upper, int count);

int main()
{
    password_random();
    return 0;
}

int password_random()
{
    char martrix[255];
    int password_lenth = 19;
    char password[255];
    int i, rand_num, martrix_lenth;
    time_t t;

    srand((unsigned)time(&t));
    strcpy(martrix, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    martrix_lenth = strlen(martrix);
    for (i = 0; i < password_lenth; i++)
    {
        rand_num = rand_int(0, martrix_lenth - 1, 1);
        password[i] = martrix[rand_num];
    }

    printf("%s\r\n", password);

    return 0;
}

// src: https://www.geeksforgeeks.org/generating-random-number-range-c/
int rand_int(int lower, int upper, int count)
{
    int i, j, num, _rand_num = 1;

    for (i = 0; i < count; i++)
    {
        srand(time(NULL));
        for (j = 0; j < i; j++)
        {
            _rand_num += rand() % (upper - lower + 1) + lower;
        }
        
        num = rand() % (upper - lower + 1) + lower;
        printf("%d\r\n", _rand_num);
    }
    return num;
}