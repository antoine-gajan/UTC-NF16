//Exercice 4 - Question 3 - Pointeurs

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //D�claration des variables
    int i;
    int *j;
    //On affecte � i la valeur 5
    i = 5;
    //Affectation � j de l'adresse de i
    j = &i;
    //Affichage
    printf("i = %d et le contenu de j est %d", i, *j);

    return 0;
}

