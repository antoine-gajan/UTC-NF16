//Exercice 3 - Question 3 - Initialiser une matrice

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //Cr�ation  du tableau
    int tableau[3][4];
    int valeur = 12;

    //Boucle d'initialisation du tableau � 2 dimensions
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
            tableau[i][j] = valeur;
            valeur ++;
        }
    }

    //Affichage du tableau
    printf("La matrice est : \n");
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
           printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }

    return 0;
}
