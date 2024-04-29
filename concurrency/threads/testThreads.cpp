#include <thread>
#include <vector>

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