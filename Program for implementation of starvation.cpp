#include <mutex>
#include <thread>

std::mutex high_priority_mutex;
std::mutex low_priority_mutex;

void HighPriorityThread()
{
    while (true)
    {
        high_priority_mutex.lock();
        // Keep holding the lock for this 'greedy' thread
    }
}

void LowPriorityThread()
{
    while (true)
    {
        if (low_priority_mutex.try_lock())
        {
            // Do some work
            low_priority_mutex.unlock();
        }
    }
}

int main()
{
    std::thread t1(HighPriorityThread);
    std::thread t2(LowPriorityThread);

    t1.join();
    t2.join();

    return 0;
}
