/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 02:20:52 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/27 01:02:59 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void free_system(t_system *system)
{
    t_uint i;

    if (system->dongles)
    {
        i = 0;
        while (i < system->config.number_of_coders)
            pthread_mutex_destroy(&system->dongles[i++].dongle_mutex);
        free(system->dongles);
    }
    if (system->coders)
    {
        i = 0;
        while (i < system->config.number_of_coders)
            pthread_mutex_destroy(&system->coders[i++].coder_mutex);
        free(system->coders);
    }
    pthread_mutex_destroy(&system->system_mutex);
    pthread_mutex_destroy(&system->stdout_mutex);
}