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

void priorityScheduling(struct Process processes[], int n){
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    int minPriority = 999;
    int minpprocess = 0;

    while(completed != n) {
        minPriority = 999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].priority < minPriority && remainingTime[i] > 0) {
                minPriority = processes[i].priority;
                minpprocess = i;
            }
        }

        currentTime += processes[minpprocess].burstTime;
        remainingTime[minpprocess] = 0;
        completed++;
        processes[minpprocess].completionTime = currentTime;
        processes[minpprocess].turnaroundTime = processes[minpprocess].completionTime - processes[minpprocess].arrivalTime;
        processes[minpprocess].waitingTime = processes[minpprocess].turnaroundTime - processes[minpprocess].burstTime;
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

int main(){
    
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