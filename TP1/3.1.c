//Exercice 3 - Question 1 - Initialiser un tableau

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //Cr�ation  du tableau et de la variable de contr�le
    int tableau[10];
    int controle = 0;

    //Boucle d'initialisation
    for (controle = 0; controle < 10; controle ++)
    {
        tableau[controle] = 0;
    }

    return 0;
}


