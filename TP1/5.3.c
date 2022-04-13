//Exercice 5 - Question 3 - Jeu du pendu

#include <stdlib.h>
#include <stdio.h>

int NbLettresDansMot(char mot[])
{
    int nb_lettres = 0;
    while (mot[nb_lettres] != '\0')
    {
        nb_lettres ++;
    }
    return nb_lettres;
}

void InitialiserTableau(int tab[], int longueurMot)
{
    for (int i = 0; i < longueurMot; i++){
        tab[i] = 0;
    }
}

void MiseAJourTab(int tab[], char motADeviner[], char LettreProposee)
{
    int nblettres = NbLettresDansMot(motADeviner);
    for (int nb = 0; nb < nblettres; nb ++)
    {
        if (motADeviner[nb] == LettreProposee)
        {
            tab[nb] = 1;
        }
    }
}

int AfficherMot(int tab[], char motADeviner[])
{
    int nblettres = NbLettresDansMot(motADeviner);
    int trouve = 1;
    for (int nb = 0; nb < nblettres; nb ++)
    {
        if (tab[nb] == 1)
        {
            printf("%c", motADeviner[nb]);
        }
        else{
            trouve = 0;
            printf("*");
        }
    }
    printf("\n");
    return trouve;
}

int main(int argc, char *argv[])
{
    //initialisation du jeu
    int nb_coups_restants = 10;
    char motAdeviner[26];
    printf("==== JEU DU PENDU ====\n\n\n");
    printf("Joueur 1 : Entrez le mot à faire deviner : ");
    scanf("%s", motAdeviner);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    int longueurMot = NbLettresDansMot(motAdeviner);
    int *tableau = malloc(sizeof(int) * longueurMot);
    InitialiserTableau(tableau, longueurMot);
    int trouve = 0;

    //Jeu
    printf("Joueur 2 : Deviner le mot \n\n");
    while(nb_coups_restants > 0 && trouve != 1)
    {
        printf("caractere ? (nb coups restants : %d) ", nb_coups_restants);
        //Vider buffer
        char c = 0;
        while(c != '\n' && c != EOF){
            c = getchar();
        }
        char caracterePropose = getchar();
        MiseAJourTab(tableau, motAdeviner, caracterePropose);
        trouve = AfficherMot(tableau, motAdeviner);
        nb_coups_restants --;
    }

    //A Gagne ?
    if (trouve)
    {
        printf("Vous avez trouvé le bon mot en %d coups !", 10 - nb_coups_restants);
    }
    else{
        printf("Dommage ! Le mot à trouver était : %s", motAdeviner);
    }
    return 0;
}
