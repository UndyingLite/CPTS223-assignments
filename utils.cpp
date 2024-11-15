#include "utils.h"
#include "Employee.h" // Include the header file for Employee class
#include <cstdlib>
#include <ctime>
#include <cmath>

Employee emp1("Alice", 55000);
Employee emp2("Bob", 60000);
Employee emp3("Charlie", 70000);
Employee emp4("David", 50000);

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int nextPrime(int n) {
    while (!isPrime(++n));
    return n;
}
std::string generateARandomName(int length) {
    std::string name;
    for (int i = 0; i < length; ++i) {
        name += 'A' + rand() % 26;
    }
    return name;
}

std::vector<std::string> generateRandomNames(int numNames) {
    std::vector<std::string> names;
    for (int i = 0; i < numNames; ++i) {
        names.push_back(generateARandomName(5));
    }
    return names;
}

int generateARandomInteger(int MAXNUM) {
    return rand() % MAXNUM;
}

std::vector<int> generateRandomIntegers(int numNumbers) {
    std::vector<int> numbers;
    for (int i = 0; i < numNumbers; ++i) {
        numbers.push_back(generateARandomInteger(100));
    }
    return numbers;
}