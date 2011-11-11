#include <signal.h>
#include "rtx.h"

atomic(char on)
{
    static sigset_t oldmask;
    sigset_t newmask;                  //sigset_t is a bitmap that reserves one bit per signal, indicates which signals are blocked
    if (on) {
        sigemptyset(&newmask);
        sigaddset(&newmask, SIGALRM);  //the alarm signal   //sigaddset adds SIGALRM to the new mask, hence blocking it
        sigaddset(&newmask, SIGINT);   // the CNTRL-C
        sigaddset(&newmask, SIGUSR1);  // the CRT signal
        sigaddset(&newmask, SIGUSR2);  // the KB signal
        sigprocmask(SIG_BLOCK, &newmask, &oldmask);         //section between sigprocmasks is the critical section
    }
    else {
    //unblock the signals                                   //this is done by the next function
    sigprocmask(SIG_SETMASK, &oldmask, NULL);               //restores the old mask
    }
}

/*
sigprocmask(int how,
            sigset_t const * restrict set,
            sigset_t const * restrict oset)

how is of three types, SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK
SIG_BLOCK -> do we want to block?
SIG_UNBLOCK -> do we want to unblock?
SIG_SETMASK -> should new mask replace old mask?

*/
