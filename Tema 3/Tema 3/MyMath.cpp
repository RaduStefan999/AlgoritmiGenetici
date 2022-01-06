#include "MyMath.h"

long double MyMath::Abslute(long double x)
{
	return x > 0 ? x : -x;
}

unsigned int MyMath::IntAbsolute(int x)
{
	return x > 0 ? x : -x;
}