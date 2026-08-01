/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:18:37 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 03:20:33 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include <stdlib.h>

t_bool	heap_init(t_heap *heap, t_uint capacity, t_heap_keyfn key_of)
{
	heap->values = malloc(sizeof(void *) * capacity);
	if (!heap->values)
		return (false);
	heap->size = 0;
	heap->capacity = capacity;
	heap->key_of = key_of;
	return (true);
}

void	heap_destroy(t_heap *heap)
{
	if (heap->values)
	{
		free(heap->values);
		heap->values = NULL;
	}
	heap->size = 0;
	heap->capacity = 0;
}

t_bool	heap_is_empty(t_heap *heap)
{
	return (heap->size == 0);
}

void	*heap_peek(t_heap *heap)
{
	if (heap_is_empty(heap))
		return (NULL);
	return (heap->values[0]);
}
