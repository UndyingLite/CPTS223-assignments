#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
  public:
    explicit ChainingHash( int size = 101 ) : currentSize( 0 )
      { theLists.resize( nextPrime(size) ); }

    bool contains( const HashedObj & x ) const
    {
        auto & whichList = theLists[myhash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }

    void makeEmpty( )
    {
        for (auto & thisList : theLists)
            thisList.clear();
        currentSize = 0;
    }

    bool insert( const HashedObj & x )
    {
        auto & whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false;

        whichList.push_back(x);
        ++currentSize;

        if (loadFactor() >= 1.0)
            rehash();

        return true;
    }
    
    bool insert( HashedObj && x )
    {
        auto & whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false;

        whichList.push_back(std::move(x));
        ++currentSize;

        if (loadFactor() >= 1.0)
            rehash();

        return true;
    }

    bool remove( const HashedObj & x )
    {
        auto & whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);

        if (itr == end(whichList))
            return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

    double readLoadFactor() const 
    {
        return loadFactor();
    }

    int readCurrentSize() const 
    {
        return currentSize;
    }

    int readArraySize() const 
    {
        return theLists.size();
    }

  private:
    vector<list<HashedObj> > theLists;   // The array of Lists
    int currentSize;

    void rehash( )
    {
        vector<list<HashedObj> > oldLists = theLists;

        // Create new double-sized, empty table.
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto & thisList : theLists)
            thisList.clear();

        // Copy table over.
        currentSize = 0;
        for (auto & thisList : oldLists)
            for (auto & x : thisList)
                insert(std::move(x));
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % theLists.size();
    }

    double loadFactor() const
    {
        return static_cast<double>(currentSize) / theLists.size();
    }
};

#endif
