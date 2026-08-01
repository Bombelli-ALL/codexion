/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 04:12:25 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 04:12:39 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle.h"
#include "init.h"
#include "monitor.h"

void	set_coder_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->coder_mutex);
	coder->finished = true;
	pthread_mutex_unlock(&coder->coder_mutex);
}

t_ulong	get_last_compile(t_coder *coder)
{
	t_ulong	last_compile;

	pthread_mutex_lock(&coder->coder_mutex);
	last_compile = coder->last_compile;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (last_compile);
}

int	get_coder_stats(t_coder *coder)
{
	int	stats;

	stats = 0;
	pthread_mutex_lock(&coder->coder_mutex);
	stats = coder->finished;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (stats);
}
