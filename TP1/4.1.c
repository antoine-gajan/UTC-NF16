//Exercice 4 - Question 1 - Fonction de permutation

#include <stdlib.h>
#include <stdio.h>

void permutation(float *nb1, float *nb2)
{
    float temp = *nb1;
    *nb1 = *nb2;
    *nb2 = temp;
}

int main(int argc, char *argv[])
{
    //Déclaration de 2 valeurs
    float nb1 = 12;
    float nb2 = 23;
    printf("nb1 = %f et nb2 = %f \n", nb1, nb2);
    //Permutation
    permutation(&nb1, &nb2);
    //Affichage
    printf("Apres permutation, nb1 = %f et nb2 = %f", nb1, nb2);
    return 0;


}
