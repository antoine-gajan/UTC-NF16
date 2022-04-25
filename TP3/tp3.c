#include <stdlib.h>
#include <string.h>
#include "tp3.h"


// Création d'un électeur
T_Electeur creationelecteur(void){
    T_Electeur nouv = malloc(sizeof(electeur));
    if (nouv != NULL)
    {
        nouv->suivant = NULL;
    }
    return nouv;
}

// Afficher l'ensemble des électeurs
void afficheliste(T_Electeur liste)
{
    if (liste == NULL)
    {
        printf("\nLa liste d'electeurs est vide.\n");
    }
    else
    {
        printf("\n-------Liste des electeurs-------\n");
        while(liste != NULL)
        {
            printf("\nNom : %s \nNumero d'identite : %ld \nChoix : %d\n", liste->nom, liste->cin_num, liste->choix);
            liste = liste->suivant;
        }
    }
}

// Ajoute un nouveau électeur à la liste, ce nouvel électeur aura un nom, un numéro identifiant et son choix de vote
void ajoutelecteur(T_Electeur *liste, char nom[], long cin_num, int choix)
{
    //Création d'un nouveau electeur
    T_Electeur nouv = creationelecteur();
    if (nouv != NULL)
    {
        //Ajout des attributs cin_num et choix
        nouv->cin_num = cin_num;
        nouv->choix = choix;

        // Ajout de son nom
        nouv->nom = malloc(sizeof(char) * strlen(nom));
        strcpy(nouv->nom, nom);

        // Ajout au bon endroit selon l'ordre lexicographique
        T_Electeur actuel = *liste;
        if (actuel == NULL)
        {
            // Liste vide : ajout au début de liste
            *liste = nouv;
        }
        else
        {
            // Ajout au bon endroit
            T_Electeur prec = NULL;
            while (actuel != NULL && strcmp(nouv->nom, actuel->nom) > 0)
            {
                prec = actuel;
                actuel = actuel->suivant;
            }
            if (prec == NULL)
            {
                // Ajout en début de liste et liste non vide
                nouv->suivant = *liste;
                *liste = nouv;
            }
            else if (actuel == NULL)
            {
                // Ajout en fin de liste
                prec->suivant = nouv;
            }
            else
            {
                // Insertion en "milieu de liste"
                nouv->suivant = prec->suivant;
                prec->suivant = nouv;
            }
        }

        // Affichage d'un récapitulatif de l'ajout du lecteur
        printf("\nElecteur cree avec succes ! \nRecpitulatif : ");
        printf("\nNom : %s", nouv->nom);
        printf("\nNumero d'identite : %ld", nouv->cin_num);
        printf("\nChoix : %d\n", nouv->choix);
    }
}

// Fonction qui compte le nombre d'électeurs dans la liste
int comptelecteur(T_Electeur liste)
{
    // Variable pour le nombre d'électeurs
    int n = 0;
    while (liste != NULL)
    {
        // Incrémentation du nombre d'électeurs
        n ++;
        liste = liste->suivant;
    }
    return n;
}

// Fonction qui affiche les informations d'un électeur s'il est dans la liste (la fonction renvoie 0)
// Si l'électeur n'est pas dans la liste, renvoie 1
int trouvelecteur(T_Electeur liste, long cin_num)
{
    // Tant qu'on n'a pas trouvé l'électeur
    while (liste != NULL && liste->cin_num != cin_num)
    {
        // On passe à l'électeur suivant
        liste = liste->suivant;
    }
    if (liste == NULL)
    {
        // L'électeur n'est pas dans la liste
        printf("\nL'electeur n'est pas dans la liste.\n");
        return 1;
    }
    else
    {
        // Affichage d'un récapitulatif de l'électeur
        printf("\nInformations de l'electeur :");
        printf("\nNom : %s", liste->nom);
        printf("\nNumero identifiant : %ld", liste->cin_num);
        printf("\nChoix : %d\n", liste->choix);
        return 0;
    }
}

//Fonction qui supprime un électeur dont le numéro d'identité est cin_num
void Supprimelecteur(T_Electeur *liste,long cin_num)
{
    T_Electeur actuel = *liste;
    T_Electeur prec = NULL;
    // Tant qu'on n'a pas trouvé l'électeur
    while (actuel != NULL && actuel->cin_num != cin_num)
    {
        prec = actuel;
        actuel = actuel->suivant;
    }

    if (actuel == NULL)
    {
        // L'électeur n'est pas dans la liste
        printf("\nL'electeur donne n'appartient pas à la liste.\n");
    }
    else if (prec == NULL)
    {
        // Suppression de l'électeur en tête de liste
        *liste = actuel->suivant;
        // Libération de la mémoire
        free(actuel);
        printf("\nL'electeur a ete supprime avec succes !\n");
    }
    else
    {
        // Suppression de l'électeur
        prec->suivant = actuel->suivant;
        // Libération de la mémoire
        free(actuel);
        printf("\nL'electeur a ete supprime avec succes !\n");
    }
}

void decoupeliste(T_Electeur liste_initiale,T_Electeur *gauche,T_Electeur *droite,T_Electeur *blanc)
{
    T_Electeur actuel = liste_initiale;
    // Tant que l'on n'a pas atteint la fin de la liste
    while(actuel != NULL)
    {
        // Ajout aux nouvelles listes en fonction de leur choix de vote
        if (actuel->choix == 1 || actuel->choix == 3)
        {
            ajoutelecteur(gauche, actuel->nom, actuel->cin_num, actuel->choix);
        }
        else if (actuel->choix == 2 || actuel->choix == 4)
        {
            ajoutelecteur(droite, actuel->nom, actuel->cin_num, actuel->choix);
        }
        else
        {
            ajoutelecteur(blanc, actuel->nom, actuel->cin_num, actuel->choix);
        }
        actuel = actuel->suivant;
    }
}

// Fonction qui trie une liste (tri à bulles)
void triliste(T_Electeur *liste)
{
    // Initialisation de pointeurs sur structure électeur
    T_Electeur precedent;
    T_Electeur actuel;
    T_Electeur suivant;
    int modif = 1;
    // Tant que des modifs ont été faites à l'itération précédente, on continue
    while (modif == 1)
    {
        modif = 0;
        precedent = NULL;
        actuel = *liste;
        // Si actuel est NULL, la liste est vide, pas besoin de trier
        if (actuel == NULL)
        {
            return;
        }
        // Tant qu'on n'est pas en fin de liste
        while (actuel->suivant != NULL)
        {
            // S'il faut échanger 2 électeurs
            if (actuel->cin_num > actuel->suivant->cin_num)
            {
                modif = 1;
                // Si c'est en début de liste
                if (precedent == NULL)
                {
                    suivant = actuel->suivant;
                    actuel->suivant = actuel->suivant->suivant;
                    suivant->suivant = actuel;
                    precedent = suivant;
                    *liste = precedent;
                }
                else
                {
                    // Echange des 2 électeurs (hors début de liste)
                    suivant = actuel->suivant;
                    actuel->suivant = actuel->suivant->suivant;
                    precedent->suivant = suivant;
                    suivant->suivant = actuel;

                    // Mise à jour du précédent
                    precedent = suivant;
                }
            }
            else
            {
                // On se décale de un dans la liste
                precedent = actuel;
                actuel = actuel->suivant;
            }
        }
    }
}

// Fonction qui fusionne 2 listes d'électeurs
T_Electeur fusionlistes(T_Electeur gauche, T_Electeur droite)
{
    // Si une des deux listes est vide
    if (gauche == NULL)
    {
        return droite;
    }
    if (droite == NULL)
    {
        return gauche;
    }
    // Tant que l'on n'est pas à la fin de la liste gauche
    T_Electeur actuel = gauche;
    while (actuel->suivant != NULL)
    {
        actuel = actuel->suivant;
    }
    // Fusion des deux listes
    actuel->suivant = droite;
    // Tri de la liste
    triliste(&gauche);
    return gauche;
}

// Fonction qui renvoie le nombre d'électeurs de gauche
int compteGD(T_Electeur liste)
{
    T_Electeur actuel = liste;
    int nombre_gauche = 0;
    // Parcours des électeurs de la liste
    while(actuel != NULL)
    {
        // Si l'électeur vote à gauche
        if (actuel->choix == 1 || actuel->choix == 3)
        {
            nombre_gauche ++;
        }
        actuel = actuel->suivant;
    }
    return nombre_gauche;
}

// Fonction qui libère une liste d'électeurs
void libereliste(T_Electeur liste)
{
    T_Electeur actuel = liste;
    T_Electeur copie;
    // On vide les électeurs un par un
    while (actuel != NULL)
    {
        // Libération de l'espace alloué
        copie = actuel;
        actuel = actuel->suivant;
        free(copie);
        // Remise du pointeur à NULL (0)
        copie = NULL;
    }
}

