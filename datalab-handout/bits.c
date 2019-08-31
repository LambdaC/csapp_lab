/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //x ^ y = ~x & y | x & ~y;
  //x | y = ~(~x & ~y); De Morgan's laws 
  return ~(~(~x & y) & ~(x & ~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // Tmax + 1 = Tmin, and their all bits are opposite.
  // if x is Tmax, !(~(y ^ x)) is equal to 1.
  // -1 + 1 = 0, and also their all bits are opppsite.
  // if x is -1, !(~(y ^ x)) is also equal to 1.
  // other number has no this property.
  // !Tmax, !Tmin and !-1 all equal to 0, !0 equal to 1.
  // if X is Tmax, !(!x | !y) is equal to 1.
  // if x is -1, !(!x | !y) is equal to 0.
  // problem solved.
  int y = x + 1;
  return !(~(y ^ x)) & !(!y | !x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // The solution is very obvious.
  int num = 0xAA;
  num = num << 8;
  num = num + 0xAA;
  num = num << 8;
  num = num + 0xAA;
  num = num << 8;
  num = num + 0xAA;
  return !((x & num) ^ num);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // Very obvious.
  return (~x) + 1;
}
//3
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
  // if 0x30 <= x <= 0x39, x must satisy x +(-0x30) >= 0 and 0x39 + (-x) > = 0;
  // cal x + (-0x30) and 0x39 + (-x), if both result's MSB is equal to 0,
  // then x is satisfied.
  int negative_min = (~0x30) + 1;
  int negative_x = (~x) + 1;
  int min = x + negative_min; // equal x - 0x30
  int max = 0x39 + negative_x; // equal 0x39 - max
  int r = !((min >> 31) & 1) & !((max >> 31) & 1);
  return r;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // MUX's implementation
  int s = !x; // s equal 0(output y) or 1(output z)
  return (y & (~(!s) + 1)) | (z & (~s + 1));
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // first check the sign.
  // second if the sign is equal, then cal the x + (-y), and check the sign.
  int x_sign = (x >> 31) & 1;
  int y_sign = (y >> 31) & 1;
  int negative_y = (~y) + 1;
  int sum = x + negative_y;
  // if the sign is not equal, use the former part, if the sign is equal, use the later part.
  return ((x_sign ^ y_sign) & x_sign)                                  // sign is not equal
         | ((!(x_sign ^ y_sign))                                       // sign is equal 
                               & ((!sum)                               // sum is 0
                                 | ((!!sum) & (sum >> 31 & 1))));      // sum is not 0, then cal the sign bit
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // negative 0 or Tmin, it will get themself, thus their sign not change.
  // negative other number will change their sign.
  // 0'sign is 0, Tmin's sign is 1.
  // if x is 0, then (x'sign | ~x'sign) is 0, otherwise is 1.
  return (((x >> 31) & 1) | ((((~x) + 1) >> 31) & 1)) ^ 1;
}
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
  // if x is postive, find the first 1's pos, then return pos+1
  // if x is negative, ~x, find the first 1's pos, then return pos+1
  // int x_sign = (x >> 31) & 1;
  // sign?~x+1:x
  //int abs_x = ((~x_sign + 1) & (~x + 1)) | ((~(!x_sign) + 1) & x) ;
  //int y = x >> 31;
  //int abs_x = (x + y) ^ y;
  //int neg_x = ~abs_x + 1;
  int a,b,c,d,e,f,g,h,i,j,k;
  int num1,num2,num3,num4;
  int result;
  int x_sign = (x >> 31);
  // x_sign?~x:x
  x = (x_sign & (~x)) | (~x_sign & x);
  // cal 0xffff0000 and 0x0000ffff
  e = 16;
  f = 0;
  num2 = (0xff << 8) + 0xff;
  num1 = num2 << e;
  // a = ~(!!(x & num1)) + 1;
  // b = ~(!!(x & num2)) + 1;
  // optimize
  // 0x0 + (-1) ==> 0x0 + (~0) ==> 0xffffffff
  // 0x1 + (-1) ==> 0x1 + (~0) ==> 0x00000000
  a = !(x & num1) + (~0);
  b = !(x & num2) + (~0);
  k = (a & e) |
    ((~a) & (b & f));
  x = x >> k;

  // 0xf000, 0x0f00, 0x00f0, 0x000f
  e = 12;
  f = 8;
  g = 4;
  h = 0;
  num1 = 0xf << e;
  num2 = 0xf << f;
  num3 = 0xf0;
  num4 = 0xf;
  // a = ~(!!(x & num1)) + 1;
  // b = ~(!!(x & num2)) + 1;
  // c = ~(!!(x & num3)) + 1;
  // d = ~(!!(x & num4)) + 1;
  // optimize
  // 0x0 + (-1) ==> 0x0 + (~0) ==> 0xffffffff
  // 0x1 + (-1) ==> 0x1 + (~0) ==> 0x00000000
  a = !(x & num1) + (~0);
  b = !(x & num2) + (~0);
  c = !(x & num3) + (~0);
  d = !(x & num4) + (~0);
  i = (a & e) |
    ((~a) & ((b & f) |
    ((~b) & ((c & g) |
      ((~c) & (d & h))))));
  x = x >> i;

  // 0x8, 0x4, 0x2, 0x1
  e = 4;
  f = 3;
  g = 2;
  h = 1;
  num1 = 0x8;
  num2 = 0x4;
  num3 = 0x2;
  num4 = 0x1;
  // a = ~(!!(x & num1)) + 1;
  // b = ~(!!(x & num2)) + 1;
  // c = ~(!!(x & num3)) + 1;
  // d = ~(!!(x & num4)) + 1;
  // optimize
  // 0x0 + (-1) ==> 0x0 + (~0) ==> 0xffffffff
  // 0x1 + (-1) ==> 0x1 + (~0) ==> 0x00000000
  a = !(x & num1) + (~0);
  b = !(x & num2) + (~0);
  c = !(x & num3) + (~0);
  d = !(x & num4) + (~0);
  j = (a & e) |
    ((~a) & ((b & f) |
    ((~b) & ((c & g) |
      ((~c) & (d & h))))));
  result = i + j + k + 1;
  return result;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & (0x7FFFFF);
  if (exp == 0xFF) {
    return uf;
  }
  else if (exp != 0) {
    return uf + 0x800000;
  }
  else {
    unsigned carry;
    frac = frac << 1;
    carry = frac & (0x800000);
    if (carry) {
      uf = uf + 0x800000;
      frac = frac & 0x7FFFFF;
    }
    uf = uf & 0xFF800000;
    uf = uf | frac;
    return uf;
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  unsigned sign = (uf >> 31) & 1;
  if (exp == 0xFF) {
    return 0x80000000;
  }
  else if (exp == 0) {
    return 0;
  }
  else {
    int carry;
    int result = 1;
    int e = exp - 0x7F;
    if (e < 0){
      return 0;
    }
    if ((!sign && e > 31) || (sign && e > 30)){
      return 0x80000000;
    }
    while(e > 0) {
      carry = ((frac << 1) & 0x800000) >> 23;
      result = (result << 1) + carry;
      e--;
    }
    if (sign) {
      result = -result;
    }
    return result;
  }
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
/* 
 * CS:APP Data Lab 
 */ 
