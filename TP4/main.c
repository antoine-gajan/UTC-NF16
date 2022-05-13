#include <stdio.h>
#include <stdlib.h>
#include "tp4.h";

int main()
{
    /*t_ListePositions* liste = creer_liste_positions();
    ajouter_position(liste, 2, 44, 2, 1);
    ajouter_position(liste, 1,1,3,1);
    ajouter_position(liste, 2,10,4,1);
    printf("Nb element : %d\n", liste->nb_elements);
    t_Position *a = liste->debut;
    while (a != NULL)
    {
        printf("Ligne : %d, oRDRE : %d\n", a->numero_ligne, a->ordre);
        a = a->suivant;
    }*/
    //t_Index *i = creer_index();
    //t_Noeud *n;
    char *mot = "Bonjour";
    printf("%s, %d\n", mot, strlen(mot));
    to_minuscule(mot);
    printf("%s", mot);
   /* n->filsDroit = NULL;
    n->filsGauche = NULL;
    n->nb_occurences = 0;
    n->positions.debut = NULL;
    n->positions.nb_elements = 0;
    ajouter_noeud(i, n);
    printf("%d, %s\n", i->racine, i->racine->mot);
    //afficher_index(i);
    //printf("%d", rechercher_mot(i, "Bonjour"));
    //afficher_index(i);*/
    return 0;
}
