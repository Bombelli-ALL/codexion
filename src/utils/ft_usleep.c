/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 22:06:27 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/30 02:17:15 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include "utils.h"
#include "init.h"


long	get_time_ms(void)
{
	struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    long time_res = (time.tv_sec * 1000L) + (time.tv_nsec / 1000000L);
	return (time_res);
}

void	ft_usleep(long time_ms, t_system *system)
{
	long	start;
	long	remaining;

	start = get_time_ms();
	while (1)
	{
		/* Check if done : system->done*/
		if(system_is_done(system))
			break;
		remaining = time_ms - (get_time_ms() - start);
		if (remaining <= 0)
			break ;
		if (remaining > 5)
			usleep(1000);
		else
			usleep(200);
	}
}