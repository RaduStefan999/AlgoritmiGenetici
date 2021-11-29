#pragma once

#include <stdio.h>

#define CHECK(condition, value, msg) { \
	if (!(condition)) { \
		printf(msg); \
		printf("\n"); \
		return (value); \
	} \
}