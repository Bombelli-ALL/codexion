#ifndef PRINTER_H
# define PRINTER_H

# include "../include/types.h"
// #include "init.h"

/* ---------------------------------------------------------
    Message Definitions
--------------------------------------------------------- */
# define MSG_TAKE_DONGLE "has taken a dongle"
# define MSG_COMPILE     "is compiling"
# define MSG_DEBUG       "is debugging"
# define MSG_REFACTOR    "is refactoring"
# define MSG_BURNOUT     "burn out"

/* ---------------------------------------------------------
    Function Prototypes
--------------------------------------------------------- */
void    ft_error(t_string context, t_string msg, int flag);
void    ft_printer(t_system *system, t_uint coder_id, t_string msg);

#endif