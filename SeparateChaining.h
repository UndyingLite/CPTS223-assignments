#ifndef SEPARATECHAINING_H
#define SEPARATECHAINING_H

#include <vector>
#include <list>
#include <functional>

template <typename HashedObj>
class ChainingHash {
public:
    explicit ChainingHash(int size = 101) : hashTable(size), currentSize(0) {}

    bool contains(const HashedObj& x) const {
        auto& whichList = hashTable[myHash(x)];
        return std::find(whichList.begin(), whichList.end(), x) != whichList.end();
    }
 void makeEmpty() {
        for (auto& thisList : hashTable) {
            thisList.clear();
        }
        currentSize = 0;
    }

    bool insert(const HashedObj& x) {
        auto& whichList = hashTable[myHash(x)];
        if (contains(x)) return false;
        whichList.push_back(x);

        if (++currentSize > hashTable.size()) {
            rehash();
        }
        return true;
    }

    bool insert(HashedObj&& x) {
        return insert(x);
    }
bool remove(const HashedObj& x) {
        auto& whichList = hashTable[myHash(x)];
        auto itr = std::find(whichList.begin(), whichList.end(), x);

        if (itr == whichList.end()) return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

    double loadFactor() const {
        return static_cast<double>(currentSize) / hashTable.size();
    }
private:
    std::vector<std::list<HashedObj> > hashTable;
    int currentSize;

    void rehash() {
        std::vector<std::list<HashedObj> > oldHashTable = hashTable;

        hashTable.resize(nextPrime(2 * hashTable.size()));
        for (auto& thisList : hashTable) {
            thisList.clear();
        }

        currentSize = 0;
        for (auto& thisList : oldHashTable) {
            for (auto& x : thisList) {
                insert(std::move(x));
            }
        }
    }
        size_t myHash(const HashedObj& x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % hashTable.size();
    }
static size_t nextPrime(size_t n) {
    while (!isPrime(n)) ++n;
    return n;
}

static bool isPrime(size_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (size_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
};

#endif // SEPARATECHAINING_H   