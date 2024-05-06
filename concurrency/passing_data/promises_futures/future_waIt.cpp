#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double> &&prms, double input)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // simulate work
    double output = sqrt(input);
    prms.set_value(output);
}

int main()
{
    // define input data
    double inputData = 42.0;

    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(computeSqrt, std::move(prms), inputData);

// Student task STARTS here
    auto status = ftr.wait_for(std::chrono::milliseconds(1000)); // wait for 1s - could also just ftr.wait() to wait indefinitely
    if (status == std::future_status::ready) // future is ready
    {
        std::cout << "Result = " << ftr.get() << std::endl;
    }
    else if (status == std::future_status::timeout || status == std::future_status::deferred) // future is not ready
    {
        std::cout << "Result unavailable" << std::endl;
    }
// Student task ENDS here    

    // thread barrier
    t.join();

    return 0;
}
