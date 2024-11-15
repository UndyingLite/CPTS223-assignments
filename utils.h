#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Employee.h"

extern Employee emp1;
extern Employee emp2;
extern Employee emp3;
extern Employee emp4;

bool isPrime(int n);
int nextPrime(int n);
std::string generateARandomName(int length);
std::vector<std::string> generateRandomNames(int numNames);
int generateARandomInteger(int MAXNUM);
std::vector<int> generateRandomIntegers(int numNumbers);

#endif // UTILS_H
