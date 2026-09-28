/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    /*
    4 = 0100
    5 = 0101
    ~(~a+~b) = a*b
    */
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    /*
    相同为0，不同为1
    */
    return ~((~x)&(~y))&(~(x&y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (x && y)
        return !((x ^ y) >> 31);    //先异或再取第n位
    return !x && !y;                //直接取反！
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int s;

    s = ((v>>16)>0)<<4;     //如果右移16大于0，那结果就+16
    r |= s;
    v>>=s;

    s = ((v>>8)>0)<<3;
    r|=s;
    v>>=s;

    s = ((v>>4)>0)<<2;
    r|=s;
    v>>=s;

    s = ((v>>2)>0)<<1;
    r|=s;
    v>>=s;

    r|= v>>1;       //检查最后一位

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int b1 = (x>>(n<<3))&(0xFF);
    int b2 = (x>>(m<<3))&(0xFF);
    
    int mask = (0xFF<<(n<<3))|(0xFF<<(m<<3));

    x = x& ~mask;       //清零
    x = x|(b1<<(m<<3))|(b2<<(n<<3));

    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    int r = 0;      //res
    int i=32;       //32位
    while(i--){
        r = (r<<1)|(v&1);       //每次取v最低位，拼到r末尾，r左移
        v>>=1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1<<31)>>n)<<1);    //n = 4为例，1000 0000.....->1111 1000.....->1111 0000....
    
    x = x>>n;

    x &= mask;      //0*0=0,0*1=0

    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count = 0;
    int cond;
    int isfuone = !~x;
    //!~操作判断是否全1
    cond = !~(x>>16);       //右移16位，如果全1，那么左侧必定补的是1
    count += cond<<4;       //+16
    x <<= (cond<<4);        //左移16

    cond = !~(x>>24);
    count += cond<<3;       //+8
    x <<= (cond<<3);        //左移8

    cond = !~(x>>28);
    count += cond<<2;
    x <<= (cond<<2);

    cond = !~(x>>30);
    count += cond<<1;
    x <<= (cond<<1);

    cond = !~(x>>31);
    count += cond<<0;
    x <<= (cond<<0);

    count += isfuone;

    return count;
    /*
    1111 1111 1111 1111 1111 1111 1111 1111
    >>16 取高16位 判断是否全一 然后左移16位
    1111 1111 1111 1111 0000 0000 0000 0000
    >>24 取高8位 然后左移8位
    1111 1111 0000 0000 0000 0000 0000 0000
    >>28 取高4位 然后左移4
    1111 0000 0000 0000 0000 0000 0000 0000
    >>30 取高2位 左移2
    1100 0000 0000 0000 0000 0000 0000 0000
    >>31 取高1位 左移1
    1000 0000 0000 0000 0000 0000 0000 0000
    */
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    //整数转浮点数
    unsigned sign = x & 0x80000000; //取第一位符号位
    unsigned absx = x;
    if(x<0) absx = -x;  //转为绝对值

    int exp = 31;   //指数
    unsigned round,m;

    if(x==0) return 0;
    if(x==0x80000000) return 0xCF000000;        //-2^31 取绝对值会溢出 先处理
                            //1 100 11110 000 0000 0000.....
    while(!(absx & 0x80000000)){    //循环左移，直至最高位为1 确定指数
        absx <<= 1;
        exp -= 1;
    }

    round = absx&0xFF;      //提取低8位 准备舍入
    absx >>= 8;     //bit31 -> bit23
    m = absx & 0x7FFFFF;     //取低23位作为尾数

    if (round > 0x80) {
        m += 1;
    } else if (round == 0x80 && (m & 1)) {  //正好一半，偶数不动奇数进位
        m += 1;
    }

    if (m == 0x800000) {     //尾数溢出，指数加1
        exp = exp + 1;
        m = 0;
    }
    exp = exp + 127;
    return sign | (exp << 23) | m;

    /*
    0x7fffffff = 0111 1111 1111 1111 1111 1111 1111 1111
    sign = 0
    absx = 0x7fffffff
    左移1 exp = 31-1=30
    absx = 1111 1111 1111 1111 1111 1111 1111 1110
    round = 1111 1110
    absx右移8位 = 0000 0000 1111 1111 1111 1111 1111 1111 unsigned无符号类型

    m = .... .... 0111 1111 1111 1111 1111 1111 取低23位作尾数
    round = 254>128(0x80) 进位
    此时m+=1 m溢出，进位
    m=0; exp+=1
    */
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    //阶码全1
    if((uf & 0x7F800000) == 0x7F800000) return uf;      //0111 1111 1000 NAN或无穷大
    //阶码全0                               1000 0000 0000....  0111 1111 1111....
    if((uf & 0x7F800000) == 0) return (uf & 0x80000000)|((uf & 0x7FFFFFFF) << 1);   //只对低31位左移,取最高位，然后|拼接
    //指数为254
    if((uf & 0x7F800000) == 0x7F000000) return (uf & 0x80000000)| 0x7F800000;       //变为无穷大 阶码全1 M为0

    return uf + (1<<23);    //普通数，指数加1
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7ff;
    int e = exp - 1023;
    unsigned high, mag;

    if (e < 0) {
        return 0;
    }
    if (e >= 31) {
        return 0x80000000;
    }
    high = (uf2 & 0xfffff) | 0x100000;
    if (e <= 20) {
        mag = high >> (20 - e);
    } else {
        mag = (high << (e - 20)) | (uf1 >> (52 - e));
    }
    if (sign) {
        return -mag;
    }
    return mag;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
        return 0;
    if (x > 127)
        return 0x7f800000;
    if (x < -126)
        return 1 << (x + 149);
    return (x + 127) << 23;
}
