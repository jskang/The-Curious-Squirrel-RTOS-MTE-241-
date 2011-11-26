#include <signal.h>
#include "rtx.h"
#include "atomic.h"


void atomic(char on){
	static sigset_t oldmask;
	sigset_t newmask;
    	if (on && !atomic_flag) {
        	sigemptyset(&newmask);
	        sigaddset(&newmask, SIGALRM);
	        sigaddset(&newmask, SIGINT);   // the CNTRL-C
        	sigaddset(&newmask, SIGUSR1);  // the CRT signal
	        sigaddset(&newmask, SIGUSR2);  // the KB signal
	        sigprocmask(SIG_BLOCK, &newmask, &oldmask);
		atomic_flag = 1;
	}

	else {
    		sigprocmask(SIG_SETMASK, &oldmask, NULL);               //restores the old mask
		atomic_flag = 0;
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
