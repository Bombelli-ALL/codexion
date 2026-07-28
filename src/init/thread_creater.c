#include "init.h"
#include "types.h"
# include "printer.h"
# include "monitor/monitor.h"

void init_thread(t_system *system) {
    int i;

    i = 0;
    if (pthread_create(&system->monitor, NULL, &monitor, (void *)system)){
        system_set_done(system);
        free_system(system);
        ft_error("Thread_creation Faild", "Monitor Thread Faild to create", 1);
    }
    while (i < system->config.number_of_coders){
        if (pthread_create(&system->coders[i].coder_thread, NULL, &coder_routine, (void *)&system->coders[i]) != 0){
            system_set_done(system);
            free_after_fail(system, i);
            free_system(system);
            ft_error("Thread_creation Faild", "thraed has faild", 1);
        }
        i++;   
    }
}


void join_threads(t_system *system) {
    int i;
    t_bool check = false;

    i = 0;
    if (pthread_join(system->monitor, NULL)){
        system_set_done(system);
        free_after_fail(system, system->config.number_of_coders);
        free_system(system);
        ft_error("Thread_creation Faild", "Monitor Thread Faild to create", 1);
    }
    while(i < system->config.number_of_coders){
        if (pthread_join(system->coders[i].coder_thread, NULL) != 0){
            ft_error("[warning]Thread has Faild after all create", "joined faild", 0);
            check = true;
        }
        i++;
    }
    if (check){
        free_system(system);
        ft_error("A thread Faild to join", 
            "The required number of threads aren t complitly joind ", 1);
    }
}

void free_after_fail(t_system *system, int num){
    while (num--)
        if (pthread_join(system->coders[num - 1].coder_thread, NULL) != 0)
            ft_error("[Warning] a athread did not joined", "thread join", 0);
}