//Exercice 4 - Question 7

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    //Demande
    int nb_valeurs = 0;
    printf("Nombre de valeurs : ");
    scanf("%d", &nb_valeurs);
    int tab[nb_valeurs];
    for (int i = 0; i < nb_valeurs; i ++)
    {
        scanf("%d", &tab[i]);
    }
    //Changement
    int temp = tab[0];
    for (int i = 0; i < nb_valeurs - 1; i++)
    {
        tab[i] = tab[i+1];
    }
    tab[nb_valeurs - 1] = temp;
    //Affichage
    for (int i = 0; i < nb_valeurs; i ++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    //Changement
    temp = tab[nb_valeurs - 1];
    for (int i = nb_valeurs - 1; i > 0; i--)
    {
        tab[i] = tab[i-1];
    }
    tab[0] = temp;
    //Affichage
    for (int i = 0; i < nb_valeurs; i ++)
    {
        printf("%d ", tab[i]);
    }
    return 0;
}
