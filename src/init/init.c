/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:43:15 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:49:16 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "monitor.h"
#include "utils.h"
#include <stdlib.h>

/* ---------------------------------------------------------
	Initialize Dongles (Mutexes)
--------------------------------------------------------- */

void	mutex_init(t_system *system, t_uint i)
{
	if (pthread_mutex_init(&system->dongles[i].dongle_mutex, NULL) != 0)
		ft_error("init_dongles", "Failed to initialize dongle mutex", 1);
	if (pthread_mutex_init(&system->dongles[i].heap_mutex, NULL) != 0)
		ft_error("init_dongles", "Failed to initialize heap mutex", 1);
	if (pthread_cond_init(&system->dongles[i].heap_cond, NULL) != 0)
		ft_error("init_dongles",
			"Failed to initialize dongle condition variable", 1);
}

void	init_dongles(t_system *system)
{
	t_uint			i;
	t_heap_keyfn	schaduler;

	if (strcmp(system->config.scheduler, "fifo") == 0)
		schaduler = fifo_key_extractor;
	else
		schaduler = edf_key_extractor;
	system->dongles = malloc(sizeof(t_dongle)
			* system->config.number_of_coders);
	memset((void *)system->dongles, 0, system->config.number_of_coders
		* sizeof(t_dongle));
	if (!system->dongles)
		ft_error("init_dongles", "Failed to allocate memory for dongles", 1);
	i = 0;
	while (i < system->config.number_of_coders)
	{
		system->dongles[i].dongle_id = i + 1;
		system->dongles[i].in_use = false;
		system->dongles[i].available_time = 0;
		system->dongles[i].cooldown = system->config.dongle_cooldown;
		heap_init(&system->dongles[i].heap, 2, schaduler);
		mutex_init(system, i);
		i++;
	}
}

/* ---------------------------------------------------------
	Initialize Coders
--------------------------------------------------------- */
void	init_coders(t_system *system)
{
	t_uint	i;

	system->coders = (t_coder *)malloc(sizeof(t_coder)
			* system->config.number_of_coders);
	if (!system->coders)
		ft_error("init_coders", "Failed to allocate memory for coders", 1);
	i = 0;
	while (i < system->config.number_of_coders)
	{
		system->coders[i].coder_id = i + 1;
		system->coders[i].system = system;
		system->coders[i].num_of_done_compiles = 0;
		system->coders[i].finished = false;
		system->coders[i].last_compile = 0;
		system->coders[i].time_to_burn_out = system->config.time_to_burnout;
		system->coders[i].left_dongle = &system->dongles[i];
		system->coders[i].right_dongle = &system->dongles[(i + 1)
			% system->config.number_of_coders];
		if (pthread_mutex_init(&system->coders[i].coder_mutex, NULL) != 0)
			ft_error("init_coders", "Failed to initialize coder mutex", 1);
		i++;
	}
}

/* ---------------------------------------------------------
	Primary Initialization Function
--------------------------------------------------------- */
void	init_system(t_system *system)
{
	system->done = false;
	if (pthread_mutex_init(&system->system_mutex, NULL) != 0)
		ft_error("init_system", "Failed to initialize system mutex", 1);
	if (pthread_mutex_init(&system->stdout_mutex, NULL) != 0)
		ft_error("init_system", "Failed to initialize stdout mutex", 1);
	system->done = false;
	init_dongles(system);
	init_coders(system);
}
