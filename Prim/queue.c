#include <stdio.h>
#include "queue.h"

int add_one(int i)
{
    if (i == MAX_SIZE - 1)
        return 0;
    else
        return ++i;
}

void create_queue (queue *Q)
{
    Q->front_index = 0;
    Q->rear_index = MAX_SIZE - 1;
}

void enqueue (element_type d, queue *Q)
{
    if(Q->front_index == add_one(add_one(Q->rear_index)))
        return;
    else
    {
        Q->rear_index = add_one(Q->rear_index);
        Q->vector[Q->rear_index]=d;
        return;
    }
}

element_type dequeue (queue *Q)
{
    edge aux = Q->vector[Q->front_index];
    Q->front_index = add_one(Q->front_index);

    return aux;
}

edge front (queue Q)
{
    return Q.vector[Q.front_index];
}

int empty_queue(queue Q)
{
    return(Q.front_index == add_one(Q.rear_index));
}

void show_queue(queue Q)
{
    edge e;
    int weight = 0, i;

    printf("Edges: ");

    for (i = Q.front_index; i != add_one(Q.rear_index); i = add_one(i))
    {
        e = Q.vector[i];
        weight += e.weight;
        printf("(%d, %d),", e.x, e.y);
    }

    printf("\nWeight: %d\n", weight);
}
