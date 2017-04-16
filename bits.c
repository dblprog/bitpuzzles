/*
 * CS:APP Data Lab
 *
 * David Lax
 * dlax@uchicago.edu
 * Jacob Burroughs
 * burroughsjw@uchicago.edu
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int Funct(arg1, arg2, ...) {
    /* brief description of how your implementation works */
    int var1 = Expr1;
    ...
    int varM = ExprM;

    varJ = ExprJ;
    ...
    varN = ExprN;
    return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
* pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
*/
int pow2plus1(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    int result = (1 << x);
    result += 4;
    return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.  This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc. Note that '=' is not
counted;
you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
    header comment for each function. If there are any inconsistencies
        between the maximum ops in the writeup and in this file, consider
        this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//#include "absVal.c"
//#include "addOK.c"
//#include "allEvenBits.c"
//#include "allOddBits.c"
//#include "anyEvenBit.c"


/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */

int anyOddBit(int x) {
    /* 
     * Similar to homework, this essentially creates a mask of 0xaaaaaaaa (1010 1010 ...) to see if any odd bits are set;
     * and'ing each byte of x with 0xaa, and then or'ing the results together will be 0 iff x had no odd bits set;
     * !! this gives the desired result (!!0) = 0, !!x for x =/= 0 gives 1.
     */
    return !!((x & 0xaa) | ((x >> 0x8) & 0xaa) | ((x >> 0x10) & 0xaa) | ((x >> (0x18) & 0xaa)));
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
    /* 
     * Splitting in half and or'ing preserves the presence of 1's/
     * Do this by setting x = x >> 16 (only concerned with 16 rightmost bits
     * Then recurse the halving and or'ing for x = x >> 8 (and 4,2,1). 
     * Finally, NOT(x) and & with 1 to return 1 iff x == 0 
     */
    x = (x >> 16) | x; 
    x = (x >> 8) | x;   
    x = (x >> 4) | x; 
    x = (x >> 2) | x;   
    x = (x >> 1) | x;   
    return ~x & 1;
}
//#include "bitAnd.c"
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    /* 
     * Masking half of x with 0x55555555 (0101 0101 ...) and then subtracting that from x preserves the number of even bits set.
     * Similarly, masking that result with 0x33333333 ( 0011 0011 ...) and adding that to a quarter of x masked similarly preserves the remaining bits.
     * We recurse this latter process, having ultimately condensed x's set bits 3 times; multiplying our result by 2^8 gives the count of the bits. 
     */
    int mask1, mask2, mask3, num;

    mask1 = (0x55 << 24) | (0x55 << 16) | (0x55 << 8) | 0x55;
    x = x + (~((x >> 1) & mask1) +1);

    mask2 = (0x33 << 24) | (0x33 << 16) | (0x33 << 8) | 0x33;
    x = (x & mask2) + ((x >> 2) & mask2);

    mask3 = (0xF << 24) | (0xF << 16) | (0xF << 8) | 0xF;
    num = ((x + (x >> 4)) & mask3);

    return (((num <<24) + (num << 16) + (num << 8) + num) >> 24);
}

/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
    /* 
     * mask1 creates 32-highbit 1's, followed by highbit 0's
     * mask2 creates 32-
     */
    int mask1, mask2, mask3;

    mask1 = ~0 << highbit;
    mask2 = ~(1 << highbit);
    mask1 = mask1 & mask2;
    mask3 = ~(~0 << lowbit);

    return ~(mask1 | mask3);
}


//#include "bitNor.c"
//#include "bitOr.c"
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    /* 
     * Splitting x in half and xor'ing preserves the oddness of 0's;
     * Do this by setting x to x ^(x >> 16) (then 8,4,2,1)
     * returning that and 1 gives 1 iff x had an odd number of 0's
     */
    x = (x >> 16) ^ x;
    x = (x >> 8) ^ x;
    x = (x >> 4) ^ x;
    x = (x >> 2) ^ x;
    x = (x >> 1) ^ x;
    return x & 1;
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
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    /* 
     * Shifts x n*2^3=8*n bits right, and then masks away all but the
     * LSB of the new number
     */
    return (x >> (n << 3)) & 0xFF;
}
//#include "greatestBitPos.c"
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /* 
     * We determine x's sign, and then set x to ~x if x is negative.
     * Then we shift x right by 16 and mask it with 0xFFFF,
     * bang this value, and multiply by 16 and if nonzero, add it to n.
     * We then recurse (with a slightly different mask) with 8 instead of 16, then 4,2,1.
     * This value n represents 33-numbits; solve for numbits (33 and not 32 because of signbit,
     * Which we chose not to worry about from our initial step.
     */

    int alt, sigx;
    int n, y, mask1;
    sigx = (x>>31 & 1);
    sigx = (sigx << 31) >> 31;
    alt = ~x;
    x = (sigx & alt) | (~sigx & x);

    n = 0;
    mask1 = 0xFF + (0xFF << 8);
    y = (x >> 16) & (mask1);
    n += (!y) << 4;
    x =  x >> ((!!y) << 4);

    y = (x >> 8) & (0xFF);
    n += (!y) << 3;
    x = x >> ((!!y) << 3);

    y = (x >> 4) & (0xF);
    n += (!y) << 2;
    x = x >> ((!!y) << 2);

    y = (x >> 2) & (0x3);
    n += (!y) << 1;
    x = x >> ((!!y) << 1);

    y = (x >> 1) & (0x1);
    n += (!y);
    x = x >> (!!y);

    y = (x) & (0x1);
    n += (!y);

    return 32 + (~n) + 1 + 1;
}
//#include "ilog2.c"
//#include "implication.c"
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /* 
     * Computes a = x -0x30 = x-48
     * Then computes b = (a+6)/16 (if x was less than 48, (x-54)/16 is nonzero)
     * and computes  c = a/16 (if x was greater than 57, a/16 is nonzero)
     * return true iff both of these values are 0
     */
    int a = x + (~0x30 +1);
    int b = (a + 6) >> 4;
    int c = a >> 4;

    return !b & !c ;
}
/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    /* 
     * xors the numbers, which will be 0 if they are the same and not 0
     * otherwise, and flips the answer
     */
    return !(x^y);
}

/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    /* 
     * Checks the signs of x, y, and x-y
     * Checks if x is negative, y is positive, and x-y is positive, in 
     * which case an "underflow" occured
     * Checks if x-y is positive or x is positive and y is negative
     * (catching an overflow) and the calculation didn't underflow
     * and x and y are different
     */
    int xneg = (x>>31 & 1);
    int yneg = (y>>31 & 1);
    int xyneg = (x + ~y + 1)>>31 & 1;
    int subok = !(xneg & !(yneg) & !(xyneg));
    return (subok & ((!xyneg) | ((!xneg) & (yneg)))  & !!(x ^ y));
}
//#include "isLess.c"
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /* 
     * Checks the signs of x, y, and x-y
     * Checks if x is negative, y is positive, and x-y is positive, in  
     * which case an "underflow" occured
     * Checks if x-y is positive or x is positive and y is negative
     * (catching an overflow) and the calculation didn't underflow
     * and x and y are different, and then flips the answer
     * (exactly the same as isGreater, but flipped) 
     */
    int xneg = (x>>31 & 1);
    int yneg = (y>>31 & 1);
    int xyneg = (x + ~y + 1)>>31 & 1;
    int subok = !(xneg & !(yneg) & !(xyneg));
    return !(subok & ((!xyneg) | ((!xneg) & (yneg)))  & !!(x ^ y));
}
//#include "isNegative.c"
/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
    /* 
     * Returns the inverse of the sign bit (which is on only for 
     * negative numbers)
     */
    return !(x>>31 & 1);
}
//#include "isNonZero.c"
/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
    /* 
     * if x equals y, x ^ y will be 0; if not, !(x^y) will be 0 so that !!(x^y) is 1
     */
    return !!(x^y);
}
//#include "isPositive.c"
//#include "isPower2.c"
//#include "isTmax.c"
//#include "isTmin.c"
//#include "isZero.c"
//#include "leastBitPos.c"
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
    /* 
     * Identical to bitCount, except we start from the left,
     * so that we can consolidate our count to the leftmost bits.
     */

    int n, y, mask1;
    x = ~x;
    n = 0;
    mask1 = 0xFF + (0xFF << 8);
    y = (x >> 16) & (mask1);
    n += (!y) << 4;
    x =  x >> ((!!y) << 4);

    y = (x >> 8) & (0xFF);
    n += (!y) << 3;
    x = x >> ((!!y) << 3);

    y = (x >> 4) & (0xF);
    n += (!y) << 2;
    x = x >> ((!!y) << 2);

    y = (x >> 2) & (0x3);
    n += (!y) << 1;
    x = x >> ((!!y) << 1);

    y = (x >> 1) & (0x1);
    n += (!y);
    x = x >> (!!y);

    y = (x) & (0x1);
    n += (!y);

    return n;
}
//#include "logicalNeg.c"
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
    /* 
     * Counts the number of bits to keep
     * Constructs a mask, like bitMask, to mask n left bits
     * Right-shifts x n bits and masks n leftmost bits
     */
    int mask1, mask2, highbit;
    highbit = (31+(~n)+1) &31;
    mask1 = ~0 << highbit;
    mask2 = ~(1 << highbit);
    mask1 = ~(mask1 & mask2);
    return ((x >> n) & mask1);
}
//  return ((x >> n) & ((32+(~n)+1);

//#include "minusOne.c"
//#include "multFiveEighths.c"
//#include "negate.c"
//#include "oddBits.c"
/*
 * rempwr2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) {
    /* 
     * posrem is x if x is positive;
     * then we check if x is nonzero.
     * if so, negrem is simply posrem -2^n
     * we set notzero and sigx so that 
     * we preserve the sign if it should be negative.  
     * we then return that result.
     */
    int posrem, negrem, sigx, notzero;
    sigx = (x>>31 & 1);
    posrem = x + ~((x >> n) << n) + 1;
    sigx = (sigx << 31) >> 31;
    notzero = !(!(posrem));
    notzero = (notzero << 31) >> 31;
    negrem = posrem + ((~(1 << n) + 1) & sigx & notzero);

    return negrem;
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
    /* 
     * Shifts c n bytes left
     * Masks out the nth byte of x
     * Combines shifted c with masked x
     */
    int mask = c << (n<<3);
    int x2 = x & ~(0xFF << (n<<3));

    return x2 | mask;
}
//#include "reverseBytes.c"
//#include "rotateLeft.c"
/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n) {
    /* 
     * Shifts x right n units and masks n bits on the left
     * Shifts x left until n original bits remain
     * Combines these components
     */
    int diff = (32 + (~n +1)) & 0x1F;
    int var1 = (x >> n) & ~(~0<<diff);
    int var2 = (x << diff);
    return var1 | var2;
}
//#include "satAdd.c"
//#include "satMul2.c"
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */

int satMul3(int x) {
    /* 
     * Checks sign of x, x + x, and x + x + x
     * Masks sum if these signs are not equal, replaced with TMax/TMin
     * Otherwise returns triple sum (i.e. product)
     */
    int sigx = (x>>31 & 1);
    int suma = x + x;
    int siga = (suma>>31 & 1);
    int sumb = suma + x;
    int sigb = (sumb>>31 & 1);
    int sigbad = ((((sigx ^ siga) | (sigx ^ sigb)) << 31) >> 31);
    int min_int = 1 << 31;
    sigx = (sigx << 31) >> 31;
    return (sumb & ~sigbad) | (sigbad & ((~sigx & (~min_int))|(sigx & min_int)));
}
//#include "sign.c"
//#include "sm2tc.c"
/*
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    /* 
     * Checks sign bit of x, y, and computed x+y
     * Overflow occurs if x>=0, y<0, and x+y<0 or
     * x<0, y>=0, x+y>=0
     */
    int xneg = (x>>31 & 1);
    int yneg = (y>>31 & 1);
    int xyneg = (x + ~y + 1)>>31 & 1;
    return !(((!xneg) & yneg & xyneg) | (xneg & (!yneg) & (!xyneg)));
}
//#include "tc2sm.c"
//#include "thirdBits.c"
//#include "tmax.c"
//#include "tmin.c"
//#include "trueFiveEighths.c"
//#include "trueThreeFourths.c"
//#include "upperBits.c"
