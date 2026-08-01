/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:19:40 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 04:01:05 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include <stdlib.h>

static void	swap_ptrs(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_bool	heap_push(t_heap *heap, void *value)
{
	t_uint	current;
	t_ulong	current_value;
	t_ulong	parent_value;
	t_uint	parent;

	if (heap->size >= heap->capacity)
		return (false);
	current = heap->size;
	heap->values[current] = value;
	heap->size++;
	while (current > 0)
	{
		parent = (current - 1) / 2;
		parent_value = heap->key_of(heap->values[parent]);
		current_value = heap->key_of(heap->values[current]);
		if (current_value >= parent_value)
			break ;
		swap_ptrs(&heap->values[current], &heap->values[parent]);
		current = parent;
	}
	return (true);
}

void	pop_helper(t_heap *heap, t_uint current, t_uint *smallest)
{
	t_uint	left;
	t_uint	right;
	t_ulong	left_value;
	t_ulong	right_value;

	left = 2 * current + 1;
	right = 2 * current + 2;
	left_value = heap->key_of(heap->values[left]);
	right_value = heap->key_of(heap->values[right]);
	if (left < heap->size && left_value < heap->key_of(heap->values[*smallest]))
		*smallest = left;
	if (right < heap->size
		&& right_value < heap->key_of(heap->values[*smallest]))
		*smallest = right;
}

void	*heap_pop(t_heap *heap)
{
	void	*head_value;
	t_uint	current;
	t_uint	smallest;

	if (heap_is_empty(heap))
		return (NULL);
	head_value = heap->values[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->values[0] = heap->values[heap->size];
		current = 0;
		while (1)
		{
			smallest = current;
			pop_helper(heap, current, &smallest);
			if (smallest == current)
				break ;
			swap_ptrs(&heap->values[current], &heap->values[smallest]);
			current = smallest;
		}
	}
	return (head_value);
}
