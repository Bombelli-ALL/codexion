/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:41:10 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:41:11 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H
# include "types.h"

void	*monitor(void *arg);

/* Schedular fonction:  fifo edf*/
t_ulong	fifo_key_extractor(void *value);
t_ulong	edf_key_extractor(void *value);

/* Schadular manager */
void	secheduler(t_system *system, int flage);
#endif