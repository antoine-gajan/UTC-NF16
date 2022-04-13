//Exercice 5 - Question 1 - Programme qui détermine le nombre et la position d'une sous-chaîne dans une chaîne

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    //Initialisation
    char chaine[10];
    printf("Entrez une chaine de moins de 10 caracteres : ");
    scanf("%s", chaine);
    char souschaine[10];
    printf("Entrez une sous-chaine de moins de 10 caracteres : ");
    scanf("%s", souschaine);
    int nb_car_chaine = 0;
    int nb_car_souschaine = 0;
    //nombre de caracteres dans la sous chaine
    while(nb_car_chaine < 10 && chaine[nb_car_chaine] != '\0')
    {
        nb_car_chaine ++;
    }
    //printf("Nb : %d\n", nb_car_chaine);
    //nombre de caracteres dans la sous chaine
    while(nb_car_souschaine < 10 && souschaine[nb_car_souschaine] != '\0')
    {
        nb_car_souschaine ++;
    }
    //printf("Nb : %d\n", nb_car_souschaine);
    //Presence ou non ?
    int nb_fois = 0;
    for (int i = 0; i < nb_car_chaine - nb_car_souschaine; i++)
    {
        int presence = 1;
        for (int j = 0; j < nb_car_souschaine; j++)
        {
            if (chaine[i + j] != souschaine[j])
            {
                presence = 0;
            }
        }
        if (presence)
        {
            nb_fois ++;
        }
    }
    printf("La sous-chaine %s est présente %d fois dans la chaine %s", souschaine, nb_fois, chaine);


    return 0;


}
