#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

double rand_double() {
    return (double)(rand() * 2.0) / (double) RAND_MAX - 1.0;
}

void new_seed() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec * 1000000 + tv.tv_usec);
}
