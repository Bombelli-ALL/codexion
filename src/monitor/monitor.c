# include "monitor.h"
# include "init.h"
# include "utils.h"
# include "coder.h"
# include "init.h"

int check_for_burns_out(t_system *system, int *counter) {
    int i; 
    i = 0;
    while(i < system->config.number_of_coders) {
        if (get_coder_stats(&system->coders[i]))
        counter++;
        else if ((get_time_ms() - get_time_to_burn(&system->coders[i])) < 0){
            system_set_done(system);
            ft_printer(system, system->coders[i].coder_id, MSG_BURNOUT);
            return(1);
        }
        i++;
    }
    return 0;
}

void *monitor(void *arg) {
    t_system *system = (t_system *)arg;
    int    counter;
    counter = 0;
    
    while (!system_is_done(system)) {
        if (check_for_burns_out(system, &counter))
            return NULL;
        if (counter == system->config.number_of_coders){
            system_set_done(system);
            return NULL;
        }
    }
}