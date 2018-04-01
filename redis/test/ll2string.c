/*************************************************************************
 > File Name: test.c
 > Author: qinchao
 > Mail: 1187620726@qq.com
 > Created Date:2018-03-17 Time:11:15:27.
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LLONG_MAX __LONG_LONG_MAX__

#define LLONG_MIN (-__LONG_LONG_MAX__ - 1LL)

#define ULLONG_MAX (__LONG_LONG_MAX__ * 2ULL + 1ULL)

typedef int int32_t;
typedef long int64_t;

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

int ll2string(char *dst, size_t dstlen, long long svalue);

void test_ll2string(void) {
  char buf[32];
  long long v;
  int sz;

  v = 0;
  sz = ll2string(buf, sizeof buf, v);
  printf("0: %s\n", buf);
  assert(sz == 1);
  assert(!strcmp(buf, "0"));

  v = -1;
  sz = ll2string(buf, sizeof buf, v);
  printf("-1: %s\n", buf);
  assert(sz == 2);
  assert(!strcmp(buf, "-1"));

  v = 99;
  sz = ll2string(buf, sizeof buf, v);
  printf("99: %s\n", buf);
  assert(sz == 2);
  assert(!strcmp(buf, "99"));

  v = -99;
  sz = ll2string(buf, sizeof buf, v);
  printf("-99: %s\n", buf);
  assert(sz == 3);
  assert(!strcmp(buf, "-99"));

  v = -2147483648;
  sz = ll2string(buf, sizeof buf, v);
  printf("-2147483648: %s\n", buf);
  assert(sz == 11);
  assert(!strcmp(buf, "-2147483648"));

  v = LLONG_MIN;
  sz = ll2string(buf, sizeof buf, v);
  printf("-9223372036854775808: %s\n", buf);
  assert(sz == 20);
  assert(!strcmp(buf, "-9223372036854775808"));

  v = LLONG_MAX;
  sz = ll2string(buf, sizeof buf, v);
  printf("9223372036854775807: %s\n", buf);
  assert(sz == 19);
  assert(!strcmp(buf, "9223372036854775807"));
}

uint32_t digits10(uint64_t v) {
  if (v < 10) return 1;
  if (v < 100) return 2;
  if (v < 1000) return 3;
  if (v < 1000000000000UL) {
    if (v < 100000000UL) {
      if (v < 1000000) {
        if (v < 10000) return 4;
        return 5 + (v >= 100000);
      }
      return 7 + (v >= 10000000UL);
    }
    if (v < 10000000000UL) {
      return 9 + (v >= 1000000000UL);
    }
    return 11 + (v >= 100000000000UL);
  }
  return 12 + digits10(v / 1000000000000UL);
}

int ll2string(char *dst, size_t dstlen, long long svalue) {
  static const char digits[201] =
      "0001020304050607080910111213141516171819"
      "2021222324252627282930313233343536373839"
      "4041424344454647484950515253545556575859"
      "6061626364656667686970717273747576777879"
      "8081828384858687888990919293949596979899";
  int negative;
  unsigned long long value;

  /* The main loop works with 64bit unsigned integers for simplicity, so
   * we convert the number here and remember if it is negative. */
  if (svalue < 0) {
    value =
        -svalue;  // mod1:  -svalue means (0 - svalue) ;see section [an example]
    negative = 1;
  } else {
    value = svalue;
    negative = 0;
  }

  /* Check length. */
  uint32_t const length = digits10(value) + negative;
  if (length >= dstlen) return 0;

  /* Null term. */
  uint32_t next = length;
  dst[next] = '\0';
  next--;
  while (value >= 10) {  // mod2
    int const i = (value % 100) * 2;
    value /= 100;
    dst[next] = digits[i + 1];
    dst[next - 1] = digits[i];
    next -= 2;
  }

  /* Handle last 1 digits. */
  if (value > 0 || length == 1) {  // mod3: value==0&&lengh= 1 means svalue=0;
    dst[next] = '0' + (uint32_t)value;
  }

  /* Add sign. */
  if (negative) dst[0] = '-';
  return length;
}

int main() { test_ll2string(); }
