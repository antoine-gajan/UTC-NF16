#include <stdio.h>
#include <unistd.h>
#include "tp3.h"

int main()
{
    int reponse = -1;
    T_Electeur liste = NULL;
    // Menu principal
    while(reponse != 9){
        printf("\nELECTION PRESIDENTIELLE 2022\n");
        printf("\n===MENU===\n");
        printf("1. Ajouter des electeurs\n");
        printf("2. Supprimer un electeur\n");
        printf("3. Rechercher un electeur\n");
        printf("4. Afficher la liste des electeurs\n");
        printf("5. Calculer le nombre d'electeurs\n");
        printf("6. Decouper la liste en trois sous-listes selon les choix: droite, gauche et blanc\n");
        printf("\ta. Trier les sous-listes\n");
        printf("\tb. Afficher les sous-listes\n");
        printf("\tc. Fusionner les deux sous-listes : gauche et droite\n");
        printf("7. Calculer les pourcentages de gauche et de droite pour le 2eme tour\n");
        printf("8. Liberer les listes\n");
        printf("9. Quitter\n");

        // Demande du choix
        do{
        printf("\nVotre choix : ");
        scanf("%d", &reponse);
        } while(reponse < 1 || reponse > 9);

        // Cas différent en fonction de la réponse
        switch(reponse)
        {
            case 1:
                printf("\n=== Ajout d'un electeur ===\n");
                char nom[100];
                long cin_num = 0;
                int choix = 0;
                printf("\nNom (de moins de 100 caracteres) : ");
                // Vider le buffer avant par sécurité
                while(getchar() != '\n');
                scanf("%[^\n]s", nom);
                // Vider le buffer après saisie par sécurité
                while(getchar() != '\n');
                printf("\nNumero de carte d'identite : ");
                scanf("%ld", &cin_num);
                printf("\nChoix : ");
                scanf("%d", &choix);
                ajoutelecteur(&liste, nom, cin_num, choix);
                sleep(1);
                break;
            case 2:
                printf("\n=== Suppression d'un electeur ===\n");
                long cin;
                printf("\nNumero de carte d'identite a supprimer : ");
                scanf("%ld", &cin);
                Supprimelecteur(&liste, cin);
                sleep(1);
                break;
            case 3:
                printf("\n=== Rechercher un electeur ===\n");
                long cin_num_recherche = 0;
                printf("\nNumero de carte d'identite : ");
                scanf("%ld", &cin_num_recherche);
                trouvelecteur(liste, cin_num_recherche);
                sleep(5);
                break;
            case 4:
                printf("\n=== Afficher les electeurs ===\n");
                afficheliste(liste);
                sleep(5);
                break;
            case 5:
                printf("\n=== Compter le nombre d'electeurs ===\n");
                int nb_electeurs = comptelecteur(liste);
                printf("\nDans la liste, il y %d electeurs.", nb_electeurs);
                sleep(5);
                break;
            case 6:
                printf("\n=== Decouper la liste en trois sous-listes ===\n");
                T_Electeur gauche = NULL;
                T_Electeur droite = NULL;
                T_Electeur blanc = NULL;
                decoupeliste(liste, &gauche, &droite, &blanc);
                //Tri des listes
                triliste(&gauche);
                triliste(&droite);
                triliste(&blanc);
                // Affichage des 3 sous listes
                printf("\nListe gauche : ");
                afficheliste(gauche);
                printf("\nListe droite : ");
                afficheliste(droite);
                printf("\nListe blanc : ");
                afficheliste(blanc);
                printf("\nListe fusionnee : ");
                // Fusion des listes gauche et droite
                T_Electeur fusion = fusionlistes(gauche, droite);
                gauche = NULL;
                droite = NULL;
                // Affichage
                afficheliste(fusion);
                sleep(5);
                break;
            case 7:
                printf("\n=== Calculer les pourcentages de gauche et de droite pour le 2eme tour === \n");
                int nbgauche = compteGD(fusion);
                int nbelecteurs_sans_blanc = comptelecteur(fusion);
                // Affichage des pourcentages
                printf("\n\nPourcentage de voteurs a gauche : %.2f %", (float)nbgauche/ nbelecteurs_sans_blanc);
                printf("\nPourcentage de voteurs a droite  : %.2f %", (float)(nbelecteurs_sans_blanc - nbgauche)/ nbelecteurs_sans_blanc);
                sleep(5);
                break;
            case 8:
                printf("\n=== Liberer les listes ===\n");
                // Libérer les listes
                libereliste(liste);
                libereliste(blanc);
                libereliste(fusion);
                liste = NULL;
                blanc = NULL;
                fusion = NULL;
                printf("\nListes liberees avec succes !\n");
                sleep(5);
                break;
            case 9:
                printf("\nVous allez quitter le programme.\n");
                sleep(2);
                break;
        }
    }
}

/*
Jeu de données test
ajoutelecteur(&liste, "Chloe", 345432, 1);
ajoutelecteur(&liste, "Paul", 65438921, 2);
ajoutelecteur(&liste, "Louis", 4356791, 3);
ajoutelecteur(&liste, "Louise", 4556762, 4);
ajoutelecteur(&liste, "Jean", 123456, 1);
ajoutelecteur(&liste, "Theo", 123,5);
ajoutelecteur(&liste, "Emma", 54763, 7);
*/
