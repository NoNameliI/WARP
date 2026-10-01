#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/sysinfo.h>

static const char ALPHABET[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!@#$%^&*()-_=+[]{};:,.<>/?";


static const char SIMVOL[] =
    "!@#$%^&*()-_=+[]{};:,.<>/?";

double sin_sum(unsigned long long mem, unsigned long long seed) {
    double sum = sin(mem) + sin(seed);
    double raw = sum * 98123.1237;
    if (raw < 0) {
        raw = -raw;
    }
    return raw;
}

unsigned long long get_ns_seed(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned long long)ts.tv_nsec;
}

int main() {
    int n;
    printf("Введите способ генерации случайного числа (1 - rand, 2 - мой): ");
    scanf("%d", &n);
    if (n == 1) {
        printf("Вы выбрали генерацию случайного числа с помощью rand().\n");
        srand(time(NULL));
        printf("Ваш пароль: ");
        for (int i = 0; i < 15; i++) {
            int index = rand() % (sizeof(ALPHABET) - 1);
            char randomChar = ALPHABET[index];
            printf("%c", randomChar);

        }
        int index = rand() % (sizeof(SIMVOL) - 1);
        char randomChar = SIMVOL[index];
        printf("%c", randomChar);
    printf("\n");
    } else if (n == 2) {
        struct sysinfo si;
        sysinfo(&si);
        printf("Вы выбрали генерацию случайного числа с помощью моего метода.\n");
        unsigned long long free_ram = (unsigned long long)si.freeram;
        printf("Ваш пароль: ");
        for (int i = 0; i < 15; i++) {
            unsigned long long seed = get_ns_seed();
            double randomDouble = sin_sum(free_ram, seed);
            int index = ((int)randomDouble % (sizeof(ALPHABET) - 1));
            char randomChar = ALPHABET[index];
            printf("%c", randomChar);
        }
        unsigned long long seed = get_ns_seed();
        double randomDouble = sin_sum(free_ram, seed);
        int index = ((int)randomDouble % (sizeof(ALPHABET) - 1));
        char randomChar = SIMVOL[index];
        printf("%c\n", randomChar);      
        printf("Shapes2\n");
    } else {
        printf("Неверный выбор. Пожалуйста, выберите 1 или 2.\n");
    }
    return 0;
}