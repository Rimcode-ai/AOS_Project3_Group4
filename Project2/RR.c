/*
 Advance Operating Systems
 Algorithm: Round Robin
 */

#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

process_stat *generateProcessStat(process *proc);

void addNewProcessesToQueue(queue *process_queue, node **process_pointer, int current_time) {
    while (*process_pointer != NULL && ((process *)(*process_pointer)->data)->arrivalTime <= current_time) {
        enqueue(process_queue, generateProcessStat((process *)(*process_pointer)->data));
        *process_pointer = (*process_pointer)->next;
    }
}

void updateScheduledProcess(node **current_node, int *current_run_time, int time_slice, queue *process_queue) {
    if (*current_node == NULL || *current_run_time == time_slice) {
        *current_run_time = 0;
        *current_node = (*current_node == NULL) ? process_queue->head : (*current_node)->next;
        if (*current_node == NULL) {
            *current_node = process_queue->head;
        }
    }
}

void handleProcessCompletion(process_stat *scheduled_process, process *proc, int current_time, node **current_node, linked_list *time_chart, queue *process_queue, int *current_run_time) {
    if (scheduled_process->runTime >= proc->runTime) {
        scheduled_process->endTime = current_time;
        addNode(time_chart, scheduled_process);
        node *next_node = (*current_node)->next;
        removeNode(process_queue, scheduled_process);
        *current_node = next_node;
        *current_run_time = 0;
    }
}

average_stats roundRobin(linked_list *processes, int time_slice) {
    int current_time = 0;

    queue *process_queue = createQueue();
    linked_list *time_chart = createLinkedList();
    node *process_pointer = processes->head;

    if (process_pointer == NULL) {
        fprintf(stderr, "No processes to schedule\n");
        return (average_stats){0}; // Return an empty average_stats struct
    }

    process_stat *scheduled_process = NULL;
    node *current_node = NULL;
    int current_run_time = 0;

    printf("\n\n\n==================================================================================================================================\n");
    printf("\nRound Robin Algorithm:\n");
    printf("Order of Processes in Execution: ");

    while (current_time < 100 || process_queue->size > 0) {

        if (current_time < 100) {
            addNewProcessesToQueue(process_queue, &process_pointer, current_time);
        }

        updateScheduledProcess(&current_node, &current_run_time, time_slice, process_queue);

        if (current_node != NULL) {
            scheduled_process = (process_stat *)current_node->data;
            process *proc = scheduled_process->proc;

            if (current_time >= 100 && scheduled_process->startTime == -1) {
                free(scheduled_process);
                node *next_node = current_node->next;
                removeNode(process_queue, scheduled_process);
                current_node = next_node;
                current_run_time = 0;
                continue;
            }

            printf("%c", proc->pid);
            current_run_time++;

            if (scheduled_process->startTime == -1) {
                scheduled_process->startTime = current_time;
            }
            scheduled_process->runTime++;

            handleProcessCompletion(scheduled_process, proc, current_time, &current_node, time_chart, process_queue, &current_run_time);
        } else {
            printf("_");
        }

        current_time++;
    }

    return printPolicyStat(time_chart);
}
