/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 23:32:30 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/26 03:09:27 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/types.h"
#include <string.h>
#include <stdio.h>




void     assign_scheduler(t_config *config, t_string arg);
void            parser_input(t_config *config, int argc, char **av);
t_string ft_skip_spaces(t_string str);
t_string valid_input(t_string str);
t_ulong         ft_number(t_string element);


#endif