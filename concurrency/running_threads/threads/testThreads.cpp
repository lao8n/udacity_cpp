#include <thread>
#include <vector>

// first num includes main thread, so 5 threads including the 4 additional threads
int main()
{
    std::vector<std::thread> threads;

    int nThreads = 4;
    for (int i = 0; i < nThreads; i++)
    {
        threads.emplace_back(std::thread([](){ // lambda function
            while (true); }));
    }

    // threads are running in parallel from main program
    std::for_each(threads.begin(), threads.end(), [](std::thread &t)
                  { t.join(); });

    return 0;
}