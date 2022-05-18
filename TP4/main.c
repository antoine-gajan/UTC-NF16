#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main()
{
    //Création de l'index et du texte à restituer
    t_Index *index = creer_index();
    int reponse = -1;
    // Menu principal
    while(reponse != 8){
        printf("\n*** INDEXATION ET RECHERCHE DANS UN FICHIER ***\n");
        printf("1. Charger un fichier\n");
        printf("2. Caractéristiques de l'index\n");
        printf("3. Afficher l'index\n");
        printf("4. Rechercher un mot\n");
        printf("5. Afficher le mot avec le maximum d'apparition\n");
        printf("6. Afficher les occurences d'un mot\n");
        printf("7. Construire le texte a partir de l'index\n");
        printf("8. Quitter\n");

        // Demande du choix
        do{
        printf("\nVotre choix : ");
        scanf("%d", &reponse);
        } while(reponse < 1 || reponse > 8);

        // Cas différent en fonction de la réponse
        switch(reponse)
        {
            case 1:
                printf("\n=== Charger un fichier ===\n");
                char filename[100];
                //Vider le buffer par sécurité
                vider_buffer();
                printf("\nNom du fichier a charger : ");
                scanf("%s", filename);
                printf("\n");
                if (indexer_fichier(index, filename) != 0)
                {
                    printf("\nFichier charge avec succes\n");
                }
                sleep(1);
                break;
            case 2:
                printf("\n=== Caracteristiques de l'index ===\n");
                printf("Nombre de mots différents : %d\n", index->nb_mots_differents);
                printf("Nombre de mots (total) : %d\n", index->nb_mots_total);
                printf("Hauteur de l'arbre : %d\n", hauteur(index->racine));
                if (equilibre(index->racine))
                {
                    printf("L'arbre est equilibre.\n");
                }
                else
                {
                    printf("L'arbre n'est pas equilibre.\n");
                }
                sleep(1);
                break;
            case 3:
                printf("\n=== Afficher l'index ===\n");
                afficher_index(index);
                sleep(5);
                break;
            case 4:
                printf("\n=== Rechercher un mot ===\n");
                char mot[100];
                printf("\nEntrez le mot à rechercher : ");
                scanf("%s", mot);
                t_Noeud *noeud = rechercher_mot(index, mot);
                if(noeud != NULL)
                {
                    printf("\nLe mot '%s' est present %d fois dans l'arbre.\nListe de ses occurences :\n", mot, noeud->nb_occurences);
                    t_Position *position = noeud->positions->debut;
                    while (position != NULL)
                    {
                        printf("  - Ligne %d, ordre %d, phrase %d\n", position->numero_ligne, position->ordre, position->numero_phrase);
                        position = position->suivant;
                    }
                }
                else
                {
                    printf("\nLe mot '%s' n'est pas present dans l'index.\n", mot);
                }
                sleep(5);
                break;
            case 5:
                printf("\n=== Afficher le mot avec le maximum d'apparition ===\n");
                afficher_max_apparition(index);
                sleep(5);
                break;
            case 6:
                printf("\n=== Afficher les occurences d'un mot === \n");
                char mot_occurences[100];
                printf("Mot a rechercher : ");
                scanf("%s", mot_occurences);
                afficher_occurences_mot(index, mot_occurences);
                sleep(5);
                break;
            case 7:
                printf("\n=== Construire le texte a partir de l'index ===\n");
                printf("Nom du fichier dans lequel vous souhaitez ecrire : ");
                vider_buffer();
                scanf("%s", filename);
                construire_texte(index, filename);
                sleep(5);
                break;
            case 8:
                libererIndex(index);
                printf("\nMemoire liberee.\nVous allez quitter le programme.\n");
                sleep(2);
                break;
        }
    }
    return 0;
}
