/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:49:46 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 04:09:25 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "monitor.h"
#include "printer.h"
#include "types.h"

static t_bool	join_thread_coders(t_system *system);

void	init_thread(t_system *system)
{
	t_uint	i;

	i = 0;
	system->start_time = get_time_ms();
	while (i < system->config.number_of_coders)
		system->coders[i++].last_compile = system->start_time;
	i = 0;
	while (i < system->config.number_of_coders)
	{
		if (pthread_create(&system->coders[i].coder_thread, NULL,
				&coder_routine, (void *)&system->coders[i]) != 0)
		{
			system_set_done(system);
			free_after_fail(system, i);
			free_system(system);
			ft_error("Thread_creation Faild", "thraed has faild", 1);
		}
		i++;
	}
	if (pthread_create(&system->monitor, NULL, &monitor, (void *)system))
	{
		system_set_done(system);
		free_system(system);
		ft_error("Thread_creation Faild", "Monitor Thread Faild to create", 1);
	}
}

void	join_threads(t_system *system)
{
	t_bool	check;

	check = join_thread_coders(system);
	system_set_done(system);
	if (pthread_join(system->monitor, NULL))
	{
		system_set_done(system);
		free_after_fail(system, system->config.number_of_coders);
		free_system(system);
		ft_error("Thread_creation Faild", "Monitor Thread Faild to create", 1);
	}
	if (check == true)
	{
		free_system(system);
		ft_error("A thread Faild to join",
			"The required number of threads aren t complitly joind ", 1);
	}
}

static t_bool	join_thread_coders(t_system *system)
{
	t_uint	i;
	t_bool	check;

	check = false;
	i = 0;
	while (i < system->config.number_of_coders)
	{
		if (pthread_join(system->coders[i++].coder_thread, NULL) != 0)
		{
			ft_error("[warning]Thread has Faild after all create",
				"joined faild", 0);
			check = true;
		}
	}
	return (check);
}

void	free_after_fail(t_system *system, int num)
{
	while (num--)
		if (pthread_join(system->coders[num].coder_thread, NULL) != 0)
			ft_error("[Warning] a athread did not joined", "thread join", 0);
}
