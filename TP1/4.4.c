//Exercice 4 - Question 4 - Pointeurs

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //Déclaration des variables
    int i;
    int *j;
    //On affecte à i la valeur 5
    i = 5;
    //Affectation à j de l'adresse de i
    j = &i;
    //Affichage
    printf("i = %d et le contenu de j est %d\n", i, *j);
    //Incrémenter la valeur contenu pointé par j
    *j = *j + 1;
    printf("i = %d\n", i);
    //Multplication de i par 5
    i *= 5;
    //Affichage du contenu point par j
    printf("Contenu pointe par j = %d\n", *j);
    //Incrémenter l'adresse de j
    j++;
    //Affichage
    printf("Contenu pointe par j = %d\n", *j);
    return 0;
}

