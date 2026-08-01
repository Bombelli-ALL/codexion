/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:51:08 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 04:17:11 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle.h"
#include "init.h"
#include "monitor.h"

static void	compile_debug_refac(t_coder *coder, int falge);

int	lock_dongles(t_coder *coder)
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
			return (1);
		}
		dongle_lock(coder, coder->left_dongle);
	}
	return (0);
}

void	unlock_dongles(t_coder *coder)
{
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
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->coder_id % 2 == 0)
		ft_usleep(1, coder->system);
	while (!system_is_done(coder->system) && !coder->finished)
	{
		if (lock_dongles(coder))
			break ;
		compile_debug_refac(coder, COMPILE);
		unlock_dongles(coder);
		compile_debug_refac(coder, DEBUG);
		compile_debug_refac(coder, REFAC);
	}
	return (NULL);
}

void	compile(t_coder *coder)
{
	t_system	*system;

	system = coder->system;
	pthread_mutex_lock(&coder->coder_mutex);
	coder->last_compile = get_time_ms();
	pthread_mutex_unlock(&coder->coder_mutex);
	ft_printer(system, coder->coder_id, MSG_COMPILE);
	ft_usleep(system->config.time_to_compile, system);
	coder->num_of_done_compiles += 1;
	if (coder->num_of_done_compiles >= system->config.num_of_req_compile)
		set_coder_done(coder);
}

static void	compile_debug_refac(t_coder *coder, int flag)
{
	t_system	*system;

	system = coder->system;
	if (system_is_done(system))
		return ;
	else if (flag == COMPILE)
		compile(coder);
	else if (flag == DEBUG)
	{
		ft_printer(system, coder->coder_id, MSG_DEBUG);
		ft_usleep(system->config.time_to_debug, system);
	}
	else if (flag == REFAC)
	{
		ft_printer(system, coder->coder_id, MSG_REFACTOR);
		ft_usleep(system->config.time_to_refactor, system);
	}
}
