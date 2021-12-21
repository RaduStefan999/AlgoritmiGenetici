#include "RandomGenerator.h"
#include "Bitstring.h"

void BitstringRandomGenerator::Random(Bitstring* bitstring)
{
    unsigned short result = 0;
    TwoBytes* bytesHolder = nullptr;

    unsigned int size = bitstring->dimensions->bitsLen / 16 + 1;

    for (unsigned int x = 0u; x < size; x++)
    {
        result = dis(gen);
        bytesHolder = reinterpret_cast<TwoBytes*>(&result);

        for (unsigned short y = 0u; y < 2; y++)
        {
            for (unsigned short z = 0u; x * 16 + y * 8 + z < bitstring->dimensions->bitsLen && z < 8; z++)
            {
                bitstring->bits[x * 16 + y * 8 + z] = ((bytesHolder->bytes[y] & 0b10000000) == 0b10000000);
                bytesHolder->bytes[y] = bytesHolder->bytes[y] << 1;
            }
        }
    }
}

