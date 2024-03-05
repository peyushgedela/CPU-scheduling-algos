#include <stdio.h>

struct Process
{
    int pid;
    int arrTime;
    int burTime;
    int comTime;
    int turnTime;
    int waitTime;
};

void sjf(struct Process processes[], int n)
{
    int currTime = 0;
    int completed = 0;
    int shortJob = 999;
    int shortest;
    int remTime[n];

    for (int i = 0; i < n; i++)
    {
        remTime[i] = processes[i].burTime;
    }

    while (completed != n)
    {
        shortJob = 999;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrTime <= currTime && processes[i].burTime <= shortJob && remTime[i] != 0)
            {
                shortJob = processes[i].burTime;
                shortest = i;
            }
        }

        currTime += processes[shortest].burTime;
        remTime[shortest] = 0;
        processes[shortest].comTime = currTime;
        completed++;
        processes[shortest].turnTime = processes[shortest].comTime - processes[shortest].arrTime;
        processes[shortest].waitTime = processes[shortest].turnTime - processes[shortest].burTime;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWait Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrTime, processes[i].burTime,
               processes[i].comTime, processes[i].turnTime, processes[i].waitTime);
    }
}

int main()
{
    printf("Enter the no. of processes: ");
    int n;
    scanf("%d", &n);
    struct Process processes[n];
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrTime, &processes[i].burTime);
    }

    sjf(processes, n);

    return 0;
}