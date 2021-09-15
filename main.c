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

void print_array(int v[], int n)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("]");
}

/** Figure 3: Obtaining the system time */

/* obtains the system time in microseconds */
double microseconds()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

/** Figure 1: Initialization of an array with pseudo-random integers in the range [−n,..., +n] */

/* set the seed of a new sequence of pseudo-random integers */
void init_seed()
{
    srand(time(NULL));
}

/* generate pseudo-random numbers between -n and +n */
void random_init(int v [], int n)
{
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

/** Tests */

void test1()
{
    int v[1]
}

void test2()
{
    int max = 5;
    int i, a, b;
    int v[max];
    printf("test\n");
    printf("%33s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (i=0; i<max+1; i++) {
        random_init(v, max);
        print_array(v, max);
        a = maxSubSum1(v, max);
        b = maxSubSum2(v, max);
        printf("%15d%15d\n", a, b);
    }
}

int main()
{
    init_seed();
    //test1();
    test2();

    int a, b;

    int v[5] = { -2, -4, 0, 0, 5 };
    a = maxSubSum1(v, 5);
    b = maxSubSum2(v, 5);
    printf("%15d%15d\n", a, b);

    return 0;
}