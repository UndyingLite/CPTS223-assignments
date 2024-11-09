#include "OpenMP.h"
#include "Heap.h"
#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

void runOpenMP()
{
    hello_world();
    calSum();
    calMax();
}

void runHeap()
{
    int data_size = 10000;
    int *data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = rand() % data_size;
    }

    // Create an instance of Heap<int>
    auto *hp = new Heap<int>();
    for (int i = 0; i < data_size; ++i)
    {
        hp->push(data[i]);
    }

    // Sort these values using STL
    std::vector<int> vect(data, data + data_size);
    std::sort(vect.begin(), vect.end());

    // Compare the pop result with the values sorted by STL
    // If the two required functions are correct, the assertions should pass
    for (int i = 0; i < data_size; ++i)
    {
        assert(vect[i] == hp->pop());
    }

    std::cout << "(3) Test runHeap() assert pass!" << std::endl;

    // Clean up the allocated memory
    delete[] data;
    delete hp;
}

int main(int argc, char *argv[])
{
    runOpenMP();
    runHeap();
    return 0;
}
