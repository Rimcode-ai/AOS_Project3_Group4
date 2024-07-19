#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"


process_stat *generateProcessStat(process *proc) {
    process_stat *newProcessStat = (process_stat *) malloc(sizeof(process_stat));
    newProcessStat->proc = proc;
    newProcessStat->waitingTime = 0;
    newProcessStat->turnaroundTime = 0;
    newProcessStat->responseTime = 0;
    newProcessStat->runTime = 0;
    newProcessStat->startTime = -1;
    newProcessStat->endTime = -1;
    return newProcessStat;
}

void enqueueArrivingProcesses(queue *processQueue, node **procPtr, int currentTime) {
    while (*procPtr != NULL && ((process *)(*procPtr)->data)->arrivalTime <= currentTime) {
        process *newProcess = (process *)(*procPtr)->data;
        enqueue(processQueue, generateProcessStat(newProcess));
        *procPtr = (*procPtr)->next;
    }
}

void printExecutionOrder(process_stat *scheduledProcess) {
    if (scheduledProcess != NULL) {
        printf("%c", scheduledProcess->proc->pid);
    } else {
        printf("_");
    }
}

void updateScheduledProcess(process_stat *scheduledProcess, int currentTime, linked_list *ll) {
    if (scheduledProcess->startTime == -1) {
        scheduledProcess->startTime = currentTime;
    }
    scheduledProcess->runTime++;
    if (scheduledProcess->runTime >= scheduledProcess->proc->runTime) {
        scheduledProcess->endTime = currentTime;
        addNode(ll, scheduledProcess);
    }
}

average_stats firstComeFirstServeNP(linked_list *processes) {
    int currentTime = 0;

    // Establish the Process Queue
    queue *processQueue = (queue *)createQueue();
    node *procPtr = processes->head;
    
    if (processes->head == NULL) {
        fprintf(stderr,"\nNo procedure exists for scheduling");
    }
    
    // Continue to monitor as long as the currentTime quanta is below 100 or the process queue remains empty
    process_stat *scheduledProcess = NULL;
    linked_list *ll = createLinkedList();
    
    printf("\n\n\n==================================================================================================================================\n");
    printf("\nFirst Come First Serve Algorithm:");
    printf("\nOrder of Processes in Execution: ");
    
    for (currentTime = 0; currentTime < 100 || scheduledProcess != NULL;) {
        // Check for incoming new processes and enqueue them
        while (procPtr != NULL && ((process *)(procPtr->data))->arrivalTime <= currentTime) {
            process *newProcess = (process *)(procPtr->data);
            enqueue(processQueue, generateProcessStat(newProcess));
            procPtr = procPtr->next;
        }

        // To check process queue and schedule it if there is no scheduled process now
        if (scheduledProcess == NULL && processQueue->size > 0) {
            scheduledProcess = (process_stat *) dequeue(processQueue);
        }
        printExecutionOrder(scheduledProcess);

        if (scheduledProcess != NULL) {
            updateScheduledProcess(scheduledProcess, currentTime, ll);
            if (scheduledProcess->endTime == currentTime) {
                scheduledProcess = NULL;
            }
        }

        // Increment time
        currentTime++;
    }

    // Print the Stat of the process
    return printPolicyStat(ll);
}
