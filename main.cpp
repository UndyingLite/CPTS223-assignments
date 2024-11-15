#include "Employee.h"
#include "SeparateChaining.h"
#include "LinearProbing.h"
#include "utils.h"
#include <iostream>

void testChainingHash() {
    ChainingHash<Employee> employeeChainingHash;
    employeeChainingHash.insert(emp1);
    employeeChainingHash.insert(emp2);
    employeeChainingHash.insert(emp3);
    employeeChainingHash.insert(emp4);

    std::cout << "ChainingHash contains emp1: " << employeeChainingHash.contains(emp1) << std::endl;
    std::cout << "ChainingHash load factor: " << employeeChainingHash.loadFactor() << std::endl;

    employeeChainingHash.remove(emp2);
    std::cout << "ChainingHash contains emp2 after removal: " << employeeChainingHash.contains(emp2) << std::endl;
}

void testProbingHash() {
    ProbingHash<Employee> employeeProbingHash;
    employeeProbingHash.insert(emp1);
    employeeProbingHash.insert(emp2);
    employeeProbingHash.insert(emp3);
    employeeProbingHash.insert(emp4);

    std::cout << "ProbingHash contains emp1: " << employeeProbingHash.contains(emp1) << std::endl;
    std::cout << "ProbingHash load factor: " << employeeProbingHash.loadFactor() << std::endl;

    employeeProbingHash.remove(emp2);
    std::cout << "ProbingHash contains emp2 after removal: " << employeeProbingHash.contains(emp2) << std::endl;
}
int main() {
    std::cout << "Testing Separate Chaining Hash Table" << std::endl;
    testChainingHash();

    std::cout << "\nTesting Linear Probing Hash Table" << std::endl;
    testProbingHash();

    return 0;
}
