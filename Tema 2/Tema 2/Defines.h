#pragma once

#include <stdio.h>

#define VALIDATE(condition, value, msg) { \
	if (!(condition)) { \
		printf(msg); \
		printf("\n"); \
		return (value); \
	} \
}

#define VALIDATE_CONT(condition) { \
	if (!(condition)) { \
		continue; \
	} \
}

#define VALIDATE_RET(condition, msg) { \
	if (!(condition)) { \
		printf(msg); \
		printf("\n"); \
		return; \
	} \
}

#define INT_TYPE (std::is_same<T, int>::value || std::is_same<T, unsigned int>::value || std::is_same<T, unsigned long long>::value)