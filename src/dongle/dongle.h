/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:50:53 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:50:54 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "types.h"
# include "utils.h"

typedef struct s_dongle
{
	t_uint	dongle_id;
	t_ulong	available_time;
	t_ulong	cooldown;
	t_mutex	dongle_mutex;
	t_mutex	heap_mutex;
	t_heap	heap;
	t_cond	heap_cond;
	t_bool	in_use;
}			t_dongle;

void		dongle_lock(t_coder *coder, t_dongle *dongle);
void		dongle_unlock(t_dongle *dongle);

#endif