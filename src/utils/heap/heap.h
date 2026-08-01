/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerradi <alerradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 00:00:00 by alerradi          #+#    #+#             */
/*   Updated: 2026/07/29 23:48:29 by alerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include "types.h"

typedef t_ulong		(*t_heap_keyfn)(void *value);

typedef struct s_heap
{
	void			**values;
	t_uint			size;
	t_uint			capacity;
	t_heap_keyfn	key_of;
}					t_heap;

t_bool				heap_init(t_heap *heap, t_uint capacity,
						t_heap_keyfn key_of);
t_bool				heap_push(t_heap *heap, void *value);
void				*heap_pop(t_heap *heap);
void				*heap_peek(t_heap *heap);
t_bool				heap_is_empty(t_heap *heap);
void				heap_destroy(t_heap *heap);

#endif