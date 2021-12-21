#pragma once
#include <random>
#include "Defines.h"

class Bitstring;

struct TwoBytes
{
    unsigned char bytes[2];
};

class BitstringRandomGenerator
{
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<unsigned short> dis;

public:
    BitstringRandomGenerator() : gen(rd()), dis(0, 65535) {};
    void Random(Bitstring*);
};

template <class T>
class IntegerRandomGenerator
{
    std::random_device rd;
    std::mt19937 gen;

public:
    IntegerRandomGenerator() : gen(rd()) {};
    T RandomBetween(T a, T b)
    {
        std::uniform_int_distribution<T> dis(a, b);
        return dis(gen);
    }
};

template <class T>
class RealRandomGenerator
{
    std::random_device rd;
    std::mt19937 gen;

public:
    RealRandomGenerator() : gen(rd()) {};
    T RandomBetween(T a, T b)
    {
        std::uniform_real_distribution<T> dis(a, b);
        return dis(gen);
    }
};
