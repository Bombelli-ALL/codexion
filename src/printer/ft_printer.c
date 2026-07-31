#include "printer.h"
#include "../utils/utils.h" /* For get_time_ms() */
#include <stdio.h>
#include "../init/init.h"

void    ft_printer(t_system *system, t_uint coder_id, t_string msg)
{
    long    current_time;

    // if (system->done == true)
    //     return ;
    current_time = get_time_ms() - system->start_time;

    pthread_mutex_lock(&system->stdout_mutex); 
    if (!system->done || msg[0] == 'b')
        printf("%ld %u %s\n", current_time, coder_id, msg);
    /* 5. Unlock the mutex */
    pthread_mutex_unlock(&system->stdout_mutex);
}