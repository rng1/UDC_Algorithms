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
