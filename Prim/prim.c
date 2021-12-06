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
#include <malloc.h>
#include <math.h>

#include "queue.h"

#define K 100

void prim(matrix m, int nodes, queue *edges);
matrix create_matrix(int n);
void init_matrix(matrix m, int n);
void free_matrix(matrix m, int n);
void test1();
void test2();
void test3();
void init_seed();
void primTables();



int main(){

    init_seed();

    printf("Tests for Prim's algorithmn:\n----------------------------"
           "\nTest1 for the following adjacency matrix:\n");
    test1();
    printf("\nTest2 for the following adjacency matrix:\n");
    test2();
    printf("\nTest2 for the following adjacency matrix:\n");
    test3();
    printf("\n\n");


    primTables();



    return 0;
}

void prim(matrix m, int nodes, queue *edges){

    int min, i, j, k = 0;
    edge a;
    int *closest = (int *) malloc(nodes*sizeof(int));
    int *minDistance = (int *) malloc(nodes*sizeof(int));

    create_queue(edges);
    minDistance[0] = -1;

    for (i = 1; i < nodes; i++){
        closest[i] = 0;
        minDistance[i] = m[i][0];
    }
    for (i = 0; i < nodes -1; i++){
        min = 99;
        for (j = 1; j < nodes; j++){
            if ((0 <= minDistance[j]) && (minDistance[j] < min)){
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

        for (j = 1; j < nodes; j++){
            if (m[j][k] < minDistance[j]){
                minDistance[j]= m[j][k];
                closest[j] = k;
            }
        }
    }
    free(closest);
    free(minDistance);
}

void cpymatrix(int size, int m1[size][size],matrix m2){

    for(int i = 0 ; i < size ; i++) {
        for(int j = 0 ; j < size ; j++){
            m2[i][j]=m1[i][j];
        }
    }

}

void printMatrix(matrix matrice, int n) {
    int x;
    int y;

    for(x = 0 ; x < n ; x++) {
        for(y = 0 ; y < n ; y++){
            if(y==0) printf("%2d", matrice[x][y]);
            else printf("%6d", matrice[x][y]);
        }
        printf("\n");
    }
}

void test1(){
    queue edges;
    matrix m = create_matrix(5);
    int aux[5][5]={
            {0,1,8,4,7},
            {1,0,2,6,5},
            {8,2,0,9,5},
            {4,6,9,0,3},
            {7,5,5,3,0},
    };
    cpymatrix(5,aux,m);
    printMatrix(m,5);

    printf("\nMinimum spanning tree:\n");
    prim(m, 5, &edges);
    show_queue(edges);
    free_matrix(m, 5);
}

void test2(){
    queue edges;
    matrix m = create_matrix(4);
    int aux[4][4]={
            {0,1,4,7},
            {1,0,2,8},
            {4,2,0,3},
            {7,8,3,0},
    };
    cpymatrix(4,aux,m);
    printMatrix(m,4);

    printf("\nMinimum spanning tree:\n");
    prim(m, 4, &edges);
    show_queue(edges);
    free_matrix(m, 4);
}

void test3(){
    queue edges;
    matrix m = create_matrix(7);
    int aux[7][7]={
            { 0, 7,99, 5,99,99,99},
            { 7, 0, 8, 9, 7,99,99},
            {99, 8, 0,99, 5,99,99},
            { 5, 9,99, 0,15, 6,99},
            {99, 7, 5,15, 0, 8, 8},
            {99,99,99, 6, 8, 0,11},
            {99,99,99,99, 9,11, 0},
    };
    cpymatrix(7,aux,m);
    printMatrix(m,7);

    printf("\nMinimum spanning tree:\n");
    prim(m, 7, &edges);
    show_queue(edges);
    free_matrix(m, 7);
}

void init_seed()
{
    srand(time(NULL));
}

double microseconds()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double time_prim(int MAX){

    int i;
    queue edges;
    matrix m = create_matrix(MAX);
    double ta, tb, t, t1, t2;

    init_matrix(m,MAX);

    ta = microseconds();

    prim(m,MAX,&edges);

    tb = microseconds();
    t = tb - ta;

    if(t < 500){
        ta = microseconds();

        for(i =0; i < K; i++){
            init_matrix(m,MAX);
            prim(m,MAX,&edges);
        }
        tb = microseconds();
        t1 = tb - ta; //more than 500
        ta = microseconds();

        for(i =0; i < K; i++){
            init_matrix(m, MAX);
        }

        tb = microseconds();
        t2 = tb - ta;
        t = (t1 -t2) / K;
    }

    free_matrix(m, MAX);
    return t;
}



void primTables(){
    int i, n=10;
    double t;
    printf("Prim's table:\n------------------------------\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.6", "t(n)/n^1.8", "t(n)/n^2.0");
    for (i = 0; i<6;i++){
        t = time_prim(n);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.6)),t/(pow(n,1.8)),t/(pow(n,2)));
        n=n*2;
    }
}



matrix create_matrix(int n){
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

