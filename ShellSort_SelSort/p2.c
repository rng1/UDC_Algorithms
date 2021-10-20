#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

#define K 100

//SORTING FUNCTIONS
void shell_sort(int v[], int n)
{
    int increment = n;
    int i, j; // for loop variables
    int aux = 0; // auxiliary variable
    bool stay;
    do
    {
        increment = increment / 2;
        for (i = increment; i < n; i++){
            aux = v[i];
            j = i;
            stay = true;

            while ((j - increment) >= 0 && stay)
            {
                if (aux < v[j - increment])
                {
                    v[j] = v[j - increment];
                    j = j - increment;
                }
                else
                {
                    stay = false;
                }
            }
            v[j] = aux;
        }
    }
    while (increment != 1);
}

void sel_sort(int v[], int n) {
    int minj,minx;

    for (int i=0; i < n-1;++i){
        minj=i;
        minx=v[i];
        for (int j = i+1; j < n; ++j) {
            if (v[j]<minx ){
                minj=j;
                minx=v[j];
            }
        }
        v[minj]=v[i];
        v[i]=minx;
    }
}

//AUXILIARY FUNCTIONS
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

void print_array(int v[], int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("%3d ", v[i]);
    }
    printf("\n");
}

//Obtains the system time in microseconds
double microseconds()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void generateAscending(int v[], int n){
    for (int i = 0; i < n; ++i) {
        v[i]=i;
    }
}

void generateDescending(int v[], int n){
    n-=1;
    for (int i = 0; i <= n; ++i) {
        v[i]=n-i;
    }
}

//TESTING FUNCTIONS
void sel_sortTest(){
    int max = 17;

    int randomArray[max], descending[10] = {10,9,8,7,6,5,4,3,2,1};

    printf("Selection sort test:\n");
    random_init(randomArray, max);
    printf("Random initialization\n");
    print_array(randomArray, max);
    //function isSorted
    sel_sort(randomArray,max);
    print_array(randomArray, max);
    //function isSorted

    printf("Descending initialization\n");
    print_array(descending, 10);
    //function isSorted
    sel_sort(descending,10);
    print_array(descending, 10);
    //function isSorted
}

void shell_sortTest(){
    int max = 17;

    int randomArray[max], descending[10] = {10,9,8,7,6,5,4,3,2,1};

    printf("\nShell sort test:\n");
    random_init(randomArray, max);
    printf("Random initialization\n");
    print_array(randomArray, max);
    //function isSorted
    shell_sort(randomArray,max);
    print_array(randomArray, max);
    //function isSorted

    printf("Descending initialization\n");
    print_array(descending, 10);
    //function isSorted
    shell_sort(descending,10);
    print_array(descending, 10);
    //function isSorted
}

//MEASURING FUNCTIONS
double time_selSort(int MAX, int arrayType)
{
    //ArrayType: 1:random, 2:ascending, 3:descending
    int v[MAX], i;

    double ta, tb, t, t1, t2;

    switch (arrayType) {
        case 1: random_init(v,MAX); break;
        case 2: generateAscending(v,MAX); break;
        case 3: generateDescending(v,MAX); break;
        default: break;
    }

    ta = microseconds();

    //maxSubSum1(v,MAX);
    sel_sort(v,MAX);

    tb = microseconds();
    t = tb - ta;

    if(t < 500){
        ta = microseconds();
        for(i =0; i < K; i++){

            switch (arrayType) {
                case 1: random_init(v,MAX); break;
                case 2: generateAscending(v,MAX); break;
                case 3: generateDescending(v,MAX); break;
                default: break;
            }


            //maxSubSum1(v,MAX);
            sel_sort(v,MAX);

        }
        tb = microseconds();
        t1 = tb - ta; //more than 500
        ta = microseconds();

        //esto que cojones hace
        for(i =0; i < K; i++){

            switch (arrayType) {
                case 1: random_init(v,MAX); break;
                case 2: generateAscending(v,MAX); break;
                case 3: generateDescending(v,MAX); break;
                default: break;
            }


        }

        tb = microseconds();
        t2 = tb - ta;
        t = (t1 -t2) / K;
    }
    return t;
}

double time_ShellSort(int MAX, int arrayType)
{
    int v[MAX], i;
    double ta, tb, t, t1, t2;

    switch (arrayType) {
        case 1: random_init(v,MAX); break;
        case 2: generateAscending(v,MAX); break;
        case 3: generateDescending(v,MAX); break;
        default: break;
    }


    ta = microseconds();

    //maxSubSum2(v,MAX);
    shell_sort(v,MAX);

    tb = microseconds();
    t = tb - ta;

    if(t < 500){
        ta = microseconds();
        for(i =0; i < K; i++){

            switch (arrayType) {
                case 1: random_init(v,MAX); break;
                case 2: generateAscending(v,MAX); break;
                case 3: generateDescending(v,MAX); break;
                default: break;
            }

            //maxSubSum2(v,MAX);
            shell_sort(v,MAX);
        }
        tb = microseconds();
        t1 = tb - ta; //more than 500
        ta = microseconds();

        for(i =0; i < K; i++){
            switch (arrayType) {
                case 1: random_init(v,MAX); break;
                case 2: generateAscending(v,MAX); break;
                case 3: generateDescending(v,MAX); break;
                default: break;
            }
        }

        tb = microseconds();
        t2 = tb - ta;
        t = (t1 -t2) / K;
    }
    return t;
}

//MAIN
int main() {

    int n=500, i;
    double t;

    init_seed();


    sel_sortTest();
    shell_sortTest();


    printf("\n\nSelection sort random:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_selSort(n,1);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nSelection sort ascending:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_selSort(n,2);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nSelection sort descendding:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_selSort(n,3);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }




    //shell sort random (funcion ya creada mas o menos)
    //shell sort ascending
    //shell sort descending

    n=500;
    printf("\n\n\nShell sort random:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_ShellSort(n,1);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nShell sort ascending:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_ShellSort(n,2);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }

    n=500;
    printf("\n\nShell sort descending:\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");
    for (i = 0; i<=6;i++){
        t = time_ShellSort(n,3);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }



    // agrupar shell sort y sel sort en funciones




    return 0;
}
