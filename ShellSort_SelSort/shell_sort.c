#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void shell_sort(int v[], int n);

int main(int argc, char **argv)
{
    int i;
    int array[10] = {10,9,8,7,6,5,4,3,2,1};

    for (i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
    shell_sort(array, 10);

    for (i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

}

void shell_sort(int v[], int n)
{
    int increment = n;
    int i, j; // for loop variables
    int aux = 0; // auxiliary variable
    bool stay;

    do
    {
        increment = increment / 2;
        for (i = increment + 1; i <= n; i++){
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




