#ifndef MONITOR_H
# define MONITOR_H
# include "types.h"

void *monitor(void *arg);


/* Schedular fonction:  fifo edf*/
t_ulong fifo_key_extractor(void *value);
t_ulong edf_key_extractor(void *value);

/* Schadular manager */
void    secheduler(t_system *system, int flage);
# endif