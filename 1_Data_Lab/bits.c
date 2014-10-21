/* 
 * CS:APP Data Lab 
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

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Team name: Replace with either:
      Your login ID if working as a one person team
      or, ID1+ID2 where ID1 is the login ID of the first team member
      and ID2 is the login ID of the second team member */
    "edzh3452+jkee", 
   /* Student name 1: Replace with the full name of first team member */
   "Edward Renxi Zhu",
   /* Login ID 1: Replace with the login ID of first team member */
   "edzh3452",

   /* The following should only be changed if there are two team members */
   /* Student name 2: Full name of the second team member */
   "Benjamin Kee",
   /* Login ID 2: Login ID of the second team member */
   "jkee"
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
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


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
//
// 15 problems, 40 points
// 2 - rating 1
// 3 - rating 2
// 7 - rating 3
// 3 - rating 4

// rating 1

/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {	
// or with 0 and if there are anything other than 0, it will bang out 0
  return !(x|0);

}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {	
// if both are complimented and or'ed the two, that will give 0 for all 
// numbers that should give both 1's, so compliment that
	return ~(~x|~y);
}
// rating 2
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
// shift left by 32-(n-bits) = if anything is left of it, then it will
// be deleted, then shift back and xor it with original to see any differences 
	return !(((x << (32+(~n+1)))>>(32+(~n+1)))^x);
} 
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {	
// multiply n by 8 because we have 32 bit system, then shift it left to
// get rid of lower numbers, then mask b so the last 8 bits are 0, and 
// xor a with b to get the desired byte
	int a = x >> (n<<3);
	int b = a >> 8 << 8;
	return a ^ b;
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {	
// xor shows any differences, so then just take the bang of the bang
  return !(!(x^y));
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {
// only using ~ and &, we and the x and compliment of y and then and the
// visa versa, then compliment that to see where there are differences
  return ~(~(x&~y) & ~(y&~x));
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
// right shift is always an arithmetic shift, so if we left shift 31,
// it will give the LSB and then right shift it all the way back
	int result = ((x << 31) >> 31);
	return result;
}
// rating 3
/* 
 * sum3 - x+y+z using only a single '+'
 *   Example: sum3(3, 4, 5) = 12
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 16
 *   Rating: 3
 */
/* A helper routine to perform the addition.  Don't change this code */
static int sum(int x, int y) {
  return x+y;
}
int sum3(int x, int y, int z) {
// word 1 shows the carries and pushes the carries over left by one
// and word 2 Xor's all of them together, which is addition without the carries
  int word1 = 0;
  int word2 = 0;
  /**************************************************************
     Fill in code below that computes values for word1 and word2
     without using any '+' operations 
  ***************************************************************/
	word1 = ( (x&y) | (y&z) | (x&z) ) << 1;
	word2 = x ^ y ^ z;
  /**************************************************************
     Don't change anything below here
  ***************************************************************/
  return sum(word1,word2);
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
// we mask every 8 bits so that a is the last 8 bits(LSB), and d is the
// first 8 bits (MSB) and same with everything in between, and we switch
// the ordering around to reverse the byte
	int a = x << 24;
	int bmask = (~(0xFF << 24) >> 16) << 16;
	int b = x << 8;
	int cmask = (~(0xFF << 24) >> 16) << 8; 
	int c = x >> 8;
	int dmask = (~(0xFF << 24) >> 16); 
	int d = x >> 24;
  return (a+(b&bmask) + (c&cmask) + (d&dmask));
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNegative(int x) {
// Because of twos compliment, if the first number is negative, then it
// is a negative number, so we bang bang the first number
  return !(!(x >> 31));
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
// we must take two tests, one for straight subtraction and another for
// checking if there is a sign difference, then the comparison with the 
// sign difference and the subtraction sign will show whether less or not
	int d = (x + (~y +1)) >> 31;
	int a;
	x = x >> 31;
	y = y >> 31;
	a = (x^y);
	a = (a&x)|(~a&d);
	return (a&1)|(~a&0);
}
// rating 4
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
// turn the number negative and then left shift x and a all the way to
// the right and and with 1, if it is 0, it will say zero, else 1
  int a = ~x + 1;
  return (a >> 31 | x >> 31) & 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {				
// we must make masks so that it counts by every other 1, two 1s every two 
// 0s, and then half 0 half 1s every 8 bits, and finally with 16 zeros and
// 16 1s, its similar to divide and conquer. Then we add our shifted number
// with the original or previously shifted number and compare that with
// the mask that we created in relationship according to the shift
  int mask1, mask2, mask3, mask4, mask5, a;
  mask1 = 0x55;
  mask1 = (mask1 << 8) + mask1;			//01010101
  mask1 = (mask1 << 16) + mask1; 		//0x55555555

  mask2 = 0x33;
  mask2 = (mask2 << 8) + mask2;			//00110011
  mask2 = (mask2 << 16) + mask2; 		//0x33333333

  mask3 = 0x0F;
  mask3 = (mask3 << 8) + mask3;			//00001111
  mask3 = (mask3 << 16) + mask3; 		//0x0F0F0F0F

  mask4 = (0xFF << 16) + 0xFF;	//0x00FF00FF = 00000000 11111111

  mask5 = (0xFF << 8) + 0xFF;  	//0x0000FFFF = 00000000 00000000 11111111 11111111

  a = x + ~((x >> 1) & mask1) + 1;
  a = ((a >> 2) & mask2) + (a & mask2);
  a = ((a >> 4) + a) & mask3;
  a = ((a >> 8) + a) & mask4;
  a = ((a >> 16) + a) & mask5;

  return a;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
// keep or-ing x with other half until you have one number left, if there 
// are any 1s then it will keep it, then at the end, take compliment and 
// and with one will give either 1 or 0
	x = (x>>16) | x;
	x = (x>>8) | x;
	x = (x>>4) | x;
	x = (x>>2) | x;
	x = (x>>1) | x;
	
	return ~x & 1;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
// very similar to bang, but instead of or-ing (which would keep any 1s)
// we would Xor it because we only want ODD numbers, so Xor will only give
// an odd number of 1, because Xoring two 1s will return 0.
	x = (x>>16) ^ x;
	x = (x>>8) ^ x;
	x = (x>>4) ^ x;
	x = (x>>2) ^ x;
	x = (x>>1) ^ x;
	
	return x & 1;
}
