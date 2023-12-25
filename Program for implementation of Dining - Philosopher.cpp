#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

const int N = 5;
mutex forks[N];

void dine(int i)
{
    for (int j = 0; j < 10; ++j)
    {
        forks[i].lock();
        forks[(i + 1) % N].lock();
        cout << "Philosopher " << i << " is eating.\n";
        forks[i].unlock();
        forks[(i + 1) % N].unlock();
        cout << "Philosopher " << i << " is thinking.\n";
    }
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < N; ++i)
        threads.emplace_back(thread(dine, i));
    for (auto &t : threads)
        t.join();
    return 0;
}
