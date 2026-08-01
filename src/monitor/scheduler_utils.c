/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:41:31 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:49:16 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "init.h"
#include "string.h"
#include "types.h"
#include "utils.h"

/* ---------------------------------------------------------
	FIFO schaduler: Sorts by first in
   --------------------------------------------------------- */
t_ulong	fifo_key_extractor(void *value)
{
	t_coder	*coder;
	t_ulong	time;

	coder = (t_coder *)value;
	pthread_mutex_lock(&coder->coder_mutex);
	time = coder->time_to_burn_out;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (time);
}

/* ---------------------------------------------------------
	EDF schaduler: Sorts by closest burnout
   --------------------------------------------------------- */
t_ulong	edf_key_extractor(void *value)
{
	t_coder	*coder;
	t_ulong	deadline;

	coder = (t_coder *)value;
	pthread_mutex_lock(&coder->coder_mutex);
	deadline = coder->last_compile + coder->time_to_burn_out;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (deadline);
}
