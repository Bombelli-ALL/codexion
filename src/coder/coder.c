# include "coder.h"
# include "init.h"
# include "monitor/monitor.h"

int get_coder_stats(t_coder *coder) {
    int stats;

    stats = 0;
    pthread_mutex_lock(&coder->coder_mutex);
    stats = coder->finished;
    pthread_mutex_unlock(&coder->coder_mutex);
    return (stats);
}

t_ulong get_time_to_burn(t_coder *coder) {
    t_ulong time_last;

    pthread_mutex_lock(&coder->coder_mutex);
    time_last = coder->time_last_to_burn_out;
    pthread_mutex_unlock(&coder->coder_mutex);
    return (time_last); 
}

void    *coder_routine(void *arg) {
    t_coder *coder;
    coder = (t_coder *)arg;

    while (!system_is_done(coder->system) && !coder->finished){
        if (get_scheduler(coder->system)){
            fifo(coder, 1);
        }
        else
            edf(coder);
    }
}