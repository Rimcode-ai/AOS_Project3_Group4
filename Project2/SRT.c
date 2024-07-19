/*
 Advance Operating Systems
 Algorithm: Shortest Remaining Time
 */

#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

process_stat *generateProcessStat(process *proc);

// displayQueueContents prints the processes in the queue with their remaining times
void displayQueueContents(queue *q)
{
	if (q->head == NULL)
	{
		return;
	}

	printf("Queue Contains:\n");
	for (node *current = q->head; current != NULL; current = current->next)
	{
		process_stat *ps = (process_stat *)current->data;
		process *p = ps->proc;
		printf("Process Id %c Remaining Time %f\n",p->pid,(p->runTime - ps->runTime));
	}
}

// compareRemainingTime compares the remaining times of two processes for sorting
int compareRemainingTime( void *data1, void *data2)
{
	process_stat *ps1 = (process_stat *)data1;
	process_stat *ps2 = (process_stat *)data2;

	double remainingTime1 = ps1->proc->runTime - ps1->runTime;
	double remainingTime2 = ps2->proc->runTime - ps2->runTime;

	if (remainingTime1 < remainingTime2) {
		return -1;
	} else {
		return 1;
	}
}

// Shortest Remaining Time (SRT) Preemptive Scheduling Implementation
average_stats shortestRemainingTimeP(linked_list *processes)
{
    int timeQuantum = 0;

    // Initialize process queue and execution order list
    queue *processQueue = createQueue();
    linked_list *executionOrder = createLinkedList();

    node *currentProcessNode = processes->head;
    if (currentProcessNode == NULL) {
        fprintf(stderr, "No processes available for scheduling.\n");
        return (average_stats){0}; // Return an empty average_stats struct
    }

    // Initialize the currently scheduled process
    process_stat *currentScheduledProcess = NULL;

    printf("\n\n\n==================================================================================================================================\n");
    printf("\nShortest Remaining Time Algorithm:\n");
    printf("Order of Processes in Execution: ");

    // Main scheduling loop
    while (timeQuantum < 100 || currentScheduledProcess != NULL) {
        if (currentScheduledProcess != NULL) {
            enqueue(processQueue, currentScheduledProcess);
            currentScheduledProcess = NULL;
        }

        // Enqueue newly arriving processes
        while (currentProcessNode != NULL && ((process *)currentProcessNode->data)->arrivalTime <= timeQuantum) {
            process *incomingProcess = (process *)currentProcessNode->data;
            enqueue(processQueue, generateProcessStat(incomingProcess));
            currentProcessNode = currentProcessNode->next;
        }

        // Sort the queue based on the shortest remaining time
        sort(processQueue, compareRemainingTime);

        // Schedule the next process if none is currently scheduled
        if (currentScheduledProcess == NULL && processQueue->size > 0) {
            currentScheduledProcess = (process_stat *)dequeue(processQueue);

            // Skip processes that haven't started before time quantum 100
            while (timeQuantum >= 100 && currentScheduledProcess->startTime == -1) {
                currentScheduledProcess = (process_stat *)dequeue(processQueue);
            }
        }

        // Execute the current scheduled process
        if (currentScheduledProcess != NULL) {
            process *proc = currentScheduledProcess->proc;

            // Display the process ID of the currently running process
            printf("%c", proc->pid);

            // Update process statistics
            if (currentScheduledProcess->startTime == -1) {
                currentScheduledProcess->startTime = timeQuantum;
            }
            currentScheduledProcess->runTime++;

            // If the process completes, record the end time and add to execution order
            if (currentScheduledProcess->runTime >= proc->runTime) {
                currentScheduledProcess->endTime = timeQuantum;
                addNode(executionOrder, currentScheduledProcess);
                currentScheduledProcess = NULL;
            }
        } else {
            // Print an underscore if no process is scheduled
            printf("_");
        }

        // Increment the time quantum
        timeQuantum++;
    }

    // Output the process statistics
    return printPolicyStat(executionOrder);
}
