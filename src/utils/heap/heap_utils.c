/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:40:00 by alerradi          #+#    #+#             */
/*   Updated: 2026/08/01 14:42:00 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include <stdlib.h>

void	swap_ptrs(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sift_down(t_heap *heap, t_uint current)
{
	t_uint	smallest;
	t_uint	left;
	t_uint	right;

	smallest = current;
	left = 2 * current + 1;
	right = 2 * current + 2;
	if (left < heap->size
		&& heap->key_of(heap->values[left])
		< heap->key_of(heap->values[smallest]))
		smallest = left;
	if (right < heap->size
		&& heap->key_of(heap->values[right])
		< heap->key_of(heap->values[smallest]))
		smallest = right;
	if (smallest == current)
		return ;
	swap_ptrs(&heap->values[current], &heap->values[smallest]);
	sift_down(heap, smallest);
}

void	*heap_pop(t_heap *heap)
{
	void	*head_value;

	if (heap_is_empty(heap))
		return (NULL);
	head_value = heap->values[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->values[0] = heap->values[heap->size];
		sift_down(heap, 0);
	}
	return (head_value);
}
