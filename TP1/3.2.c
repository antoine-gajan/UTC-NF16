//Exercice 3 - Question 2 - Initialiser un tableau

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //Création  du tableau
    int tableau[5];
    int i = 0;

    //Boucle d'initialisation
    for (i = 0; i < 5; i ++)
    {
        tableau[i] = 4 - i;
    }

    return 0;
}
