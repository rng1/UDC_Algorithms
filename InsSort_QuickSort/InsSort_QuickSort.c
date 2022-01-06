#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define ARRAYLENGTH 20
#define K 100
#define THRESHOLD 1

void swap(int *x, int *y);
void median3(int v[], int i, int j);
void sort_aux(int v[], int left, int right);
void array_print (int v[], int n);
int is_sorted(int v[], int n);
void ins_sort(int v[], int n);
void quick_sort(int v[], int n);
void init_seed();
void random_init(int v [], int n);
void generate_ascending(int v[], int n);
void generate_descending(int v[], int n);
void test_QuickSort();
void test_InsertionSort();
double time_quickSort(int MAX, int arrayType);
void insertionSort_Tables();
void quickSort_Tables();
double microseconds();



/* MAIN FUNCTION AND ALGORITHMS */
int main()
{
    init_seed();
    test_QuickSort();
    printf("\n");
    test_InsertionSort();

    insertionSort_Tables();
    quickSort_Tables();

    return 0;
}


void ins_sort(int v[], int n)
{
    int i;
    int x, j;

    for (i = 1; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void quick_sort(int v[], int n)
{
    sort_aux(v, 0, n - 1);

    if (THRESHOLD > 1)
        ins_sort(v, n);
}


/* TEST FUNCTIONS */

void test_QuickSort(){

    int v[ARRAYLENGTH];

    printf("Quick sort test:\n\n");

    printf("Random initialization:\n");
    random_init(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("Sorted? %d\nsorting...\n", is_sorted(v,ARRAYLENGTH));
    quick_sort(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("sorted? %d\n\n",is_sorted(v,ARRAYLENGTH));


    printf("Descending initialization:\n");
    generate_descending(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("Sorted? %d\nsorting...\n", is_sorted(v,ARRAYLENGTH));
    quick_sort(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("sorted? %d\n\n",is_sorted(v,ARRAYLENGTH));

    printf("Ascending initialization:\n");
    generate_ascending(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("Sorted? %d\nsorting...\n", is_sorted(v,ARRAYLENGTH));
    quick_sort(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("sorted? %d\n\n",is_sorted(v,ARRAYLENGTH));

}

void test_InsertionSort(){

    int v[ARRAYLENGTH];

    printf("Insertion sort test:\n\n");

    printf("Random initialization:\n");
    random_init(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("Sorted? %d\nsorting...\n", is_sorted(v,ARRAYLENGTH));
    ins_sort(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("sorted? %d\n\n",is_sorted(v,ARRAYLENGTH));


    printf("Descending initialization:\n");
    generate_descending(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("Sorted? %d\nsorting...\n", is_sorted(v,ARRAYLENGTH));
    ins_sort(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("sorted? %d\n\n",is_sorted(v,ARRAYLENGTH));

    printf("Ascending initialization:\n");
    generate_ascending(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("Sorted? %d\nsorting...\n", is_sorted(v,ARRAYLENGTH));
    ins_sort(v,ARRAYLENGTH);
    array_print(v,ARRAYLENGTH);
    printf("sorted? %d\n\n",is_sorted(v,ARRAYLENGTH));

}

void initArray(int v[], int arrayType, int MAX){

    switch (arrayType) {
        case 1: random_init(v,MAX); break;
        case 2: generate_ascending(v,MAX); break;
        case 3: generate_descending(v,MAX); break;
        default: break;
    }
}


/* MEASURING TIME FUNCTIONS */
double time_insertionSort(int MAX, int arrayType)
{
    int v[MAX], i;
    double ta, tb, t, t1, t2;

    initArray(v,arrayType,MAX);

    ta = microseconds();

    ins_sort(v,MAX);
    tb = microseconds();
    t = tb - ta;

    if(t < 500){
        ta = microseconds();
        for(i =0; i < K; i++){
            initArray(v,arrayType,MAX);
            ins_sort(v,MAX);
        }
        tb = microseconds();
        t1 = tb - ta; //more than 500
        ta = microseconds();

        for(i =0; i < K; i++){
            initArray(v,arrayType,MAX);
        }

        tb = microseconds();
        t2 = tb - ta;
        t = (t1 -t2) / K;
    }
    return t;
}



double time_quickSort(int MAX, int arrayType)
{
    //ArrayType: 1:random, 2:ascending, 3:descending
    int v[MAX], i;

    double ta, tb, t, t1, t2;

    initArray(v,arrayType,MAX);

    ta = microseconds();

    quick_sort(v,MAX);

    tb = microseconds();
    t = tb - ta;

    if(t < 500){
        ta = microseconds();
        for(i =0; i < K; i++){

            initArray(v,arrayType,MAX);

            quick_sort(v,MAX);
        }
        tb = microseconds();
        t1 = tb - ta; //more than 500
        ta = microseconds();

        for(i =0; i < K; i++){
            initArray(v,arrayType,MAX);
        }

        tb = microseconds();
        t2 = tb - ta;
        t = (t1 -t2) / K;
    }
    return t;
}

/* TABLES */

void insertionSort_Tables(){
    int i, n=500;
    double t;
    printf("Insertion sort tables:\n------------------------------\n");
    printf("Insertion sort random:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_insertionSort(n,1);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nInsertion sort ascending:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^0.7", "t(n)/n^0.9", "t(n)/n^1.1");
    for (i = 0; i<=6;i++){
        t = time_insertionSort(n,2);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,0.7)),t/(pow(n,0.9)),t/(pow(n,1.1)));
        n=n*2;
    }

    n=500;
    printf("\n\nInsertion sort descending:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.7", "t(n)/n^1.9", "t(n)/n^2.1");
    for (i = 0; i<=6;i++){
        t = time_insertionSort(n,3);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.7)),t/(pow(n,1.9)),t/(pow(n,2.1)));
        n=n*2;
    }
}

void quickSort_Tables(){
    int i, n=500;
    double t;
    printf("\n\nQuick sort tables:\n------------------------------\n");
    printf("Quick sort random with threshold %d:\n", THRESHOLD);
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1", "t(n)/n^1.1", "t(n)/n^1.2");
    for (i = 0; i<=6;i++){
        t = time_quickSort(n,1);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1)),t/(pow(n,1.1)),t/(pow(n,1.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nQuick sort ascending with threshold %d:\n",THRESHOLD);
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n^1", "t(n)/n^1.2");
    for (i = 0; i<=6;i++){
        t = time_quickSort(n,2);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,0.8)),t/(pow(n,1)),t/(pow(n,1.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nQuick sort descending with threshold %d:\n",THRESHOLD);
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.6", "t(n)/n^1.8", "t(n)/n^2");
    for (i = 0; i<=6;i++){
        t = time_quickSort(n,3);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.6)),t/(pow(n,1.8)),t/(pow(n,2)));
        n=n*2;
    }
}



/* AUXILIARY FUNCTIONS */

int is_sorted(int v[], int n)
{
    int i;

    for (i = 0; i < n-1; ++i)
        if (v[i] > v[i+1])
            return 0;

    return 1;
}

void array_print(int v[], int n)
{
    int i;

    printf("[ ");

    for (i = 0; i < n; i++)
        printf("%3d ", v[i]);

    printf("]\n");
}

void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

void median3(int v[], int i, int j)
{
    int mid;

    mid = (i + j)/2;

    if (v[mid] > v[j])
        swap(&v[mid], &v[j]);
    else if (v[mid] > v[i])
        swap(&v[mid], &v[i]);
    else if (v[i] > v[j])
        swap(&v[i], &v[j]);
}

void sort_aux(int v[], int left, int right)
{
    int pivot, i, j;

    if (left + THRESHOLD <= right)
    {
        median3(v, left, right);

        pivot = v[left];
        i = left;
        j = right;

        while (j > i)
        {
            // a lo mejor falla, si no cambiar los do-while a while
            do
                i++;
            while (v[i] < pivot);

            do
                j--;
            while (v[j] > pivot);

            swap(&v[i], &v[j]);
        }

        swap(&v[i], &v[j]); // undo last swap
        swap(&v[left], &v[j]);
        sort_aux(v, left, j - 1);
        sort_aux(v, j + 1, right);
    }
}

double microseconds()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

/* ARRAY CREATION FUNCTIONS */

void init_seed()
{
    srand(time(NULL));
}

void random_init(int v [], int n)
{
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}


void generate_ascending(int v[], int n){
    for (int i = 0; i < n; ++i) {
        v[i]=i;
    }
}

void generate_descending(int v[], int n){
    n-=1;
    for (int i = 0; i <= n; ++i) {
        v[i]=n-i;
    }
}
