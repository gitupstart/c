#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};
int compareProcesses(const void* a, const void* b) {
    struct Process* process1 = (struct Process*)a;
    struct Process* process2 = (struct Process*)b;
    if (process1->arrival_time != process2->arrival_time)
        return process1->arrival_time - process2->arrival_time;
    else
        return process1->burst_time - process2->burst_time;
}
void calculateAndDraw(int n, struct Process processes[]) {
    qsort(processes, n, sizeof(struct Process), compareProcesses);
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }
    int completion_time[n];
    int time = 0;
    while (1) {
        int shortest_burst_index = -1;
        int shortest_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && remaining_time[i] < shortest_burst && remaining_time[i] > 0) {
                shortest_burst = remaining_time[i];
                shortest_burst_index = i;
            }
        }
        if (shortest_burst_index == -1)
            break;
        time += remaining_time[shortest_burst_index];
        completion_time[shortest_burst_index] = time;
        remaining_time[shortest_burst_index] = 0;
        processes[shortest_burst_index].waiting_time = time - processes[shortest_burst_index].arrival_time - processes[shortest_burst_index].burst_time;
        if (processes[shortest_burst_index].waiting_time < 0)
            processes[shortest_burst_index].waiting_time = 0;
        processes[shortest_burst_index].turnaround_time = time - processes[shortest_burst_index].arrival_time;
    }
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }
    printf("\nGantt Chart:\n");
    printf(" _________________________________________________________________________\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf("  P%d   |", processes[i].id);
    }
    printf("\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf("   %d   |", completion_time[i]);
    }
    printf("\n");
    printf("\nProcess   Burst time   Arrival time   Waiting time   Turnaround time\n");
    for (int i = 0; i < n; i++) {
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        processes[i].id = i + 1;
    }
    calculateAndDraw(n, processes);
    return 0;}
