#include "utils.h"
#include <stdlib.h>
#include "init.h"

/* ---------------------------------------------------------
    Initialize Dongles (Mutexes)
--------------------------------------------------------- */
void init_dongles(t_system *system)
{
    t_uint i;

    system->dongles = malloc(sizeof(t_dongle) * system->config.number_of_coders);
    memset((void *)system->dongles, 0,system->config.number_of_coders * sizeof(t_dongle));
    if (!system->dongles)
        ft_error("init_dongles", "Failed to allocate memory for dongles", 1);

    i = 0;
    while (i < system->config.number_of_coders)
    {
        system->dongles[i].dongle_id = i;
        system->dongles[i].in_use = false;
        system->dongles[i].available_time = 0;
        
        if (pthread_mutex_init(&system->dongles[i].dongle_mutex, NULL) != 0)
            ft_error("init_dongles", "Failed to initialize dongle mutex", 1);
        i++;
    }
}

/* ---------------------------------------------------------
    Initialize Coders
--------------------------------------------------------- */
void init_coders(t_system *system)
{
    t_uint i;

    system->coders = (t_coder *)malloc(sizeof(t_coder) * system->config.number_of_coders);
    if (!system->coders)
        ft_error("init_coders", "Failed to allocate memory for coders", 1);

    i = 0;
    while (i < system->config.number_of_coders)
    {
        system->coders[i].coder_id = i + 1; /* Coders usually start at 1 */
        system->coders[i].system = system;
        system->coders[i].num_of_done_compiles = 0;
        system->coders[i].finished = false;
        system->coders[i].last_compile = 0;
        system->coders[i].time_last_to_burn_out = system->config.time_to_burnout;
        
        /* Circularly assign the left and right dongles */
        system->coders[i].left_dongle = &system->dongles[i];
        system->coders[i].right_dongle = &system->dongles[(i + 1) % system->config.number_of_coders];
        
        if (pthread_mutex_init(&system->coders[i].coder_mutex, NULL) != 0)
            ft_error("init_coders", "Failed to initialize coder mutex", 1);
        i++;
    }
}

/* ---------------------------------------------------------
    Primary Initialization Function
--------------------------------------------------------- */
void init_system(t_system *system)
{
    system->done = false;
    
    /* Initialize system-wide mutexes */
    if (pthread_mutex_init(&system->system_mutex, NULL) != 0)
        ft_error("init_system", "Failed to initialize system mutex", 1);
    if (pthread_mutex_init(&system->stdout_mutex, NULL) != 0)
        ft_error("init_system", "Failed to initialize stdout mutex", 1);

        system->done = false;
        init_coders(system);
        init_dongles(system);
}

