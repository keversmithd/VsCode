#ifndef RN_H
#define RN_H
#include <random>
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<int> dis;
std::mt19937 mt(rd());
#endif