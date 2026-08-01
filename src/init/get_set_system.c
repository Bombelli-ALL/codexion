/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 02:20:17 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:43:03 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

/* ---------------------------------------------------------
	Thread-Safe State Getters & Setters
--------------------------------------------------------- */
t_bool	system_is_done(t_system *system)
{
	t_bool	status;

	pthread_mutex_lock(&system->system_mutex);
	status = system->done;
	pthread_mutex_unlock(&system->system_mutex);
	return (status);
}

void	system_set_done(t_system *system)
{
	pthread_mutex_lock(&system->system_mutex);
	system->done = true;
	pthread_mutex_unlock(&system->system_mutex);
}
