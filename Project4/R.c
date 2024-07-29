#include "PAGE.h"
//random algorithm
void R_FUNCTION(LISTOFPAGES* PRM) {
    page* FITR = PRM->HDL;
    page* PGRNDMEVC = PRM->HDL;
    int CNTER = 0;
    int r = rand() % Toal_PAGE;
    while(FITR) {
        if(FITR->pid>0 && CNTER < r){
            PGRNDMEVC = FITR;
        }
        FITR = FITR->next;
        CNTER++;
    }
    if (DEBUG==1) printf("EVICTED ones :: p[%03d] c:%02d l:%02f\n", PGRNDMEVC->pid, PGRNDMEVC->CNTER, PGRNDMEVC->LONE);
    PGRNDMEVC->pid = -1;
    PGRNDMEVC->PGENUMBER = -1;
}
