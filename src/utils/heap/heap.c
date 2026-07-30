# include "heap.h"
# include <stdlib.h>

static void swap_ptrs(void **a, void **b)
{
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

t_bool heap_init(t_heap *heap, t_uint capacity, t_heap_keyfn key_of) {
    
    heap->values = malloc(sizeof(void *) * capacity);
    if (!heap->values)
        return (false);
    heap->size = 0;
    heap->capacity = capacity;
    heap->key_of = key_of;
    return (true);
}

void heap_destroy(t_heap *heap)
{
    if (heap->values)
    {
        free(heap->values);
        heap->values = NULL;
    }
    heap->size = 0;
    heap->capacity = 0;
}

t_bool heap_is_empty(t_heap *heap)
{
    return (heap->size == 0);
}

void *heap_peek(t_heap *heap)
{
    if (heap_is_empty(heap))
        return (NULL);
    return (heap->values[0]);
}

t_bool heap_push(t_heap *heap, void *value)
{
    t_uint current;
    t_uint parent;

    if (heap->size >= heap->capacity)
        return (false);

    /* Insert at the end */
    current = heap->size;
    heap->values[current] = value;
    heap->size++;

    /* Maintaine the concept of  Min-Heap property (the minimume value always moved to be the parent)*/
    while (current > 0)
    {
        parent = (current - 1) / 2;
        if (heap->key_of(heap->values[current]) >= heap->key_of(heap->values[parent]))
            break; /* Heap property satisfied */
            
        swap_ptrs(&heap->values[current], &heap->values[parent]);
        current = parent;
    }
    return (true);
}

void *heap_pop(t_heap *heap)
{
    void    *head_value;
    t_uint  current;
    t_uint  smallest;
    t_uint  left;
    t_uint  right;

    if (heap_is_empty(heap))
        return (NULL);

    head_value = heap->values[0];
    heap->size--;

    if (heap->size > 0)
    {
        /* Move the last element to the head */
        heap->values[0] = heap->values[heap->size];
        current = 0;

        /* Maintaine the concept of  Min-Heap property (the minimume value always moved to be the parent)*/
        while (1)
        {
            left = 2 * current + 1;
            right = 2 * current + 2;
            smallest = current;

            if (left < heap->size && 
                heap->key_of(heap->values[left]) < heap->key_of(heap->values[smallest]))
                smallest = left;
                
            if (right < heap->size && 
                heap->key_of(heap->values[right]) < heap->key_of(heap->values[smallest]))
                smallest = right;

            if (smallest == current)
                break; /* Heap property satisfied */

            swap_ptrs(&heap->values[current], &heap->values[smallest]);
            current = smallest;
        }
    }
    return (head_value);
}