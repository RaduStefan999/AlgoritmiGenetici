#pragma once
#include <random>

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
class NumberRandomGenerator
{
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<T> dis;

public:
    NumberRandomGenerator() : gen(rd()), dis(0, 65535) {};
    T Random(double a, double b) { return dis(gen); }
};

