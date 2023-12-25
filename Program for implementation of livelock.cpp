#include <atomic>
#include <thread>

std::atomic<bool> flag1(false);
std::atomic<bool> flag2(false);

void ping()
{
    while (true)
    {
        while (flag2.load()) {}
        flag1.store(true);
        // do work...
        flag1.store(false);
    }
}

void pong()
{
    while (true)
    {
        while (flag1.load()) {}
        flag2.store(true);
        // do work...
        flag2.store(false);
    }
}

int main()
{
    std::thread t1(ping);
    std::thread t2(pong);

    t1.join();
    t2.join();

    return 0;
}
