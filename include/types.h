/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 03:08:37 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/28 17:26:05 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <stddef.h>

typedef unsigned long   t_ulong;
typedef unsigned int    t_uint;
typedef pthread_t       t_thread;
typedef pthread_mutex_t t_mutex;
typedef char            *t_string;

typedef enum e_bool {
    false,
    true
}   t_bool;

/* ---------------------------------------------------------
    FULL DEFINITIONS (Must be defined before t_system)
--------------------------------------------------------- */
typedef struct s_config {
    t_uint      number_of_coders;
    t_ulong     time_to_burnout;
    t_ulong     time_to_compile;
    t_ulong     time_to_debug;
    t_ulong     time_to_refactor;
    t_uint      number_of_compiles_required;
    t_ulong     dongle_cooldown;
    t_string    scheduler;
}   t_config;

/* ---------------------------------------------------------
    FORWARD DECLARATIONS (For pointers)
--------------------------------------------------------- */
typedef struct s_system t_system;
typedef struct s_dongle t_dongle;
typedef struct s_coder  t_coder;
typedef struct s_queue  t_queue;


# define TIME_UNIT_MAX 4294967295UL

#endif