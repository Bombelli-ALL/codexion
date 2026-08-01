/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 22:06:27 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:17:05 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "utils.h"
#include <time.h>
#include <unistd.h>

long	get_time_ms(void)
{
	struct timespec	time;
	long			time_res;

	clock_gettime(CLOCK_MONOTONIC, &time);
	time_res = (time.tv_sec * 1000L) + (time.tv_nsec / 1000000L);
	return (time_res);
}

/* Check if done : system->done*/
void	ft_usleep(long time_ms, t_system *system)
{
	long	start;
	long	remaining;

	start = get_time_ms();
	while (1)
	{
		if (system_is_done(system))
			break ;
		remaining = time_ms - (get_time_ms() - start);
		if (remaining <= 0)
			break ;
		if (remaining > 5)
			usleep(1000);
		else
			usleep(200);
	}
}
