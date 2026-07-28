#include "queue.h"
#include <stdlib.h>

void init_queue(t_queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

t_bool  enqueue(t_queue *queue, void *value) {
    //Create new node + initialize it
    t_node *newnode = malloc(sizeof(t_node));
    if (!newnode)
        return false;
    newnode->value = value;
    newnode->next_node = NULL;
    // if there is a tail connect this tail to it 
    if (queue->tail != NULL)
        queue->tail->next_node = newnode;
    queue->tail = newnode;
    //make sure head makes sense
    if(queue->head == NULL)
        queue->head = newnode;
    return true;
}

void     *dequeue(t_queue *queue) {
    t_node *tmp;
    void *value;
    //check for empty queue
    if (!queue->head)
        return (NULL);
    //save the haed of the queue
    tmp = queue->head;
    //save the resulte we re going to return 
    value = tmp->value;
    //take it off
    queue->head = queue->head->next_node;
    if (!queue->head)
        queue->tail = NULL;
    free(tmp);
    return (value);
}