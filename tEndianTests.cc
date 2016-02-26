/*
 Endian Template by Terence J. Grant (tjgrant@tatewake.com)

 Work with big endian and little endian types in C++ without ever calling a
 conversion function.

 The MIT License (MIT)
 Copyright (c) 2012-03-09 Terence J. Grant (tjgrant@tatewake.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions: The above copyright notice and this
 permission notice shall be included in all copies or substantial portions of
 the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <assert.h>
#include <cstdint>
#include "tEndian.h"

#include <stdio.h>

class tEndianTests
{
public:
    tEndianTests()
    {
        testSizeOf();
        testPlatMemIsMem();
        testOtherMemIsSwapped();
        testArithmeticAssignment();
        testLittleCompoundArithmeticAssignment();
        testBigCompoundArithmeticAssignment();
        testBigIsBig();
        testLittleIsLittle();
    }

    void testSizeOf()
    {
        assert(sizeof(leuint64) == 8);
        assert(sizeof(leuint32) == 4);
        assert(sizeof(leuint16) == 2);
        assert(sizeof(leint64) == 8);
        assert(sizeof(leint32) == 4);
        assert(sizeof(leint16) == 2);
        assert(sizeof(lefloat64) == 8);
        assert(sizeof(lefloat32) == 4);

        assert(sizeof(beuint64) == 8);
        assert(sizeof(beuint32) == 4);
        assert(sizeof(beuint16) == 2);
        assert(sizeof(beint64) == 8);
        assert(sizeof(beint32) == 4);
        assert(sizeof(beint16) == 2);
        assert(sizeof(befloat64) == 8);
        assert(sizeof(befloat32) == 4);

        printf("*** ::testSizeOf passed\n");
    }

    void testPlatMemIsMem()
    {
        union
        {
            uint8_t  c[2];
            uint16_t i;
        } u;

        u.i = 0x0001;

        if (u.c[0])
        {
            leuint32 val = 0x12345678;
            assert(((uint32_t*)&val)[0] == 0x12345678);
        }
        else
        {
            beuint32 val = 0x12345678;
            assert(((uint32_t*)&val)[0] == 0x12345678);
        }

        printf("*** ::testPlatMemIsMem passed\n");
    }

    void testOtherMemIsSwapped()
    {
        union
        {
            uint8_t  c[2];
            uint16_t i;
        } u;

        u.i = 0x0001;

        if (u.c[0])
        {
            beuint32 val = 0x12345678;
            assert(((uint32_t*)&val)[0] == 0x78563412);
        }
        else
        {
            leuint32 val = 0x12345678;
            assert(((uint32_t*)&val)[0] == 0x78563412);
        }

        printf("*** ::testOtherMemIsSwapped passed\n");
    }

    void testArithmeticAssignment()
    {
        leint32 a;
        beint32 b;

        // Prefix ++
        a = 0; b = 0;

        assert(a == 0);     assert(b == 0);
        assert(++a == 1);   assert(++b == 1);
        assert(a == 1);     assert(b == 1);

        // Prefix --
        a = 0; b = 0;

        assert(a == 0);     assert(b == 0);
        assert(--a == -1);  assert(--b == -1);
        assert(a == -1);    assert(b == -1);

        // Postfix ++
        a = 0; b = 0;

        assert(a++ == 0);   assert(b++ == 0);
        assert(a == 1);     assert(b == 1);

        // Postfix --
        a = 0; b = 0;

        assert(a-- == 0);   assert(b-- == 0);
        assert(a == -1);    assert(b == -1);

        printf("*** ::testArithmeticAssignment passed\n");
    }

    void testLittleCompoundArithmeticAssignment()
    {
        leint16 a;
        a = 2; a += 5; assert(a == 7);
        a = 2; a -= 5; assert(a == -3);
        a = 2; a *= 5; assert(a == 10);
        a = 15; a /= 5; assert(a == 3);
        a = 13; a %= 7; assert(a == 6);
        a = 63; a &= 7; assert(a == 7);
        a = 63; a |= 64; assert(a == 127);
        a = 63; a ^= 7; assert(a == 56);
        a = 63; a <<= 1; assert(a == 126);
        a = 126; a >>= 1; assert(a == 63);

        printf("*** ::testLittleCompoundArithmeticAssignment passed\n");
    }

    void testBigCompoundArithmeticAssignment()
    {
        beint16 a;
        a = 2; a += 5; assert(a == 7);
        a = 2; a -= 5; assert(a == -3);
        a = 2; a *= 5; assert(a == 10);
        a = 15; a /= 5; assert(a == 3);
        a = 13; a %= 7; assert(a == 6);
        a = 63; a &= 7; assert(a == 7);
        a = 63; a |= 64; assert(a == 127);
        a = 63; a ^= 7; assert(a == 56);
        a = 63; a <<= 1; assert(a == 126);
        a = 126; a >>= 1; assert(a == 63);

        printf("*** ::testBigCompoundArithmeticAssignment passed\n");
    }

    void testBigIsBig()
    {
        {
            beuint64   big     = 0x1122334455667788;
            beuint64   invbig  = 0x8877665544332211;
            leuint64   lit     = 0x1122334455667788;
            beuint64   other   = 0x1122334455667788;

            assert( ((uint64_t*)&big)[0] != ((uint64_t*)&invbig)[0]);
            assert( ((uint64_t*)&big)[0] == ((uint64_t*)&other)[0] );
            assert( ((uint64_t*)&big)[0] != ((uint64_t*)&lit)[0] );
            assert( ((uint64_t*)&invbig)[0] != ((uint64_t*)&other)[0] );
            assert( ((uint64_t*)&invbig)[0] == ((uint64_t*)&lit)[0] );
        }
        {
            beint32   big     = 0x12345678;
            beint32   invbig  = 0x78563412;
            leint32   lit     = 0x12345678;
            beint32   other   = 0x12345678;

            assert( ((uint32_t*)&big)[0] != ((uint32_t*)&invbig)[0]);
            assert( ((uint32_t*)&big)[0] == ((uint32_t*)&other)[0] );
            assert( ((uint32_t*)&big)[0] != ((uint32_t*)&lit)[0] );
            assert( ((uint32_t*)&invbig)[0] != ((uint32_t*)&other)[0] );
            assert( ((uint32_t*)&invbig)[0] == ((uint32_t*)&lit)[0] );
        }
        {
            beint16   big     = 0x0102;
            beint16   invbig  = 0x0201;
            leint16   lit     = 0x0102;
            beint16   other   = 0x0102;

            assert( ((uint16_t*)&big)[0] != ((uint16_t*)&invbig)[0]);
            assert( ((uint16_t*)&big)[0] == ((uint16_t*)&other)[0] );
            assert( ((uint16_t*)&big)[0] != ((uint16_t*)&lit)[0] );
            assert( ((uint16_t*)&invbig)[0] != ((uint16_t*)&other)[0] );
            assert( ((uint16_t*)&invbig)[0] == ((uint16_t*)&lit)[0] );
        }

        printf("*** ::testBigIsBig passed\n");
    }

    void testLittleIsLittle()
    {
        {
            leuint64   lit     = 0x1122334455667788;
            leuint64   invlit  = 0x8877665544332211;
            leuint64   plat    = 0x1122334455667788;
            beuint64   big     = 0x1122334455667788;

            assert( ((uint32_t*)&lit)[0] != ((uint32_t*)&invlit)[0]);
            assert( ((uint32_t*)&lit)[0] != ((uint32_t*)&big)[0] );
            assert( ((uint32_t*)&lit)[0] == ((uint32_t*)&plat)[0] );
            assert( ((uint32_t*)&invlit)[0] == ((uint32_t*)&big)[0] );
            assert( ((uint32_t*)&invlit)[0] != ((uint32_t*)&plat)[0] );
        }
        {
            leint32   lit     = 0x12345678;
            leint32   invlit  = 0x78563412;
            leint32   plat    = 0x12345678;
            beint32   big     = 0x12345678;

            assert( ((uint32_t*)&lit)[0] != ((uint32_t*)&invlit)[0]);
            assert( ((uint32_t*)&lit)[0] != ((uint32_t*)&big)[0] );
            assert( ((uint32_t*)&lit)[0] == ((uint32_t*)&plat)[0] );
            assert( ((uint32_t*)&invlit)[0] == ((uint32_t*)&big)[0] );
            assert( ((uint32_t*)&invlit)[0] != ((uint32_t*)&plat)[0] );
        }
        {
            leint16   lit     = 0x0102;
            leint16   invlit  = 0x0201;
            leint16   plat    = 0x0102;
            beint16   big     = 0x0102;

            assert( ((uint16_t*)&lit)[0] != ((uint16_t*)&invlit)[0]);
            assert( ((uint16_t*)&lit)[0] != ((uint16_t*)&big)[0] );
            assert( ((uint16_t*)&lit)[0] == ((uint16_t*)&plat)[0] );
            assert( ((uint16_t*)&invlit)[0] == ((uint16_t*)&big)[0] );
            assert( ((uint16_t*)&invlit)[0] != ((uint16_t*)&plat)[0] );
        }

        printf("*** ::testLittleIsLittle passed\n");
    }
};

int main (int argc, char *argv[])
{
    printf("*** Running tEndianTests...\n");

    tEndianTests();

    printf("*** All tests passed!\n");

    return 0;
}