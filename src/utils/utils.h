/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 23:32:26 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/28 17:45:45 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "types.h"
# include "queue.h"

t_bool  is_space(char c);
int     ft_isdigit(int c);
size_t  ft_strlen(t_string s);
long    get_time_ms(void);
void    ft_usleep(long ms, t_system *system);

#endif