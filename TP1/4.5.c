//Exercice 4 - Question 5 - Pointeurs


#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //Création  du tableau
    int tableau[3][4];
    int valeur = 12;

    //Boucle d'initialisation du tableau à 2 dimensions
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
        int *ligne = tableau[i];
        for (int j = 0; j < 4; j ++)
        {
           printf("%d ", ligne[j]);
        }
        printf("\n");
    }

}
