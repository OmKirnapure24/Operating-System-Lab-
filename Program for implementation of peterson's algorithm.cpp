#include <iostream>
#include <thread>

using namespace std;

bool flag[2];
int turn;

void petersons_algorithm(int self) {
    int other = 1 - self;
    flag[self] = true;
    turn = other;
    while (flag[other] && turn == other);
}

void release(int self) {
    flag[self] = false;
}

void critical_section(int self) {
    cout << "Process " << self << " is in the critical section.\n";
}

void process(int self) {
    while (true) {
        petersons_algorithm(self);
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
