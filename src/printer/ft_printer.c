/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:38:58 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:39:31 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init/init.h"
#include "../utils/utils.h" /* For get_time_ms() */
#include "printer.h"
#include <stdio.h>

void	ft_printer(t_system *system, t_uint coder_id, t_string msg)
{
	long	current_time;

	current_time = get_time_ms() - system->start_time;
	pthread_mutex_lock(&system->stdout_mutex);
	if (!system_is_done(system) || msg[0] == 'b')
		printf("%ld %u %s\n", current_time, coder_id, msg);
	pthread_mutex_unlock(&system->stdout_mutex);
}
