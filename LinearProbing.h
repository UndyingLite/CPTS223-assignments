#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include <vector>
#include <functional>

#include "utils.h"
#include "Employee.h"

template <typename HashedObj>
class ProbingHash {
public:
    explicit ProbingHash(int size = 101) : hashTable(size), currentSize(0) {}

    bool contains(const HashedObj& x) const {
        return isActive(findPos(x));
    }

    void makeEmpty() {
        for (auto& entry : hashTable) {
            entry.info = EMPTY;
        }
        currentSize = 0;
    }

    bool insert(const HashedObj& x) {
        int currentPos = findPos(x);
        if (isActive(currentPos)) return false;

        hashTable[currentPos].element = x;
        hashTable[currentPos].info = ACTIVE;

        if (++currentSize > hashTable.size() / 2) {
            rehash();
        }
        return true;
    }

    bool insert(HashedObj&& x) {
        return insert(x);
    }

    bool remove(const HashedObj& x) {
        int currentPos = findPos(x);
        if (!isActive(currentPos)) return false;

        hashTable[currentPos].info = DELETED;
        return true;
    }

    double loadFactor() const {
        return static_cast<double>(currentSize) / hashTable.size();
    }

private:
    enum EntryType { ACTIVE, EMPTY, DELETED };

    struct HashEntry {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i) {}
    };

    std::vector<HashEntry> hashTable;
    int currentSize;

    bool isActive(int currentPos) const {
        return hashTable[currentPos].info == ACTIVE;
    }

    int findPos(const HashedObj& x) const {
        int offset = 1;
        int currentPos = myHash(x);

        while (hashTable[currentPos].info != EMPTY && hashTable[currentPos].element != x) {
            currentPos += offset;
            offset += 2;
            if (currentPos >= hashTable.size()) {
                currentPos -= hashTable.size();
            }
        }
        return currentPos;
    }

    void rehash() {
        std::vector<HashEntry> oldHashTable = hashTable;

        hashTable.resize(nextPrime(2 * hashTable.size()));
        for (auto& entry : hashTable) {
            entry.info = EMPTY;
        }

        currentSize = 0;
        for (auto& entry : oldHashTable) {
            if (entry.info == ACTIVE) {
                insert(std::move(entry.element));
            }
        }
    }

    size_t myHash(const HashedObj& x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % hashTable.size();
    }
};

#endif // LINEARPROBING_H
