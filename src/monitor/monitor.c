# include "monitor.h"
# include "init.h"
# include "utils.h"
# include "coder.h"
# include "init.h"

int check_for_burns_out(t_system *system, t_uint *counter) {
    t_uint i;
    long diffrent_time;
    i = 0;
    while(i < system->config.number_of_coders) {
        if (get_coder_stats(&system->coders[i]))
        (*counter)++;
        else {
            diffrent_time = get_time_ms() - get_last_compile(&system->coders[i]);
            if (diffrent_time >= (long)system->config.time_to_burnout){
                system_set_done(system);
                ft_printer(system, system->coders[i].coder_id, MSG_BURNOUT);
            return(1);
            }
        }
        i++;
    }
    return 0;
}

void *monitor(void *arg) {
    t_system *system = (t_system *)arg;
    t_uint    counter;
    
    while (!system_is_done(system)) {
        counter = 0;
        if (check_for_burns_out(system, &counter))
            return NULL;
        if (counter == system->config.number_of_coders){
            system_set_done(system);
            return NULL;
        }
        usleep(500);
    }
    return NULL;
}