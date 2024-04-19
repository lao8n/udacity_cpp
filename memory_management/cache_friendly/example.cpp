#include <chrono>
#include <iostream>
// g++ -std=c++11 example.cpp
int main()
{
    // create array 
    const int size = 4;
    static int x[size][size];

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            x[i][j] = i + j;
            std::cout << &x[i][j] << ": i=" << i << ", j=" << j << std::endl;
        }
    }

    // print execution time to console
    auto t2 = std::chrono::high_resolution_clock::now(); // stop time measurement
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    std::cout << "Execution time: " << duration << " nanoseconds" << std::endl;
    // ji = 3927000ns
    // ij = 6641000ns - slower so maybe it is column major
    return 0;
}