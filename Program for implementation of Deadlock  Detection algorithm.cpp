#include <iostream>
#include <vector>

using namespace std;

const int N = 5;

void detect_deadlock(vector<vector<int>> allocation, vector<vector<int>> request, vector<int> available)
{
    vector<bool> finish(N, false);
    vector<int> work(available);

    for (int i = 0; i < N; ++i)
    {
        if (finish[i])
            continue;

        bool can_allocate = true;
        for (int j = 0; j < N; ++j)
        {
            if (request[i][j] > work[j])
            {
                can_allocate = false;
                break;
            }
        }

        if (can_allocate)
        {
            finish[i] = true;
            for (int j = 0; j < N; ++j)
                work[j] += allocation[i][j];
            i = -1;
        }
    }

    bool deadlock = true;
    for (int i = 0; i < N; ++i)
    {
        if (!finish[i])
        {
            deadlock = false;
            break;
        }
    }

    if (deadlock)
        cout << "Deadlock detected.\n";
    else
        cout << "No deadlock detected.\n";
}

int main()
{
    vector<vector<int>> allocation = {{0, 1, 0, 1, 0},
                                       {2, 0, 0, 0, 3},
                                       {0, 0, 0, 2, 0},
                                       {1, 0, 1, 0, 0},
                                       {0, 1, 0, 0, 0}};
    vector<vector<int>> request = {{0, 0, 0, 0, 0},
                                    {2, 0, 2, 1, 1},
                                    {0, 1, 0, 0, 0},
                                    {1, 1, 0, 0, 1},
                                    {0, 0, 0, 0, 0}};
    vector<int> available = {1, 0, 2, 0, 0};

    detect_deadlock(allocation, request, available);

    return 0;
}
