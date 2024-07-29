#include "PAGE.h"
//LRU algorithm
void LRU_FUNCTION(LISTOFPAGES* PLLRU) {
    page* FITLRU = PLLRU->HDL;
    page* LRU_PGEVVTON = PLLRU->HDL;
    int lru = FITLRU->LONE;
    while(FITLRU) {
        if(FITLRU->LONE < lru){
            LRU_PGEVVTON = FITLRU;
            lru = FITLRU->LONE;
        }
        FITLRU = FITLRU->next;
    }
    if (DEBUG==1) printf("EVICTED ones :: p[%03d] c:%02d l:%02f\n", LRU_PGEVVTON->pid, LRU_PGEVVTON->CNTER, LRU_PGEVVTON->LONE);
    LRU_PGEVVTON->pid = -1;
    LRU_PGEVVTON->PGENUMBER = -1;
}
