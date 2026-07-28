/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 23:32:34 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/27 00:53:53 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../printer/printer.h"
#include "../utils/utils.h"
#include <string.h>
#include <stdlib.h>


t_string ft_skip_spaces(t_string str)
{
    while (is_space(*str))
        ++str;
    return (str);
}

t_string valid_input(t_string str)
{
    t_string digits;

    str = ft_skip_spaces(str);
    if (*str == '+')
        ++str;
    digits = str;
    while (*digits)
    {
        if (!ft_isdigit(*digits))
            ft_error("valid_input", "argument contains a non-digit character", 1);
        ++digits;
    }
    if (ft_strlen(str) == 0)
        ft_error("valid_input", "argument contains no digits", 1);
    if (ft_strlen(str) > 10)
        ft_error("valid_input", "argument exceeds maximum digit length (10)", 1);
    return (str);
}

t_ulong ft_number(t_string element)
{
    t_ulong  number;
    t_string str;

    number = 0;
    str = valid_input(element);
    while (ft_isdigit(*str))
        number = (number * 10) + (*str++ - '0');
    if (number > TIME_UNIT_MAX)
        ft_error("ft_number", "value exceeds TIME_UNIT_MAX", 1);
    return (number);
}

void assign_scheduler(t_config *config, t_string arg)
{
    t_string scheduler;

    scheduler = ft_skip_spaces(arg);
    if (strcmp(scheduler, "fifo") == 0)
        config->scheduler = scheduler;
    else if (strcmp(scheduler, "edf") == 0)
        config->scheduler = scheduler;
    else
        ft_error("parser_input", "unknown scheduler type, expected *fifo* or *edf*", 1);
}

void parser_input(t_config *config, int argc, char **av)
{
    t_ulong coders_count;
    if (argc - 1 != 8)
        ft_error("parser_input", "expected exactly 8 arguments", 1);
    
    coders_count = ft_number(av[1]);
    if (coders_count > 250) 
        ft_error("parser_input", "number_of_coders exceeds safe thread limit (max 250)", 1);
    config->number_of_coders             = (t_uint)coders_count;
    config->time_to_burnout              = ft_number(av[2]);
    config->time_to_compile              = ft_number(av[3]);
    config->time_to_debug                = ft_number(av[4]);
    config->time_to_refactor             = ft_number(av[5]);
    config->number_of_compiles_required  = (t_uint)ft_number(av[6]);
    config->dongle_cooldown              = ft_number(av[7]);
    assign_scheduler(config, av[8]);
    if (config->number_of_coders == 0)
        ft_error("parser_input", "number_of_coders cannot be zero", 1);
    if (config->number_of_compiles_required == 0)
        exit(EXIT_SUCCESS);
}