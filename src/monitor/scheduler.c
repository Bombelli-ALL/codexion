# include "types.h"
# include "string.h"
# include "init.h"
# include "utils.h"
t_bool  get_scheduler(t_system *system) {
    t_string    schedular;

    pthread_mutex_lock(&system->system_mutex);
    schedular = system->config.scheduler;
    pthread_mutex_unlock(&system->system_mutex);
    if (strcmp(schedular, "fifo") == 0)
        return true;
    return false;
}

void    fifo(t_coder *coder, int role){
    return;
}

void    edf(t_coder *coder) {
    return ;
}