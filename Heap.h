//***************************************************************************//
//** Simple Heap implementation
//***************************************************************************//
#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <vector>
#include <stdexcept> // std::out_of_range
#include <limits>
#include <string>

/**
* Declaring Heap class
*/
template <typename T>
class Heap
{
private:
    std::vector<T> _items; // Main vector of elements for heap storage. The first item in the array is a placeholder.

    /**
    * Percolates the item specified at by index down
    * into its proper location within a heap.
    * Used for dequeue operations and array to heap conversions
    */
    void percolateDown(unsigned int hole)
    {
        T temp = _items[hole];
        unsigned int child;

        while (hole * 2 < _items.size())
        {
            child = hole * 2;

            // Choose the smaller child if two children exist.
            if (child + 1 < _items.size() && _items[child + 1] < _items[child])
            {
                child++;
            }

            // If the child is smaller than the current item, move the child up.
            if (_items[child] < temp)
            {
                _items[hole] = _items[child];
                hole = child;
            }
            else
            {
                break;
            }
        }

        _items[hole] = temp;
    }

    /**
    * Add a new item to the end of the heap and percolate up this item to fix heap property
    */
    void percolateUp(T item)
    {
        _items.push_back(item);
        unsigned int hole = _items.size() - 1;

        // Move the hole upwards until the heap property is restored.
        while (hole > 1 && item < _items[hole / 2])
        {
            _items[hole] = _items[hole / 2];
            hole /= 2;
        }

        _items[hole] = item;
    }

public:
    /**
    * Default empty constructor
    */
    Heap()
    {
        _items.push_back(std::numeric_limits<T>::min()); // Push a placeholder for the first item in the array
    }

    /**
    * Adds a new item to the heap
    */
    void push(T item)
    {
        percolateUp(item);
    }

    /**
    * Removes minimum value from heap
    */
    T pop()
    {
        long unsigned int last_index = _items.size() - 1; // Calculate last item index
        int root_index = 1; // Root index (for readability)
        if (size() == 0)
        {
            throw std::out_of_range("pop() - No elements in heap");
        }
        T minItem = _items[root_index];
        _items[root_index] = _items[last_index]; // Move last item to root
        _items.pop_back(); // Erase last element entry
        if (size() > 0)
        { 
            // Only runs if the heap isn't empty now
            percolateDown(1); // Fix heap property
        }
        return minItem;
    }

    /**
    * Returns true if heap is empty, else false
    */
    bool empty() const
    {
        return _items.size() == 1;
    }

    /**
    * Returns current quantity of elements in heap (N)
    */
    long unsigned int size() const
    {
        return _items.size() - 1;
    }

    /**
    * Return heap data in order from the _items vector
    */
    std::string to_string() const
    {
        std::string ret = "";
        for (unsigned int i = 1; i < _items.size(); i++)
        {
            ret += std::to_string(_items[i]) + " ";
        }
        return ret;
    }
};

#endif
