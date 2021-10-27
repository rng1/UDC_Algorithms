#include <stdio.h>

#define ARRAYLENGTH 100
#define THRESHOLD 1

void swap(int *x, int *y);
void median3(int v[], int i, int j);
void sort_aux(int v[], int left, int right);
void array_print (int v[], int n);
int is_sorted(const int v[], int n);
void ins_sort(int v[], int n);
void quick_sort(int v[], int n);

/** MAIN FUNCTION AND ALGORITHMS */
int main()
{
    int v[ARRAYLENGTH] =
            {3, 44, -32, 7, -13, 21, 42, 34, -6, -7, 36, -40, -47, -14, -4, -17, 20, -29,
             -38, 45, -24, -9, 38, -5, 37, 19, -48, 12, -49, -22, -46, 33, -2, 48, -37,
             -31, -16, 18, 31, -11, 8, 15, 10, -12, 27, -35, 30, -45, -27, 22, 46, 47, -25,
             29, -43, 23, -15, 26, 4, -34, 40, -39, 2, -8, -28, 6, -10, 43, 17, 25, 50, 16, 49, -18, -3, -42, 9, 0, 5,
             -30, 14, 11, 13, -21, -44, -23, -19, 41, -26, 28, 32, 39, 24, 35, -33, -36, 1, -1, -50, -41};

    array_print(v, ARRAYLENGTH);
    printf("sorted? %d\n", is_sorted(v, ARRAYLENGTH));

    quick_sort(v,ARRAYLENGTH);

    array_print(v, ARRAYLENGTH);
    printf("sorted? %d\n", is_sorted(v, ARRAYLENGTH));

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

/** AUXILIARY FUNCTIONS */

int is_sorted(const int v[], int n)
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
            do
                i++;
            while (v[i] < pivot);

            while (v[j] > pivot)
                j--;

            swap(&v[i], &v[j]);
        }

        swap(&v[i], &v[j]); // undo last swap
        swap(&v[left], &v[j]);
        sort_aux(v, left, j - 1);
        sort_aux(v, j + 1, right);
    }

}
