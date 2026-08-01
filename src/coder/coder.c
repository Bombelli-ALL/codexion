/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:51:08 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 04:05:08 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle.h"
#include "init.h"
#include "monitor.h"

static void	compile_debug_refac(t_coder *coder, int falge);

int	get_coder_stats(t_coder *coder)
{
	int	stats;

	stats = 0;
	pthread_mutex_lock(&coder->coder_mutex);
	stats = coder->finished;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (stats);
}

t_ulong	get_last_compile(t_coder *coder)
{
	t_ulong	last_compile;

	pthread_mutex_lock(&coder->coder_mutex);
	last_compile = coder->last_compile;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (last_compile);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->coder_id % 2 == 0)
		ft_usleep(1, coder->system);
	while (!system_is_done(coder->system) && !coder->finished)
	{
		if (coder->coder_id % 2 == 0)
		{
			dongle_lock(coder, coder->left_dongle);
			dongle_lock(coder, coder->right_dongle);
		}
		else
		{
			dongle_lock(coder, coder->right_dongle);
			if (coder->left_dongle == coder->right_dongle)
			{
				ft_usleep(coder->system->config.time_to_burnout + 20,
					coder->system);
				break ;
			}
			dongle_lock(coder, coder->left_dongle);
		}
		compile_debug_refac(coder, COMPILE);
		if (coder->coder_id % 2 == 0)
		{
			dongle_unlock(coder->right_dongle);
			dongle_unlock(coder->left_dongle);
		}
		else
		{
			dongle_unlock(coder->left_dongle);
			dongle_unlock(coder->right_dongle);
		}
		compile_debug_refac(coder, DEBUG);
		compile_debug_refac(coder, REFAC);
	}
	return (NULL);
}

static void	compile_debug_refac(t_coder *coder, int flage)
{
	t_system	*system;

	system = coder->system;
	if (system_is_done(system))
		return ;
	else if (flage == COMPILE)
	{
		pthread_mutex_lock(&coder->coder_mutex);
		coder->last_compile = get_time_ms();
		pthread_mutex_unlock(&coder->coder_mutex);
		ft_printer(system, coder->coder_id, MSG_COMPILE);
		ft_usleep(system->config.time_to_compile, system);
		coder->num_of_done_compiles += 1;
		if (coder->num_of_done_compiles >= system->config.num_of_req_compile)
			set_coder_done(coder);
	}
	else if (flage == DEBUG)
	{
		ft_printer(system, coder->coder_id, MSG_DEBUG);
		ft_usleep(system->config.time_to_debug, system);
	}
	else if (flage == REFAC)
	{
		ft_printer(system, coder->coder_id, MSG_REFACTOR);
		ft_usleep(system->config.time_to_refactor, system);
	}
}

void	set_coder_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->coder_mutex);
	coder->finished = true;
	pthread_mutex_unlock(&coder->coder_mutex);
}
