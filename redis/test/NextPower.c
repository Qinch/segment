/*************************************************************************
 > File Name: test.c
 > Author: qinchao
 > Mail: 1187620726@qq.com
 > Created Date:2018-03-18 Time:12:28:44.
 ************************************************************************/
#include <stdio.h>

/* Our hash table capability is a power of two */
#define DICT_HT_INITIAL_SIZE 4
#define LONG_MAX 0x7FFFFFFF
static unsigned long _dictNextPower(unsigned long size) {
  unsigned long i = DICT_HT_INITIAL_SIZE;

  if (size >= LONG_MAX) return LONG_MAX + 1LU;
  while (1) {
    if (i >= size) return i;
    i *= 2;
  }
}
static unsigned long _dictNextPowerX(unsigned long size) {
  if (size <= DICT_HT_INITIAL_SIZE)
    return DICT_HT_INITIAL_SIZE;
  else if (size >= LONG_MAX)
    return LONG_MAX + 1LU;
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
int main() {
  unsigned long In = 0;
  for (; In <= LONG_MAX; In++) {
    unsigned long ret1 = _dictNextPower(In);
    unsigned long ret2 = _dictNextPowerX(In);
    if (ret1 != ret2) printf("bad optimition\n");
  }
}
