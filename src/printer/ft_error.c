/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 23:33:47 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/26 23:34:53 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include <stdio.h>
#include "types.h"
#include <stdlib.h>

void    ft_error(t_string context, t_string msg, int flag)
{
    fprintf(stderr, "[ERROR] %s: %s\n", context, msg);
    if (flag)
        exit(EXIT_FAILURE);
}

