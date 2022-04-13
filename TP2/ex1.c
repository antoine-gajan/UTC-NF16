#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ex1.h"

int fact1(int n)
{
    if (n < 0)
    {
        printf("La factorielle est définie pour des nombres négatifs.");
    }
    int fact = 1;
    for (int i = 2; i <= n; i++)
    {
        fact *= i;
    }
    return fact;
}

int fact2(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * fact2(n - 1);
    }
}

int** matrice_extraite(int **tab, int n, int i)
{
    int **matrice = malloc((n-1) * sizeof(*matrice));
    for (int k = 0; k < n - 1; k ++)
    {
        int *ligne = malloc((n-1) * sizeof(**matrice));
        *(matrice + k) = ligne;
    }
    for (int k = 1; k < n; k++)
    {
        for (int l = 0; l < i; l++)
        {
            *(*(matrice+k-1)+l) = tab[k][l];
        }
        for (int l = i + 1; l < n; l++)
        {
            *(*(matrice+k-1)+l-1) = tab[k][l];
        }
    }
    return matrice;
}

int determinant(int tab[][], int n)
{
    if (n == 1)
    {
        return tab[0][0];
    }
    else
    {
        int det = 0;
        for (int i = 0; i < n; i++)
        {
            det += pow(-1, i) * tab[0][i] * determinant(matrice_extraite(tab, n, i), n - 1);
        }
        return determinant;
    }
}

int Fibo1(int n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        return Fibo1(n-1) + Fibo1(n-2);
    }
}

int Fibo2(int n)
{
    if (n == 0 || n==1)
    {
        return n;
    }
    else
    {
        if (n % 2 == 0)
        {
            return pow(Fibo2(n / 2), 2) + 2 * Fibo2(n / 2) * Fibo2(n / 2 - 1);
        }
        else
        {
            return pow(Fibo2((n-1)/2), 2) + pow(Fibo2((n-1)/2 + 1), 2);
        }
    }
}
