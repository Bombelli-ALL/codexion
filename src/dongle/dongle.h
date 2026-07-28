#ifndef DONGLE_H
# define DONGLE_H

# include "types.h"
# include "utils.h"

typedef struct s_dongle {
    t_uint      dongle_id;
    t_ulong     available_time;
    t_mutex     dongle_mutex;
    t_bool      in_use;
    t_queue     *queue;
}   t_dongle;

void    dongle_lock(t_dongle *dongle);
void    dongle_unlock(t_dongle *dongle);

#endif