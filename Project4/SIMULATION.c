#include "PAGE.h"

int main(int Argumnt1, char* Argumnt2[]) {

    int TimeStamp = 0;/// simulator timestamp

//paging options
int *PGCoptn = malloc(sizeof(int)*4);
    PGCoptn[0] = 5;
    PGCoptn[1] = 11;
    PGCoptn[2] = 17;
    PGCoptn[3] = 31;


//pointer to the Page
    page *Page_pointer;

    void (*AlgoFunction)(LISTOFPAGES*);
    if (Argumnt1 != 2){
        printf("*******Page Replacement Algo are: FCFS, LRU, LFU, MFU or Random.\n");
        return -1;
    }//checking which function to call
    if(strcmp(Argumnt2[1], "FCFS") == 0){
        AlgoFunction = FCFS_FUNCTION;
    }else if(strcmp(Argumnt2[1], "LRU") == 0){
        AlgoFunction = LRU_FUNCTION;
    }else if(strcmp(Argumnt2[1], "LFU") == 0){
        AlgoFunction = LFU_FUNCTION;
    }else if(strcmp(Argumnt2[1], "MFU") == 0){
        AlgoFunction = MFU_FUNCTION;
    }else if(strcmp(Argumnt2[1], "Random") == 0){
        AlgoFunction = R_FUNCTION;
    }else {
printf("####################################################################\n");
        printf("These are the options to run for simulation : FCFS, LRU, LFU, MFU or Random.\n");
printf("####################################################################\n");

        return -1;
    }

    int swappingInProcess = 0;

    srand(0);
    int i;
    for(i = 0; i < 5; i++) {
        printf("------======= Running simulator   %d ========-------\n", i+1);

        LISTOFPAGES pl;
        Intializing_PGELIst(&pl);
        process Q[Total_PROCESS];
	int i;
        for(i=0;i<Total_PROCESS;i++) {
            Q[i].pid = i;
            Q[i].PGECNTER = PGCoptn[rand()%4];
            Q[i].TIMEARR = rand()%60;
            Q[i].DRUTION = rand() % PROCss_DuraTN;// maximum process duration
            Q[i].PGCRR = 0; // all processes begin with page 0
        }
        qsort(Q,Total_PROCESS,sizeof(process),CMP_ARRtime);

        int index = 0; // index to the start of process queue
        for(TimeStamp = 0; TimeStamp < TotaL_DURATION; TimeStamp++) {

            //looking for new process at sart of every second
            while(index < Total_PROCESS && Q[index].TIMEARR <= TimeStamp) {

		 //To check atleast four pages
                if(PageWhoRFree(&pl,4)) {
			// if its present then bring it in the memory
                    page* p = PAGEfrreeeg(&pl);
                    p->pid = Q[index].pid;
                    p->PGENUMBER = Q[index].PGCRR;
                    p->FTBOUGHT = 1.0*TimeStamp;
                    p->CNTER = 1;
                    p->LONE = TimeStamp;
                    printf("Page::: %d for process id::: %d brought in at ::: %f\n",Q[index].PGCRR,Q[index].pid,p->FTBOUGHT);
                    swappingInProcess++;
                    index++;
                } else break;
            }
	    int i;
            for(i=0;i<10;i++) {
		int j;
		for(j=0;j<index;j++) if(Q[j].DRUTION > 0) {
                    Q[j].PGCRR = PGNUMNXT(Q[j].PGCRR,Q[j].PGECNTER);
                    if(MEMinPGES(&pl,Q[j].pid,Q[j].PGCRR)) {

                        Page_pointer = IDwhozPGrFree(&pl,Q[j].pid,Q[j].PGCRR);
                        if (Page_pointer == NULL){
                            printf("Theres is bug , got null : pid %d page:: %d\n", Q[j].pid, Q[j].PGCRR);
                            return -1;
                        }

                        Page_pointer->CNTER++;
                        Page_pointer->LONE = TimeStamp;
                        continue;
                    }

                    // if we are here then that means we refered a page which is not there in memory. So we need to bring it in.

                    page* pageeeg = PAGEfrreeeg(&pl);
                    if(!pageeeg) {
printf("####################################################################\n");

                        printf("Memory is full, Page list:\n");
                        PageeDisplayingg(&pl);

                        AlgoFunction(&pl);
                        PageeDisplayingg(&pl);

                        pageeeg = PAGEfrreeeg(&pl);
                    }
                    pageeeg->pid = Q[j].pid;
                    pageeeg->PGENUMBER = Q[j].PGCRR;
                    pageeeg->FTBOUGHT = TimeStamp+(0.1*i);
                    pageeeg->LONE = TimeStamp+(0.1*i);
                    pageeeg->CNTER = 0;
                    printf("Page::: %d for process %d brought in at %f\n",Q[j].PGCRR,Q[j].pid,pageeeg->FTBOUGHT);
                    swappingInProcess++;
                }

            }
	    int j;

            for(j=0;j<index;j++) if(Q[j].DRUTION > 0) {
                Q[j].DRUTION--;
                if(Q[j].DRUTION == 0) {
printf("####################################################################\n");
                    printf("Process id %d is done. Memory is getting free ... \n",Q[j].pid);
printf("####################################################################\n");
                    MEMRFree(&pl,Q[j].pid);
                }
            }
            usleep(900);
        }
    }

    printf("Averge number of processes that were successfully swapped in %d\n", (swappingInProcess / 5));
}
