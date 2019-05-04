#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "./include/config.h"

static unsigned long int rand_seed = _RAND_SEED_VALUE;

int password_random();
int rand_int(int lower, int upper);
void seed_rand(long unsigned int seed);

int main()
{
    password_random();
    return 0;
}

int password_random()
{
    char dictionary[255];
    char password[255];
    int i, rand_num, dictionary_lenth, password_lenth = _DEFAULT_PASSWORD_LENGTH;

    strcpy(dictionary, _RANDOM_PASSWORD_DICTIONARY);
    dictionary_lenth = strlen(dictionary);
    for (i = 0; i < password_lenth; i++)
    {
        rand_num = rand_int(0, dictionary_lenth - 1);
        password[i] = dictionary[rand_num];
    }

    printf("%s\r\n", password);

    return 0;
}

int rand_int(int lower, int upper)
{
    int i, j, num;
    long unsigned int rand_num;
    long func_seed;

    func_seed = clock();
    rand_num = func_seed * rand_seed + func_seed * (func_seed & _FUNC_SEED_MASK) - rand_seed % (rand_seed & _RAND_SEED_MASK);
    seed_rand(rand_num);

    num = rand_num % (upper - lower + 1) + lower;
    return num;
}
void seed_rand(long unsigned int seed)
{
    rand_seed = seed;
}