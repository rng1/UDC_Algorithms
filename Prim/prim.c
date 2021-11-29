#define MAX_SIZE 1600 

typedef int ** matrix; 
typedef struct { 
    int x, y, weight; 
} edge; 
    
typedef edge element_type; 
typedef struct { 
    int front_index, rear_index, size; 
    element_type vector[MAX_SIZE]; 
} queue; 
void create_queue(queue *);
int empty_queue(queue); 
void enqueue(element_type, queue *); 
element_type dequeue(queue *); 
element_type front(queue); 
void show_queue(queue); 

void prim(matrix m, int nodes, queue *edges) 
/* calculate the minimum spanning tree returning 
   the edges of the tree in the ’edges’ queue */
{ 
    int min, i, j, k=0; 
    edge a; 
    int *closest = (int *) malloc(nodes*sizeof(int)); 
    int *minDistance = (int *) malloc(nodes*sizeof(int)); 
    create_queue(edges); 
    minDistance[0] = -1; 
    for(i = 1; i < nodes; i++) { 
        closest[i] = 0; minDistance[i] = m[i][0]; 
    } 
    /* 
    ... 
    */ 
    free(closest); 
    free(minDistance);
}