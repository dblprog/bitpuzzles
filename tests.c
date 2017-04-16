/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

//#include "absVal.c"
//#include "addOK.c"
//#include "allEvenBits.c"
//#include "allOddBits.c"
//#include "anyEvenBit.c"
int test_anyOddBit(int x) {
    int i;
    for (i = 1; i < 32; i+=2)
        if (x & (1<<i))
      return 1;
    return 0;
}
int test_bang(int x)
{
  return !x;
}
//#include "bitAnd.c"
int test_bitCount(int x) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result += (x >> i) & 0x1;
  return result;
}







int test_bitMask(int highbit, int lowbit)
{
  int result = 0;
  int i;
  for (i = lowbit; i <= highbit; i++)
    result |= 1 << i;
  return result;
}
//#include "bitNor.c"
//#include "bitOr.c"
int test_bitParity(int x) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result ^= (x >> i) & 0x1;
  return result;
}
//#include "bitXor.c"
//#include "byteSwap.c"
//#include "conditional.c"
//#include "copyLSB.c"
//#include "divpwr2.c"
//#include "evenBits.c"
//#include "ezThreeFourths.c"
//#include "fitsBits.c"
//#include "fitsShort.c"
//#include "float_abs.c"
//#include "float_f2i.c"
//#include "float_half.c"
//#include "float_i2f.c"
//#include "float_neg.c"
//#include "float_twice.c"
int test_getByte(int x, int n)
{
    unsigned char byte;
    switch(n) {
    case 0:
      byte = x;
      break;
    case 1:
      byte = x >> 8;
      break;
    case 2:
      byte = x >> 16;
      break;
    default:
      byte = x >> 24;
      break;
    }
    return (int) (unsigned) byte;
}
//#include "greatestBitPos.c"
int test_howManyBits(int x) {
    unsigned int a, cnt;
    x = x<0 ? -x-1 : x;
    a = (unsigned int)x;
    for (cnt=0; a; a>>=1, cnt++)
        ;
    return (int)(cnt + 1);
}
//#include "ilog2.c"
//#include "implication.c"
int test_isAsciiDigit(int x) {
  return (0x30 <= x) && (x <= 0x39);
}
int test_isEqual(int x, int y)
{
  return x == y;
}
int test_isGreater(int x, int y)
{
  return x > y;
}
//#include "isLess.c"
int test_isLessOrEqual(int x, int y)
{
  return x <= y;
}
//#include "isNegative.c"
int test_isNonNegative(int x) {
  return x >= 0;
}
//#include "isNonZero.c"
int test_isNotEqual(int x, int y)
{
  return x != y;
}
//#include "isPositive.c"
//#include "isPower2.c"
//#include "isTmax.c"
//#include "isTmin.c"
//#include "isZero.c"
//#include "leastBitPos.c"
int test_leftBitCount(int x) {
  int result = 0;
  int i;
  for (i = 31; i >= 0; i--) {
      int bit = (x >> i) & 0x1;
      if (!bit)
   break;
      result ++;
  }
  return result;
}
//#include "logicalNeg.c"
int test_logicalShift(int x, int n) {
  unsigned u = (unsigned) x;
  unsigned shifted = u >> n;
  return (int) shifted;
}
//#include "minusOne.c"
//#include "multFiveEighths.c"
//#include "negate.c"
//#include "oddBits.c"
int test_rempwr2(int x, int n)
{
    int p2n = 1<<n;
    return x%p2n;
}
int test_replaceByte(int x, int n, int c)
{
    switch(n) {
    case 0:
      x = (x & 0xFFFFFF00) | c;
      break;
    case 1:
      x = (x & 0xFFFF00FF) | (c << 8);
      break;
    case 2:
      x = (x & 0xFF00FFFF) | (c << 16);
      break;
    default:
      x = (x & 0x00FFFFFF) | (c << 24);
      break;
    }
    return x;
}
//#include "reverseBytes.c"
//#include "rotateLeft.c"
int test_rotateRight(int x, int n) {
  unsigned u = (unsigned) x;
  int i;
  for (i = 0; i < n; i++) {
      unsigned lsb = (u & 1) << 31;
      unsigned rest = u >> 1;
      u = lsb | rest;
  }
  return (int) u;
}
//#include "satAdd.c"
//#include "satMul2.c"
int test_satMul3(int x)
{
  if ((x+x+x)/3 != x)
    return x < 0 ? 0x80000000 : 0x7FFFFFFF;
  else
    return 3*x;
}
//#include "sign.c"
//#include "sm2tc.c"
int test_subOK(int x, int y)
{
  long long ldiff = (long long) x - y;
  return ldiff == (int) ldiff;
}
//#include "tc2sm.c"
//#include "thirdBits.c"
//#include "tmax.c"
//#include "tmin.c"
//#include "trueFiveEighths.c"
//#include "trueThreeFourths.c"
//#include "upperBits.c"
