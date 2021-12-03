#include <stdlib.h>
#include <malloc.h>

#include "queue.h"

// TODO(roi) implementar el main y acoplar las funciones del pdf, revisar

int main()
{

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
