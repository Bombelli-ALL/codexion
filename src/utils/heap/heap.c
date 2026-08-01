/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:36:01 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 14:41:56 by alerradi         ###   ########.fr       */
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

t_bool	heap_push(t_heap *heap, void *value)
{
	t_uint	current;
	t_uint	parent;

	if (heap->size >= heap->capacity)
		return (false);
	current = heap->size;
	heap->values[current] = value;
	heap->size++;
	while (current > 0)
	{
		parent = (current - 1) / 2;
		if (heap->key_of(heap->values[current])
			>= heap->key_of(heap->values[parent]))
			break ;
		swap_ptrs(&heap->values[current], &heap->values[parent]);
		current = parent;
	}
	return (true);
}
