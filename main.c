/*
 * TITLE: MAXIMUM SUBSEQUENCE SUM
 * SUBTITLE: Practical 1
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * AUTHOR 3:  LOGIN 3:
 * GROUP: 6.1
 * DATE: 25 / 09 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

//#define MAX 1000
#define K 100

/** Algorithms */

int maxSubSum1(int v[], int n) // O(n²)
{
    int i, j;
    long thisSum, maxSum = 0;

    for (i = 0; i < n; i++)
    {
        thisSum = 0;
        for (j = i; j < n; j++)
        {
            thisSum += v[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }

    return maxSum;
}

int maxSubSum2(int v[], int n) // O(n)
{
    int i;
    long thisSum = 0, maxSum = 0;

    for (i = 0; i < n; i++) {
        thisSum += v[i];
        if (thisSum > maxSum)
            maxSum = thisSum;
        else if (thisSum < 0)
            thisSum = 0;
    }

    return maxSum;
}

//Obtains the system time in microseconds
double microseconds()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Set the seed of a new sequence of pseudo-random integers
void init_seed()
{
    srand(time(NULL));
}

// Generate pseudo-random numbers between -n and +n
void random_init(int v [], int n)
{
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}


/*void print_array(int v[], int n)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("]");
}*/
/*void print_program()
{
    int i, a, b;
    int v[MAX];
    printf("test 2\n");
    printf("%33s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (i = 0; i < max + 1; i++) {
        random_init(v, MAX);
        print_array(v, MAX);
        a = maxSubSum1(v, MAX);
        b = maxSubSum2(v, MAX);
        printf("%15d%15d\n", a, b);
    }
}*/


double measure_time1(int MAX)
{
    int v[MAX], i;
    int sum;
    double ta, tb, t, t1, t2;

        init_seed();
        random_init(v,MAX);
        ta = microseconds();
        sum = maxSubSum1(v,MAX);
        //sum = maxSubSum2(v,MAX);
        tb = microseconds();
        t = tb - ta;

        if(t < 500){
            ta = microseconds();
            for(i =0; i < K; i++){
                init_seed();
                random_init(v,MAX);
                sum = maxSubSum1(v,MAX);
                //sum = maxSubSum2(v,MAX);
            }
            tb = microseconds();
            t1 = tb - ta; //MAS DE 500
            ta = microseconds();
            for(i =0; i < K; i++){
                init_seed();
                random_init(v,MAX);
            }
            tb = microseconds();
            t2 = tb - ta;
            t = (t1 -t2) / K;
    }
        return t;
}
double measure_time2(int MAX)
{
    int v[MAX], i;
    int sum;
    double ta, tb, t, t1, t2;

    init_seed();
    random_init(v,MAX);
    ta = microseconds();
    sum = maxSubSum2(v,MAX);
    tb = microseconds();
    t = tb - ta;

    if(t < 500){
        ta = microseconds();
        for(i =0; i < K; i++){
            init_seed();
            random_init(v,MAX);
            sum = maxSubSum2(v,MAX);
        }
        tb = microseconds();
        t1 = tb - ta; //MAS DE 500
        ta = microseconds();
        for(i =0; i < K; i++){
            init_seed();
            random_init(v,MAX);
        }
        tb = microseconds();
        t2 = tb - ta;
        t = (t1 -t2) / K;
    }
    return t;
}


int main(){


    int n=500, i;
    double t;

    /*
    printf("MaxSubSum 1\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");

    for (i = 0; i<=6;i++){
        t = measure_time1(n);
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }*/

    n=500;
    printf("\nMaxSubSum 2\n");
    printf("%6s%18s%18s%18s%18s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2.0", "t(n)/n^2.2");

    for (i = 0; i<=6;i++){
        t = measure_time2(n);
        //printf("%lf\n",measure_time2(n));
        printf("%6d%18.3lf%18.6lf%18.6lf%18.6lf\n",n, t, t/(pow(n,1.8)),t/(pow(n,2)),t/(pow(n,2.2)));
        n=n*2;
    }

    //printf("%lf\n",measure_time1(500));
    //printf("%lf",measure_time2(36000));

    return 0;
}
