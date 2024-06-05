#include <stdio.h>

int main() {
    int n; // Number of Processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivaltime[n], bursttime[n], priority[n], waitingTime[n], turnaroundTime[n];
    int CPU = 0, allTime = 0;

    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("For Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrivaltime[i]);
        printf("Burst Time: ");
        scanf("%d", &bursttime[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
    }

    int ATt[n], PPt[n];
    int NoP = n;
    int i = 0;

    for (i = 0; i < n; i++) {
        PPt[i] = priority[i];
        ATt[i] = arrivaltime[i];
    }

    int LAT = 0;
    for (i = 0; i < n; i++)
        if (arrivaltime[i] > LAT)
            LAT = arrivaltime[i];

    int MAX_P = 0;
    for (i = 0; i < n; i++)
        if (PPt[i] > MAX_P)
            MAX_P = PPt[i];

    int ATi = 0, P1 = PPt[0], P2 = PPt[0];
    int j = -1;
    while (NoP > 0 && CPU <= 1000) {
        for (i = 0; i < n; i++) {
            if ((ATt[i] <= CPU) && (ATt[i] != (LAT + 10))) {
                if (PPt[i] != (MAX_P + 1)) {
                    P2 = PPt[i];
                    j = 1;

                    if (P2 < P1) {
                        j = 1;
                        ATi = i;
                        P1 = PPt[i];
                        P2 = PPt[i];
                    }
                }
            }
        }

        if (j == -1) {
            CPU = CPU + 1;
            continue;
        } else {
            waitingTime[ATi] = CPU - ATt[ATi];
            CPU = CPU + bursttime[ATi];
            turnaroundTime[ATi] = CPU - ATt[ATi];
            ATt[ATi] = LAT + 10;
            j = -1;
            PPt[ATi] = MAX_P + 1;
            ATi = 0;
            P1 = MAX_P + 1;
            P2 = MAX_P + 1;
            NoP = NoP - 1;
        }
    }

    printf("\nProcess_Number\tBurst_Time\tPriority\tArrival_Time\tWaiting_Time\tTurnaround_Time\n\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bursttime[i], priority[i], arrivaltime[i], waitingTime[i], turnaroundTime[i]);
    }

    float AvgWT = 0, AVGTaT = 0;
    for (i = 0; i < n; i++) {
        AvgWT = waitingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }

    printf("Average waiting time = %f\n", AvgWT / n);
    printf("Average turnaround time = %f\n", AVGTaT / n);

    return 0;
}
