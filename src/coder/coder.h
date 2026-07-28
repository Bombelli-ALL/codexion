#ifndef CODER_H
# define CODER_H

# include "types.h"
# include "dongle.h"

typedef struct s_system t_system;

typedef struct s_coder {
    t_uint      coder_id;
    t_dongle    *left_dongle;
    t_dongle    *right_dongle;
    t_thread    coder_thread;
    t_mutex     coder_mutex;
    t_ulong     last_compile;
    t_ulong     time_last_to_burn_out;
    t_uint      num_of_done_compiles;
    t_bool      finished;
    t_system    *system;
}   t_coder;

void    *coder_routine(void *arg);

/* Getters of time_to_burn_out and coder stats done or not */
int     get_coder_stats(t_coder *coder);
t_ulong     get_time_to_burn(t_coder *coder);

#endif