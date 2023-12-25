#include <mutex>
#include <thread>

std::mutex mutex1, mutex2;

void ThreadA()
{
    // Creates deadlock problem
    mutex2.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex1.lock();
    mutex2.unlock();
    mutex1.unlock();
}

void ThreadB()
{
    // Creates deadlock problem
    mutex1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex2.lock();
    mutex1.unlock();
    mutex2.unlock();
}

int main()
{
    std::thread t1(ThreadA);
    std::thread t2(ThreadB);

    t1.join();
    t2.join();

    return 0;
}
