#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

const int N = 5;
atomic<int> number[N];
atomic<bool> choosing[N];

int max_number()
{
    int m = number[0];
    for (int i = 1; i < N; ++i)
        m = max(m, number[i]);
    return m;
}

void lock(int i)
{
    choosing[i] = true;
    number[i] = max_number() + 1;
    choosing[i] = false;
    for (int j = 0; j < N; ++j)
    {
        while (choosing[j])
            ;
        while ((number[j] != 0) && ((number[j] < number[i]) || ((number[j] == number[i]) && (j < i))))
            ;
    }
}

void unlock(int i)
{
    number[i] = 0;
}

void thread_func(int i)
{
    for (int j = 0; j < 10; ++j)
    {
        lock(i);
        cout << "Thread " << i << " is in critical section.\n";
        unlock(i);
    }
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < N; ++i)
        threads.emplace_back(thread(thread_func, i));
    for (auto &t : threads)
        t.join();
    return 0;
}
