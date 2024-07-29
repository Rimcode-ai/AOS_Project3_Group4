#include "PAGE.h"
//LfU algorithm
void LFU_FUNCTION(LISTOFPAGES* pLFUl) {
    page* FITLFU = pLFUl->HDL;
    page* PG_LFUEVICTN = pLFUl->HDL;
    int min = FITLFU->CNTER;
    while(FITLFU) {
        if(FITLFU->CNTER < min){
            PG_LFUEVICTN = FITLFU;
            min = FITLFU->CNTER;
        }
        FITLFU = FITLFU->next;
    }
    if (DEBUG==1) printf("EVICTED ones :: p[%03d] c:%02d l:%02f\n", PG_LFUEVICTN->pid, PG_LFUEVICTN->CNTER, PG_LFUEVICTN->LONE);
    PG_LFUEVICTN->pid = -1;
    PG_LFUEVICTN->PGENUMBER = -1;
}
