/*************************************************************************
 > File Name: fortest.c
 > Author: qinchao
 > Mail: 1187620726@qq.com
 > Created Date:2018-03-21 Time:06:47:47.
 ************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <time.h>

/* Our hash table capability is a power of two */
static unsigned long _dictNextPower(unsigned long size) {
    unsigned long prev;
    unsigned long iter = size;
    if (size >= LONG_MAX) return LONG_MAX + 1LU;
    while (iter) {
        prev = iter;
        iter = iter & (iter - 1);
    }
    return prev == size ? prev : prev << 1;
}

/* Our hash table capability is a power of two */
static unsigned long _dictNextPower2(unsigned long size) {
    unsigned long i = 4;

    if (size >= LONG_MAX) return LONG_MAX;
    while (1) {
        if (i >= size)
            return i;
        i *= 2;
    }
}


static unsigned long _dictNextPower3(unsigned long size) {
  if (size <= 4)
        return 4;
  else if (size >= LONG_MAX)
    return LONG_MAX + 1UL;
  else {
    --size;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size |= size >> 32;
    return size + 1;
  }
}

int main(void) {
    int start;
    int end;
    start = time((time_t *) NULL);
    for (int i = 0; i < 1000000000; ++i) {
        _dictNextPower2(i);
    }
    end = time((time_t *) NULL);
    printf("%d\n", end - start);

    start = time((time_t *) NULL);
    for (int j = 0; j < 1000000000; ++j) {
        _dictNextPower(j);
    }
    end = time((time_t *) NULL);
    printf("%d\n", end - start);

    start = time((time_t *) NULL);
    for (int j = 0; j < 1000000000; ++j) {
        _dictNextPower3(j);
    }
    end = time((time_t *) NULL);
    printf("%d\n", end - start);
    return 0;
}
