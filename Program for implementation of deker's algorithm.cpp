#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> flag[2];
atomic<int> turn;

void dekkers_algorithm(int self) {
    int other = 1 - self;
    flag[self] = true;
    while (flag[other]) {
        if (turn != self) {
            flag[self] = false;
            while (turn != self);
            flag[self] = true;
        }
    }
}

void release(int self) {
    int other = 1 - self;
    turn = other;
    flag[self] = false;
}

void critical_section(int self) {
    cout << "Process " << self << " is in the critical section.\n";
}

void process(int self) {
    while (true) {
        dekkers_algorithm(self);
        critical_section(self);
        release(self);
    }
}

int main() {
    thread t0(process, 0);
    thread t1(process, 1);
    t0.join();
    t1.join();
    return 0;
}
