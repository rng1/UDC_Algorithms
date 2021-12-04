/*
 *    TITLE: PRIM'S ALGORITHM
 * SUBTITLE: Practical 4
 * AUTHOR 1: Martin do Rio Rico          LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez    LOGIN 2: r.naranjo
 * AUTHOR 3: Guillermo Fernandez Sanchez LOGIN 3: guillermo.fernandezs
 *    GROUP: 6.1
 *     DATE: 07 / 12 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <malloc.h>

#include "queue.h"

// TODO(roi) revisar el main y asegurarse de que funcione, también añadir las funciones de los tiempos, lo siento chicos :( 
void prim(matrix m, int nodes, queue *edges);
matrix create_matrix(int n);
void init_matrix(matrix m, int n);
void free_matrix(matrix m, int n);

int main()
{
    queue edges;

    matrix m = create_matrix(5);
    init_matrix(m, 5);

    prim(m, 5, edges);
    show_queue(edges);
    free_matrix(m, 5);

    return 0;
}

void prim(matrix m, int nodes, queue *edges) 
{ 
    int min, i, j, k = 0; 
    edge a; 
    int *closest = (int *) malloc(nodes*sizeof(int)); 
    int *minDistance = (int *) malloc(nodes*sizeof(int)); 

    create_queue(edges); 
    minDistance[0] = -1; 
    
    for (i = 1; i < nodes; i++) 
    { 
        closest[i] = 0; 
        minDistance[i] = m[i][0]; 
    }

    for (i = 0; i < nodes -1; i++) 
    {
        min = 99;

        for (j = 1; j < nodes; j++) 
        {
            if ((0 <= minDistance[j]) && (minDistance[j] < min))
            {
                min = minDistance[j];
                k = j;
            }
        }

        // set edge data and enqueue
        a.x = closest[k];
        a.y = k;
        a.weight = min;

        enqueue(a, edges);
        minDistance[k] = -1;

        for (j = 1; j < nodes; j++)
        {
            if (m[j][k] < minDistance[j])
            {
                minDistance[j]= m[j][k];
                closest[j] = k;
            }
        }
    }

    free(closest); 
    free(minDistance);
}

matrix create_matrix(int n)
{
    int i;
    matrix aux;

    if ((aux = malloc(n * sizeof(int *))) == NULL)
        return NULL;

    for (i = 0; i < n; ++i)
        if ((aux[i] = malloc(n * sizeof(int))) == NULL)
            return NULL;

    return aux;
}

// create an undirected complete graph with random values between int i, j
void init_matrix(matrix m, int n)
{
    int i, j;

    for (i = 0; i < n; ++i)
        for (j = i + 1; j < n; ++j)
            m[i][j] = rand() % n + 1;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j <= i; ++j)
        {
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
        }
    }
}

void free_matrix(matrix m, int n)
{
    int i;

    for (i = 0; i < n; ++i)
        free(m[i]);
    free(m);
}
