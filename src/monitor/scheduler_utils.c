# include "types.h"
# include "string.h"
# include "init.h"
# include "utils.h"

#include "coder.h"

/* ---------------------------------------------------------
    FIFO schaduler: Sorts by first in 
   --------------------------------------------------------- */
t_ulong fifo_key_extractor(void *value)
{
    t_coder *coder;
    t_ulong time;
    
    coder = (t_coder *)value;
    pthread_mutex_lock(&coder->coder_mutex);
    time = coder->time_last_to_burn_out;
    pthread_mutex_unlock(&coder->coder_mutex);
    /* request the dongle first = older request = should be in the head Min-Heap */
    return (time);
}

/* ---------------------------------------------------------
    EDF schaduler: Sorts by closest burnout 
   --------------------------------------------------------- */
t_ulong edf_key_extractor(void *value)
{
    t_coder *coder;
    t_ulong deadline;
    
    coder = (t_coder *)value;
    /* Deadline is the absolute time they will burn out */
    pthread_mutex_lock(&coder->coder_mutex);
    deadline = coder->last_compile + coder->time_last_to_burn_out;
    pthread_mutex_unlock(&coder->coder_mutex);
    /* Lower deadline = burns out sooner = higher priority in Min-Heap */
    return (deadline);
}

