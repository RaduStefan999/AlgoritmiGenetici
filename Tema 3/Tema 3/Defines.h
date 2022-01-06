#pragma once

#include <stdio.h>
#include <chrono>

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

template <
	class result_t = std::chrono::milliseconds,
	class clock_t = std::chrono::steady_clock,
	class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
	return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

template <class T>
typename std::vector<T>::iterator insertReverseSorted(std::vector<T>& vec, T const& item, unsigned int maxSize)
{
	auto comparator = []<typename T>(const T & lh, const T & rh) -> bool
	{
		return lh < rh;
	};

	auto insertPosition = std::upper_bound(vec.begin(), vec.end(), item, comparator);
	
	if (vec.size() < maxSize)
	{
		return vec.insert(insertPosition, item);
	}
	else if (insertPosition != vec.end())
	{
		auto poz = vec.insert(insertPosition, item);
		vec.pop_back();
		return poz;
	}

	return vec.end();
}