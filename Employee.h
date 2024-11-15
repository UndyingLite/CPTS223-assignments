#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
public:
    std::string firstName;
    std::string lastName;
    int id;
    double salary;

    Employee() : firstName(""), lastName(""), id(0), salary(0.0) {}
    Employee(const std::string& firstName, const std::string& lastName, int id)
        : firstName(firstName), lastName(lastName), id(id), salary(0.0) {}

    bool operator==(const Employee& other) const {
        return id == other.id; // Assuming ID is unique and can be used for comparison
    }

    bool operator!=(const Employee& other) const {
        return !(*this == other);
    }
};

namespace std {
    template<>
    struct hash<Employee> {
        size_t operator()(const Employee& e) const {
            return hash<int>()(e.id);
        }
    };
}

#endif // EMPLOYEE_H
