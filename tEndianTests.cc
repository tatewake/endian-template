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

#include "Base/package.h"

#include "Test/package.h"

class tEndianTests : public TestFixture<tEndianTests>
{
public:
	TEST_FIXTURE( tEndianTests )
	{
		TEST_CASE( testSizeOf );
		TEST_CASE( testPlatMemIsMem );
		TEST_CASE( testOtherMemIsSwapped );
		TEST_CASE( testArithmeticAssignment );
		TEST_CASE( testLittleCompoundArithmeticAssignment );
		TEST_CASE( testBigCompoundArithmeticAssignment );
        TEST_CASE( testBigIsBig );
        TEST_CASE( testLittleIsLittle );
	}

    void testSizeOf()
	{
		ASSERT(sizeof(leuint64_t) == 8);
		ASSERT(sizeof(leuint32_t) == 4);
		ASSERT(sizeof(leuint16_t) == 2);
		ASSERT(sizeof(leint64_t) == 8);
		ASSERT(sizeof(leint32_t) == 4);
		ASSERT(sizeof(leint16_t) == 2);
        ASSERT(sizeof(lefloat64_t) == 8);
        ASSERT(sizeof(lefloat32_t) == 4);
        ASSERT(sizeof(lefloat16_t) == 2);

		ASSERT(sizeof(beuint64_t) == 8);
		ASSERT(sizeof(beuint32_t) == 4);
		ASSERT(sizeof(beuint16_t) == 2);
		ASSERT(sizeof(beint64_t) == 8);
		ASSERT(sizeof(beint32_t) == 4);
		ASSERT(sizeof(beint16_t) == 2);
        ASSERT(sizeof(befloat64_t) == 8);
        ASSERT(sizeof(befloat32_t) == 4);
        ASSERT(sizeof(befloat16_t) == 2);
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
            leuint32_t val = 0x12345678;
            ASSERT(((uint32_t*)&val)[0] == 0x12345678);
        }
        else
        {
            beuint32_t val = 0x12345678;
            ASSERT(((uint32_t*)&val)[0] == 0x12345678);
        }
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
            beuint32_t val = 0x12345678;
            ASSERT(((uint32_t*)&val)[0] == 0x78563412);
        }
        else
        {
            leuint32_t val = 0x12345678;
            ASSERT(((uint32_t*)&val)[0] == 0x78563412);
        }
	}

    void testArithmeticAssignment()
    {
        leint32_t a;
        beint32_t b;

        // Prefix ++
        a = 0; b = 0;

        ASSERT(a == 0);     ASSERT(b == 0);
        ASSERT(++a == 1);   ASSERT(++b == 1);
        ASSERT(a == 1);     ASSERT(b == 1);

        // Prefix --
        a = 0; b = 0;

        ASSERT(a == 0);     ASSERT(b == 0);
        ASSERT(--a == -1);  ASSERT(--b == -1);
        ASSERT(a == -1);    ASSERT(b == -1);

        // Postfix ++
        a = 0; b = 0;

        ASSERT(a++ == 0);   ASSERT(b++ == 0);
        ASSERT(a == 1);     ASSERT(b == 1);

        // Postfix --
        a = 0; b = 0;

        ASSERT(a-- == 0);   ASSERT(b-- == 0);
        ASSERT(a == -1);    ASSERT(b == -1);
    }

    void testLittleCompoundArithmeticAssignment()
	{
        leint16_t a;
        a = 2; a += 5; ASSERT(a == 7);
        a = 2; a -= 5; ASSERT(a == -3);
        a = 2; a *= 5; ASSERT(a == 10);
        a = 15; a /= 5; ASSERT(a == 3);
        a = 13; a %= 7; ASSERT(a == 6);
        a = 63; a &= 7; ASSERT(a == 7);
        a = 63; a |= 64; ASSERT(a == 127);
        a = 63; a ^= 7; ASSERT(a == 56);
        a = 63; a <<= 1; ASSERT(a == 126);
        a = 126; a >>= 1; ASSERT(a == 63);
	}

    void testBigCompoundArithmeticAssignment()
	{
        beint16_t a;
        a = 2; a += 5; ASSERT(a == 7);
        a = 2; a -= 5; ASSERT(a == -3);
        a = 2; a *= 5; ASSERT(a == 10);
        a = 15; a /= 5; ASSERT(a == 3);
        a = 13; a %= 7; ASSERT(a == 6);
        a = 63; a &= 7; ASSERT(a == 7);
        a = 63; a |= 64; ASSERT(a == 127);
        a = 63; a ^= 7; ASSERT(a == 56);
        a = 63; a <<= 1; ASSERT(a == 126);
        a = 126; a >>= 1; ASSERT(a == 63);
	}

    void testBigIsBig()
    {
        {
            beuint64_t   big     = 0x1122334455667788;
            beuint64_t   invbig  = 0x8877665544332211;
            leuint64_t   lit     = 0x1122334455667788;
            beuint64_t   other   = 0x1122334455667788;

            ASSERT( ((uint64_t*)&big)[0] != ((uint64_t*)&invbig)[0]);
            ASSERT( ((uint64_t*)&big)[0] == ((uint64_t*)&other)[0] );
            ASSERT( ((uint64_t*)&big)[0] != ((uint64_t*)&lit)[0] );
            ASSERT( ((uint64_t*)&invbig)[0] != ((uint64_t*)&other)[0] );
            ASSERT( ((uint64_t*)&invbig)[0] == ((uint64_t*)&lit)[0] );
        }
        {
            beint32_t   big     = 0x12345678;
            beint32_t   invbig  = 0x78563412;
            leint32_t   lit     = 0x12345678;
            beint32_t   other   = 0x12345678;

            ASSERT( ((uint32_t*)&big)[0] != ((uint32_t*)&invbig)[0]);
            ASSERT( ((uint32_t*)&big)[0] == ((uint32_t*)&other)[0] );
            ASSERT( ((uint32_t*)&big)[0] != ((uint32_t*)&lit)[0] );
            ASSERT( ((uint32_t*)&invbig)[0] != ((uint32_t*)&other)[0] );
            ASSERT( ((uint32_t*)&invbig)[0] == ((uint32_t*)&lit)[0] );
        }
        {
            beint16_t   big     = 0x0102;
            beint16_t   invbig  = 0x0201;
            leint16_t   lit     = 0x0102;
            beint16_t   other   = 0x0102;

            ASSERT( ((uint16_t*)&big)[0] != ((uint16_t*)&invbig)[0]);
            ASSERT( ((uint16_t*)&big)[0] == ((uint16_t*)&other)[0] );
            ASSERT( ((uint16_t*)&big)[0] != ((uint16_t*)&lit)[0] );
            ASSERT( ((uint16_t*)&invbig)[0] != ((uint16_t*)&other)[0] );
            ASSERT( ((uint16_t*)&invbig)[0] == ((uint16_t*)&lit)[0] );
        }
    }

    void testLittleIsLittle()
    {
        {
            leuint64_t   lit     = 0x1122334455667788;
            leuint64_t   invlit  = 0x8877665544332211;
            leuint64_t   plat    = 0x1122334455667788;
            beuint64_t   big     = 0x1122334455667788;

            ASSERT( ((uint32_t*)&lit)[0] != ((uint32_t*)&invlit)[0]);
            ASSERT( ((uint32_t*)&lit)[0] != ((uint32_t*)&big)[0] );
            ASSERT( ((uint32_t*)&lit)[0] == ((uint32_t*)&plat)[0] );
            ASSERT( ((uint32_t*)&invlit)[0] == ((uint32_t*)&big)[0] );
            ASSERT( ((uint32_t*)&invlit)[0] != ((uint32_t*)&plat)[0] );
        }
        {
            leint32_t   lit     = 0x12345678;
            leint32_t   invlit  = 0x78563412;
            leint32_t   plat    = 0x12345678;
            beint32_t   big     = 0x12345678;

            ASSERT( ((uint32_t*)&lit)[0] != ((uint32_t*)&invlit)[0]);
            ASSERT( ((uint32_t*)&lit)[0] != ((uint32_t*)&big)[0] );
            ASSERT( ((uint32_t*)&lit)[0] == ((uint32_t*)&plat)[0] );
            ASSERT( ((uint32_t*)&invlit)[0] == ((uint32_t*)&big)[0] );
            ASSERT( ((uint32_t*)&invlit)[0] != ((uint32_t*)&plat)[0] );
        }
        {
            leint16_t   lit     = 0x0102;
            leint16_t   invlit  = 0x0201;
            leint16_t   plat    = 0x0102;
            beint16_t   big     = 0x0102;

            ASSERT( ((uint16_t*)&lit)[0] != ((uint16_t*)&invlit)[0]);
            ASSERT( ((uint16_t*)&lit)[0] != ((uint16_t*)&big)[0] );
            ASSERT( ((uint16_t*)&lit)[0] == ((uint16_t*)&plat)[0] );
            ASSERT( ((uint16_t*)&invlit)[0] == ((uint16_t*)&big)[0] );
            ASSERT( ((uint16_t*)&invlit)[0] != ((uint16_t*)&plat)[0] );
        }
    }
};

REGISTER_FIXTURE( tEndianTests );
