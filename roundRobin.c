#include <stdio.h>
#include <stdlib.h>

struct ReadyQueue
{
    int pid;
    struct ReadyQueue *next;
};

struct Process
{
    int pid, at, bt, ct, tat, wt;
};

struct ReadyQueue *front, *rear;

void enqueue(int pid)
{
    struct ReadyQueue *temp = malloc(sizeof(struct ReadyQueue));
    temp->pid = pid;
    temp->next = NULL;

    if (front == NULL)
    {
        front = temp;
    }
    else
    {
        rear->next = temp;
    }
    rear = temp;
}

int dequeue()
{
    if (front == NULL)
    {
        return -1;
    }
    else
    {
        struct ReadyQueue *temp = front;
        front = front->next;
        int pid = temp->pid;
        free(temp);
        return pid;
    }
}

void display()
{
    struct ReadyQueue *temp = front;
    while (temp != NULL)
    {
        printf("%d ", temp->pid);
        temp = temp->next;
    }
    printf("\n");
}

void roundRobin(struct Process processes[], int tq, int n)
{
    int completed = 0, currTime = 0, rem[n], inqueue[n];

    for (int i = 0; i < n; i++)
    {
        rem[i] = processes[i].bt;
        inqueue[i] = 0;
    }

    // Sort processes by arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].at > processes[j + 1].at)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    currTime = processes[0].at;

    while (completed != n)
    {

        display();

        // Iterate through all processes and add them to the ready queue if they are ready
        for (int i = 0; i < n; i++)
        {
            if (rem[processes[i].pid] > 0 && processes[i].at <= currTime && inqueue[i] == 0)
            {
                enqueue(processes[i].pid);
                inqueue[i] = 1;
            }
        }

        int k = dequeue();
        if (k == -1)
        {
            currTime++;
            continue;
        }
        else
        {
            if (rem[k] <= tq)
            {
                currTime += rem[k];
                rem[k] = 0;
                inqueue[k] = 0;
            }
            else
            {
                currTime += tq;
                rem[k] -= tq;
                // Iterate through all processes and add them to the ready queue if they are ready
                for (int i = 0; i < n; i++)
                {
                    if (rem[processes[i].pid] > 0 && processes[i].at <= currTime && inqueue[i] == 0)
                    {
                        enqueue(processes[i].pid);
                        inqueue[i] = 1;
                    }
                }
                enqueue(k);
                inqueue[k] = 1;
            }
        }

        if (rem[k] == 0)
        {
            completed++;
            for (int i = 0; i < n; i++)
            {
                if (k == processes[i].pid)
                {
                    processes[i].ct = currTime;
                    processes[i].tat = processes[i].ct - processes[i].at;
                    processes[i].wt = processes[i].tat - processes[i].bt;
                }
            }
        }
    }

    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    float act = 0, atat = 0, awt = 0;
    for (int i = 0; i < n; i++)
    {
        act += processes[i].ct;
        atat += processes[i].tat;
        awt += processes[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }

    act /= n;
    atat /= n;
    awt /= n;

    printf("avg CT: %f\navg TAT:%f\navg WT: %f\n", act, atat, awt);
}

int main()
{
    int n, tq;
    printf("Enter no of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        processes[i].pid = i;
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    printf("Enter time quanta: ");
    scanf("%d", &tq);

    roundRobin(processes, tq, n);

    return 0;
}