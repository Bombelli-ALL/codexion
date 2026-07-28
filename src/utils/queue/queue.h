# include "types.h"

/* ---------------------------------------------------------
    Queus declaration: linked linst
--------------------------------------------------------- */

typedef struct  node
{
    void *value;
    struct node *next_node;
    
} t_node;

typedef struct  s_queue{
    t_node *head;
    t_node *tail;
} t_queue;

void    init_queue(t_queue *queue);
t_bool  enqueue(t_queue *queue, void *value);
int     dequeue(t_queue *queue);

