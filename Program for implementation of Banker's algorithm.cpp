#include <stdio.h>
#define n 5
#define m 3

void calculateNeed(int need[n][m], int maxm[n][m],
                   int allot[n][m])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int maxm[][m],
            int allot[][m])
{
    int need[n][m];
    calculateNeed(need, maxm, allot);

    bool finish[n] = {0};
    int safeSeq[n];
    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (found == false)
        {
            printf("System is not in safe state");
            return false;
        }
    }
    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("%d ", safeSeq[i]);
    return true;
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};
    int maxm[][m] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};
    int allot[][m] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};
    isSafe(processes, avail, maxm, allot);
    return 0;
}
