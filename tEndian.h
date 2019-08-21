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

#pragma once

#include <cassert>
#include <cstdint>

//Both tLittleEndian and tBigEndian are manufactured primitives
//that are essentially immutable except for the assignment operators.
//All math logic happens outside of the class in the native format
//and an internal set/swap method is used to store the data.

template<typename T>
class tEndianBase
{
protected:
#if _MSC_VER
#pragma warning ( push ) 
#pragma warning ( disable : 4701 )
#pragma warning ( disable : 4789 )
#endif
    static T Swap(const T& b)
    {
        T n;

        switch(sizeof(T))
        {
            case 8: //64-bit
                ((uint8_t*)&n)[0] = ((uint8_t*)&b)[7];
                ((uint8_t*)&n)[1] = ((uint8_t*)&b)[6];
                ((uint8_t*)&n)[2] = ((uint8_t*)&b)[5];
                ((uint8_t*)&n)[3] = ((uint8_t*)&b)[4];
                ((uint8_t*)&n)[4] = ((uint8_t*)&b)[3];
                ((uint8_t*)&n)[5] = ((uint8_t*)&b)[2];
                ((uint8_t*)&n)[6] = ((uint8_t*)&b)[1];
                ((uint8_t*)&n)[7] = ((uint8_t*)&b)[0];
                break;
            case 4: //32-bit
                ((uint8_t*)&n)[0] = ((uint8_t*)&b)[3];
                ((uint8_t*)&n)[1] = ((uint8_t*)&b)[2];
                ((uint8_t*)&n)[2] = ((uint8_t*)&b)[1];
                ((uint8_t*)&n)[3] = ((uint8_t*)&b)[0];
                break;
            case 2: //16-bit
                ((uint8_t*)&n)[0] = ((uint8_t*)&b)[1];
                ((uint8_t*)&n)[1] = ((uint8_t*)&b)[0];
                break;
            default:
                assert(0);  //Endian swap is only defined for 2, 4, and 8-byte types
                break;
        }

        return n;
    }
#if _MSC_VER
#pragma warning ( pop )
#endif
};

template<typename T>
class tLittleEndian
: public tEndianBase<T>
{
protected:
    T mData;

protected:
    static T Transform(const T& b)
    {
        const uint16_t i = 1;

        return (reinterpret_cast<const char&>(i) == 1) ? b : tEndianBase<T>::Swap(b);
    }
public:
    // Constructors
    tLittleEndian() = default;

    //If we endian swap, it happens in two places:
    //1. Set an OE from a PE
    //2. Get a PE from an OE
    // Storage in
    tLittleEndian(const T& b) : mData(Transform(b)) { }
    template <typename U> explicit tLittleEndian(U const & b) : mData(Transform(T(b))) { }
    // Storage out
    template <typename U> operator U() const { return U(Transform(mData)); }
    operator T() const { return Transform(mData); }

    template <typename U> bool operator ==(U const& o) { return U(*this) == o; }
    template <typename U> bool operator !=(U const& o) { return U(*this) != o; }

    //Arithmetic assignment operators
    tLittleEndian& operator ++()   /* prefix */ {                           *this = T(*this) + T(1); return *this; }
    tLittleEndian operator ++(int) /* suffix */ { tLittleEndian t(*this);   *this = T(*this) + T(1); return t; }
    tLittleEndian& operator --()   /* prefix */ {                           *this = T(*this) - T(1); return *this; }
    tLittleEndian operator --(int) /* suffix */ { tLittleEndian t(*this);   *this = T(*this) - T(1); return t; }
    
    //Compound assignment operators
    tLittleEndian& operator +=(const T& b)  { *this = T(*this) + b; return *this; }
    tLittleEndian& operator -=(const T& b)  { *this = T(*this) - b; return *this; }
    tLittleEndian& operator *=(const T& b)  { *this = T(*this) * b; return *this; }
    tLittleEndian& operator /=(const T& b)  { *this = T(*this) / b; return *this; }
    tLittleEndian& operator %=(const T& b)  { *this = T(*this) % b; return *this; }
    tLittleEndian& operator &=(const T& b)  { *this = T(*this) & b; return *this; }
    tLittleEndian& operator |=(const T& b)  { *this = T(*this) | b; return *this; }
    tLittleEndian& operator ^=(const T& b)  { *this = T(*this) ^ b; return *this; }
    tLittleEndian& operator <<=(const T& b) { *this = T(T(*this) << b); return *this; }
    tLittleEndian& operator >>=(const T& b) { *this = T(T(*this) >> b); return *this; }
};

template<typename T>
class tBigEndian
: public tEndianBase<T>
{
protected:
    T mData;
    
protected:
    static T Transform(const T& b)
    {
        const uint16_t i = 1;

        return (reinterpret_cast<const char&>(i) == 1) ? tEndianBase<T>::Swap(b) : b;
    }

public:
    // Constructors
    tBigEndian() = default;
    
    //If we endian swap, it happens in two places:
    //1. Set an OE from a PE
    //2. Get a PE from an OE
    // Storage in
    tBigEndian(const T& b) : mData(Transform(b)) { }
    template <typename U> explicit tBigEndian(U const & b) : mData(Transform(T(b))) { }
    // Storage out
    template <typename U> operator U() const { return U(Transform(mData)); }
    operator T() const { return Transform(mData); }
    
    template <typename U> bool operator ==(U const& o) { return U(*this) == o; }
    template <typename U> bool operator !=(U const& o) { return U(*this) != o; }

    //Arithmetic assignment operators
    tBigEndian& operator ++()   /* prefix */ {                      *this = T(*this) + 1; return *this; }
    tBigEndian operator ++(int) /* suffix */ { tBigEndian t(*this); *this = T(*this) + 1; return t; }
    tBigEndian& operator --()   /* prefix */ {                      *this = T(*this) - 1; return *this; }
    tBigEndian operator --(int) /* suffix */ { tBigEndian t(*this); *this = T(*this) - 1; return t; }
    
    //Compound assignment operators
    tBigEndian& operator +=(const T& b)  { *this = T(*this) + b; return *this; }
    tBigEndian& operator -=(const T& b)  { *this = T(*this) - b; return *this; }
    tBigEndian& operator *=(const T& b)  { *this = T(*this) * b; return *this; }
    tBigEndian& operator /=(const T& b)  { *this = T(*this) / b; return *this; }
    tBigEndian& operator %=(const T& b)  { *this = T(*this) % b; return *this; }
    tBigEndian& operator &=(const T& b)  { *this = T(*this) & b; return *this; }
    tBigEndian& operator |=(const T& b)  { *this = T(*this) | b; return *this; }
    tBigEndian& operator ^=(const T& b)  { *this = T(*this) ^ b; return *this; }
    tBigEndian& operator <<=(const T& b) { *this = T(T(*this) << b); return *this; }
    tBigEndian& operator >>=(const T& b) { *this = T(T(*this) >> b); return *this; }
};

typedef tLittleEndian<int16_t>      leint16;
typedef tLittleEndian<int32_t>      leint32;
typedef tLittleEndian<int64_t>      leint64;

typedef tLittleEndian<uint16_t>     leuint16;
typedef tLittleEndian<uint32_t>     leuint32;
typedef tLittleEndian<uint64_t>     leuint64;

typedef tLittleEndian<float>        lefloat32;
typedef tLittleEndian<double>       lefloat64;

typedef tBigEndian<int16_t>         beint16;
typedef tBigEndian<int32_t>         beint32;
typedef tBigEndian<int64_t>         beint64;

typedef tBigEndian<uint16_t>        beuint16;
typedef tBigEndian<uint32_t>        beuint32;
typedef tBigEndian<uint64_t>        beuint64;

typedef tBigEndian<float>           befloat32;
typedef tBigEndian<double>          befloat64;
