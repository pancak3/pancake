
#include "./include/config.h"

unsigned long int G_RAND_SEED = _RAND_SEED_VALUE;

int password_random();
int rand_int(int lower, int upper);
void seed_rand(long unsigned int seed);
long unsigned int pancake_rand();
int pan_mkdir(const char *s_path);

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

    char *noise_path;
    FILE *fp_noise = NULL;

#if OS_TYPE == OS_WIN32 | _OS_TYPE == OS_WIN64

    if (noise_path = getenv("APPDATA")))
        {
            strcat(noise_path, "\\pancake\\")
        }
    else
    {
        printf("Appdata path not found.");
        exit(-1);
    }

#elif _OS_TYPE == OS_LINUX | _OS_TYPE == OS_MAC_OS
    noise_path = getenv("HOME");
    strcat(noise_path, "/.pancake/");
#else
#error "unsupported system"
#endif

    if (access(noise_path, F_OK) != 0)
    {
        pan_mkdir(noise_path);
    }
    // put noise in
    strcat(noise_path, "pancake.noise");
    fp_noise = fopen(noise_path, "w+");
    fseek(fp_noise, 0, SEEK_SET);
    char noise_line[_MAX_NOISE_LINE];
    fgets(noise_line, _MAX_NOISE_LINE, fp_noise);
    if (strlen(noise_line) > 1)
    {
        long unsigned int noise_line_int = atoi(noise_line);
        G_RAND_SEED+=noise_line_int;
        G_RAND_SEED*=G_RAND_SEED;
    }
    fclose(fp_noise);

    // random begin

    strcpy(dictionary, _RANDOM_PASSWORD_DICTIONARY);
    dictionary_lenth = strlen(dictionary);
    for (i = 0; i < password_lenth; i++)
    {
        rand_num = rand_int(0, dictionary_lenth - 1);
        password[i] = dictionary[rand_num];
    }

    fp_noise = fopen(noise_path, "w");
    fseek(fp_noise, 0, SEEK_SET);
    fprintf(fp_noise, "%ld", G_RAND_SEED);
    fclose(fp_noise);

    printf("%s\r\n", password);

    return 0;
}

int rand_int(int lower, int upper)
{
    int num;

    num = pancake_rand() % (upper - lower + 1) + lower;
    return num;
}

void seed_rand(long unsigned int seed)
{
    G_RAND_SEED = seed;
}

long unsigned int pancake_rand()
{
    long unsigned int rand_num, noise_b, noise_c, noise_m, func_seed;

    func_seed = clock() * (G_RAND_SEED - 1);
    func_seed *= func_seed;
    rand_num = ((_NOISE_B * func_seed + _NOISE_C) % _NOISE_M);
    seed_rand(rand_num);

    return rand_num;
}

/*
https://sharp2wing.iteye.com/blog/1280802
*/

int pan_mkdir(const char *s_path)
{
    char dir_name[256];
    char separator[2];
#if OS_TYPE == OS_WIN32 | _OS_TYPE == OS_WIN64
    dir_name[0] = s_path[0];
    dir_name[1] = s_path[1];
    strcat(dir_name, "\\\\");
#elif _OS_TYPE == OS_LINUX | _OS_TYPE == OS_MAC_OS
    strcpy(dir_name, s_path);
#else
#error "unsupported system"
#endif
    // strcpy(dir_name, s_path);
    int i, len = strlen(s_path);
    for (i = 1; i < len; i++)
    {
        dir_name[i] = s_path[i];
#if _OS_TYPE == OS_LINUX | _OS_TYPE == OS_MAC_OS
        if (dir_name[i] == '/')
#elif OS_TYPE == OS_WIN32 | _OS_TYPE == OS_WIN64
        if (dir_name[i] == '\\')
#else
#error "unsupported system"
#endif
        {
            dir_name[i] = '\0';
            if (access(dir_name, F_OK) != 0)
            {
#if _OS_TYPE == OS_LINUX | _OS_TYPE == OS_MAC_OS

                if (mkdir(dir_name, 0755) == -1)
#elif OS_TYPE == OS_WIN32 | _OS_TYPE == OS_WIN64
                if (_mkdir(const char dir_name) == -1)
#else
#error "unsupported system"
#endif

                {
                    printf("mkdir error: %s\n", dir_name);
                    exit(-1);
                }
            }
#if _OS_TYPE == OS_LINUX | _OS_TYPE == OS_MAC_OS
            dir_name[i] = '/';
#elif OS_TYPE == OS_WIN32 | _OS_TYPE == OS_WIN64
            dir_name[i] = '\\';
            dir_name[i + 1] = '\\';
            i++;

#else
#error "unsupported system"
#endif
        }
    }
    return 1;
}
