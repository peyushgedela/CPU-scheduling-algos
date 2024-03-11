#include <stdio.h>

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void priorityScheduling(struct Process processes[], int n) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    int minPriorityProcess;
    int minPriority = 9999;

    while (completed != n) {
        minPriority = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0 &&
                processes[i].priority < minPriority && remainingTime[i] > 0) {
                minPriority = processes[i].priority;
                minPriorityProcess = i;
            }
        }

        currentTime++;
        remainingTime[minPriorityProcess]--;

        if (remainingTime[minPriorityProcess] == 0) {
            completed++;
            processes[minPriorityProcess].completionTime = currentTime;
            processes[minPriorityProcess].turnaroundTime = processes[minPriorityProcess].completionTime - processes[minPriorityProcess].arrivalTime;
            processes[minPriorityProcess].waitingTime = processes[minPriorityProcess].turnaroundTime - processes[minPriorityProcess].burstTime;
        }
    }

    printf("Process Execution Order:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d completed at time %d\n", processes[i].processId, processes[i].completionTime);
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter process ID, arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d %d", &processes[i].processId, &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
    }

    priorityScheduling(processes, n);

    return 0;
}
