/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 23:33:39 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/28 22:06:49 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_system	system;

	memset(&system, 0, sizeof(t_system));
	parser_input(&system.config, argc, argv);
	init_system(&system);
	init_thread(&system);
	join_threads(&system);
	free_system(&system);
	return (0);
}
