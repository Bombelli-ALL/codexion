/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:57:08 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:57:09 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "dongle.h"
# include "types.h"

typedef struct s_system	t_system;
# define COMPILE 1
# define DEBUG 2
# define REFAC 3

typedef struct s_coder
{
	t_uint				coder_id;
	t_dongle			*left_dongle;
	t_dongle			*right_dongle;
	t_thread			coder_thread;
	t_mutex				coder_mutex;
	t_ulong				last_compile;
	t_ulong				time_to_burn_out;
	t_uint				num_of_done_compiles;
	t_ulong				time_requested_compile;
	t_bool				finished;
	t_system			*system;
}						t_coder;

void					*coder_routine(void *arg);

/* Getters of time_to_burn_out and coder stats done or not */
int						get_coder_stats(t_coder *coder);
t_ulong					get_last_compile(t_coder *coder);
void					set_coder_done(t_coder *coder);

#endif