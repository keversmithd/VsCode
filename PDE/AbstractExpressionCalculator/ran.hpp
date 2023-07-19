#ifndef RN_H
#define RN_H
#include <random>
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);

#endif