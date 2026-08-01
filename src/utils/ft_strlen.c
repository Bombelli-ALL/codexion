/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 22:07:21 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:05:20 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>

size_t	ft_strlen(t_string s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
