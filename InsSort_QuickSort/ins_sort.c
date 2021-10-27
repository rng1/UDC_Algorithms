#include <stdio.h>

#define ARRAYLENGTH 17

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
                j = j - 1;
            }

            v[j + 1] = x;
    }
}

void array_print (int v[], int n)
{
    int i;

    printf("[ ");

    for (i = 0; i < n; i++)
        printf("%3d ", v[i]);

    printf("]\n");
}

int main() {
    int v[ARRAYLENGTH] = {3,-3,0,17,-5,2,11,13,6,1,7,14,1,-2,5,-14,-2};

    array_print(v, ARRAYLENGTH);
    printf("sorted? 0\nsorting...\n");

    ins_sort(v,ARRAYLENGTH);

    array_print(v, ARRAYLENGTH);
    printf("sorted\n");

    return 0;
}