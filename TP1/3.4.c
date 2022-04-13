//Exercice 3 - Question 4 - Produit de matrices

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    //Création  de 2 matrices
    int a[5][3] = {1, 4, 3, 1 ,-1, 2, -3, 1, 5, 7, 2, -3, 0, 0, 2};
    int b[3][2] = {2, 3, 5, -1 ,0, 2};
    int c[5][2];

    //Calcul des composantes de la matrice issue du proudit
    for (int i = 0; i < 5; i ++)
    {
        for (int j = 0; j < 2; j ++)
        {
            //Calcul de la valeur issue du produit
            int valeur = 0;
            for (int k = 0; k < 3; k ++)
            {
                valeur += a[i][k] * b[k][j];
            }

            c[i][j] = valeur;

        }
    }
    //Affichage du résultat
    for (int i = 0; i < 5; i ++)
    {
        for (int j = 0; j < 2; j ++)
        {
           printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
