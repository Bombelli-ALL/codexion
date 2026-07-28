/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 23:32:56 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/28 16:29:00 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <unistd.h>
# include <string.h>
# include "printer.h"
# include "types.h"
# include "dongle.h"
# include "coder.h"

struct s_system {
    t_bool      done;
    t_mutex     system_mutex;
    t_mutex     stdout_mutex;
    t_thread    monitor;
    t_coder     *coders;
    t_dongle    *dongles;
    long        start_time;
    t_config    config;
};

void    init_system(t_system *system);
void    free_system(t_system *system);
t_bool  system_is_done(t_system *system);
void    system_set_done(t_system *system);


void init_coders(t_system *system);
void init_dongles(t_system *system);


void free_after_fail(t_system *system, int num);
void join_threads(t_system *system);
void init_thread(t_system *system);

#endif