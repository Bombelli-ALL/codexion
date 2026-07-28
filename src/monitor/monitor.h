#ifndef MONITOR_H
# define MONITOR_H
# include "types.h"

void *monitor(void *arg);


/* Shedular fonction: getter  fifo edf*/
t_bool  get_scheduler(t_system *system);
void    fifo(t_coder *coder, int role);
void    edf(t_coder *coder);
# endif