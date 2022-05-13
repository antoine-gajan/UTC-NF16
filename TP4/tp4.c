#ifndef TP4_H
#define TP4_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tp4.h"
#define TAILLE_MAX 10000


t_ListePositions* creer_liste_positions()
{
    //Allocation dynamique
    t_ListePositions* liste = malloc(sizeof(t_ListePositions));
    //V�rification de l'espace m�moire
    if (liste != NULL)
    {
        liste->debut = NULL;
        liste->nb_elements = 0;
    }
    //Retourner la liste de positions vide
    return liste;
}

int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase)
{
    if (listeP == NULL || ligne <= 0 || ordre <= 0 || num_phrase <= 0)
    {
        return 0;
    }
    t_Position *pos = malloc(sizeof(t_position));
    if (pos == NULL)
    {
        return 0;
    }
    //Initialisation des attributs
    pos->numero_ligne = ligne;
    pos->numero_phrase = num_phrase;
    pos->ordre = ordre;
    pos->suivant = NULL;
    //Si la liste est vide, ajout en d�but de liste
    if (listeP->debut == NULL)
    {
        listeP->debut = pos;
    }
    //Si liste non vide, parcours pour savoir o� on ajoute
    else
    {
        t_position *prec = NULL;
        t_position *actuel = listeP->debut;
        //Ordre par num�ro de ligne
        while (actuel != NULL && pos->numero_ligne > actuel->numero_ligne)
        {
            prec = actuel;
            actuel = actuel->suivant;
        }
        //Ordre par ordre du mot dans la ligne
        while(actuel != NULL && pos->ordre > actuel->ordre)
        {
            prec = actuel;
            actuel = actuel->suivant;
        }
        //Si on doit l'ajouter en tant que premier �l�ment
        if (prec == NULL)
        {
            listeP->debut = pos;
        }
        //Ajout en milieu ou fin de liste
        else
        {
            prec->suivant = pos;
        }
        pos->suivant = actuel;
    }
    listeP->nb_elements ++;
    return 1;
}

t_Index* creer_index()
{
    //Allocation dynamique
    t_Index *arbre = malloc(sizeof(t_Index));
    if (arbre != NULL)
    {
        arbre->racine = NULL;
        arbre->nb_mots_total = 0;
        arbre->nb_mots_differents = 0;
    }
    return arbre;
}

t_Noeud* rechercher_mot(t_Index *index, char *mot)
{
    to_minuscule(mot);
    if(index == NULL)
    {
        return NULL;
    }
    t_Noeud *actuel = index->racine;
    while (actuel != NULL && strcmp(actuel->mot, mot) != 0)
    {
        if (strcmp(actuel->mot, mot) == 0)
        {
            return actuel;
        }
        if (strcmp(actuel->mot, mot) < 0)
        {
            actuel = actuel->filsGauche;
        }
        else
        {
            actuel = actuel->filsDroit;
        }
    }
    return NULL;
}

int ajouter_noeud(t_Index *index, t_Noeud *noeud)
{
    if (index == NULL || noeud == NULL)
    {
        return 0;
    }
    t_Noeud *pere = NULL;
    t_Noeud *actuel = index->racine;
    //Si l'arbre est vide
    if (actuel == NULL)
    {
        index->racine = noeud;
        return 1;
    }
    //Parcours de l'arbre pour trouver o� ajouter l'�l�ment
    while (actuel != NULL)
    {
        pere = actuel;
        if (strcmp(actuel->mot, noeud->mot) < 0)
        {
            actuel = actuel->filsDroit;
        }
        else
        {
            actuel = actuel->filsGauche;
        }
    }
    if (strcmp(pere->mot, noeud->mot) < 0)
    {
        actuel->filsDroit = noeud;
    }
    else
    {
        actuel->filsGauche = noeud;
    }
    //Mise � jour des attributs de l'index
    index->nb_mots_differents ++;
    index->nb_mots_total ++;
    return 1;
}

int indexer_fichier(t_Index *index, char *filename, t_Texte *texte)
{
    FILE *fichier = fopen(filename, "r");
    if (fichier == NULL)
    {
        return 0;
    }
    char ligne[TAILLE_MAX] = "";
    //D�finition des variables
    int num_ligne = 1;
    int ordre = 1;
    int num_phrase = 1;
    int nb_mots = 0;
    //Cr�ation de la premi�re phrase du texte
    t_Phrase *phrase = malloc(sizeof(t_Phrase));
    phrase->premier = NULL;
    phrase->num_phrase = num_phrase;
    phrase->suivant = NULL;
    ajouterPhraseDansListePhrase(texte, phrase);
    //Parcours du fichier ligne par ligne
    while(fgets(ligne, TAILLE_MAX, fichier))
    {
        char *mot = strtok(ligne, " ");
        while (mot != NULL)
        {
            nb_mots ++;
            //Initialisation d'un bool�en de changement de phrase � 0
            int changement_phrase = 0;
            //Conversion en minuscules
            to_minuscule(mot);
            //S'il y a un point dans le mot (fin de la phrase)
            if (strchr(mot, '.') != NULL)
            {
                //On enl�ve le point coll� au mot
                int size = strlen(mot);
                mot[size-1] = '\0';
                changement_phrase = 1;
            }
            //Si le mot n'est pas dans l'arbre
            t_noeud *noeud = rechercher_mot(index, mot);

            if ( noeud == NULL)
            {
                noeud = malloc(sizeof(t_noeud));
                //Si l'allocation dynamique a fonctionn�
                if (noeud != NULL)
                {
                    noeud->mot = mot;
                    noeud->nb_occurences = 1;
                    noeud->positions.debut = NULL;
                    noeud->positions.nb_elements = 0;
                    noeud->filsGauche = NULL;
                    noeud->filsDroit = NULL;
                    //Ajout du noeud � l'arbre
                    ajouter_noeud(index, noeud);
                    //Ajout de la position � la liste des positions
                    ajouter_position(&(noeud->positions), num_ligne, ordre, num_phrase);
                }
            }
            else
            {
                //Ajout de la position � la liste des positions
                ajouter_position(&(noeud->positions), num_ligne, ordre, num_phrase);
                noeud->nb_occurences ++;
                //Mise � jour des attributs de l'index
                index->nb_mots_total ++;
            }
            //Ajout du mot dans la phrase
            t_Mot *mot_phrase = malloc(sizeof(t_Mot));
            mot_phrase->mot = mot;
            mot_phrase->position = ordre;
            ajouterMotDansPhrase(phrase, mot_phrase);

            //Incr�mentation du num�ro de phrase si n�cessaire
            if (changement_phrase == 1)
            {
                num_phrase ++;
                ordre = 1;
                //Cr�ation de la nouvelle phrase
                phrase = malloc(sizeof(t_Phrase));
                phrase->num_phrase = num_phrase;
                phrase->premier = NULL;
                phrase->suivant = NULL;
                //Si changement de phrase, on ajoute une phrase au texte
                ajouterPhraseDansListePhrase(texte, phrase);
            }
            else
            {
                ordre ++;
            }
            mot = strtok(NULL, " ");
        }
        num_ligne ++;
    }
    fclose(fichier);
    return nb_mots;
}


//Fonction qui affiche l'arbre
void afficher_index(t_Index *index)
{
    if (index == NULL)
    {
        printf("L'arbre est vide.");
        return;
    }
    else
    {
        printf("D�but affiche");
        parcours_infixe_affichage(index->racine, NULL);
    }
}

void afficheNoeud(t_Noeud *noeud)
{
    // Affichage de l'�l�ment
    printf("|-- %s\n", noeud->mot);
    //Affichage de ses occurences
    for (int i = 1; i < noeud->nb_occurences; i++)
    {
        printf("|---- (l: %d, o : %d, p : %d)\n");
    }
    printf("|\n");
}

//Fonction qui parcourt l'arbre
void parcours_infixe_affichage(t_Noeud *noeud, char *dernier_car)
{
    // Si plus de noeud � afficher, on affiche rien
    if (noeud == NULL)
    {
        return ;
    }
    // Parcours du sous arbre gauche
    parcours_infixe_affichage(noeud->filsGauche, dernier_car);
    //Affichage de l'alphabet si la lettre du mot pr�c�dent est diff�rente de celle du mot actuel
    if (strupr(noeud->mot[0]) != *dernier_car)
    {
        //Affichage de la lettre en majuscule
        printf("%c\n", strupr(noeud->mot[0]));
        //Modification de la variable globale derni�re lettre
        *dernier_car = strupr(noeud->mot[0]);
    }
    afficheNoeud(noeud);
    // Parcours du sous arbre droit
    parcours_infixe_affichage(noeud->filsDroit, dernier_car);
}

void afficher_max_apparition(t_Index *index)
{
    //Si l'arbre est vide
    if (index == NULL)
    {
        printf("L'arbre est vide.\n");
    }
    //Recherche du noeud dont le mot apparait le plus souvent
    t_Noeud *noeud_max = max_occurences(index->racine);
    if (noeud_max != NULL)
    {
        //Affichage de ses caract�ristiques
        printf("Mot apparaissant le plus dans le texte : %s\n", noeud_max->mot);
        printf("Nombre d'occurences : %d\n", noeud_max->nb_occurences);
    }
}

//Fonction r�cursive qui renvoie le noeud ayant le maximum d'occurences sur un arbre
t_Noeud* max_occurences(t_Noeud *noeud)
{
    //Si le noeud est vide, pas de noeud ayant un mot avec le maximum d'occurences
    if (noeud == NULL)
    {
        return NULL;
    }
    //Recherche du maximum des sous arbres gauche et droite
    t_Noeud *max_gauche = max_occurences(noeud->filsGauche);
    t_Noeud *max_droit = max_occurences(noeud->filsDroit);

    //Distinction des cas
    //Si max_gauche et max_droit sont non NULL, on recherche le max entre le noeud actuel, max_gauche et max_droit
    if (max_gauche != NULL && max_droit != NULL)
    {
        if (noeud->nb_occurences > max_gauche->nb_occurences && noeud->nb_occurences > max_droit->nb_occurences)
        {
            return noeud;
        }
        else if (max_gauche->nb_occurences > noeud->nb_occurences && max_gauche->nb_occurences > max_droit->nb_occurences)
        {
            return max_gauche;
        }
        else
        {
            return max_droit;
        }
    }
    //Si max_gauche est NULL, on recherche le max entre le noeud actuel et max_droit
    else if (max_gauche == NULL)
    {
        if (max_droit->nb_occurences > noeud->nb_occurences)
        {
            return max_droit;
        }
        else
        {
            return noeud;
        }
    }
    //Si max_droit est NULL, on recherche le max entre le noeud actuel et max_gauche
    else if (max_droit == NULL)
    {
        if (max_gauche->nb_occurences > noeud->nb_occurences)
        {
            return max_gauche;
        }
        else
        {
            return noeud;
        }
    }
    //Sinon, on retourne le noeud p�re, seul noeud de l'arbre car on a atteint une feuille
    else
    {
        return noeud;
    }
}

void afficher_occurences_mot(t_Index *index, char *mot)
{
    t_Noeud *noeudAafficher = rechercher_mot(index, mot);
    printf("Mot = \"%s\"\n", noeudAafficher->mot);
    printf("Occurences = %d\n", noeudAafficher->nb_occurences);

}

void ajouterMotDansPhrase(t_Phrase *phrase, t_Mot *mot)
{
    if (phrase == NULL || mot == NULL)
    {
        return ;
    }
    t_Mot *actuel = phrase->premier;
    t_Mot *prec = NULL;
    while(actuel != NULL && actuel->position < mot->position)
    {
        prec = actuel;
        actuel = actuel->suivant;
    }
    if (prec == NULL)
    {
        phrase->premier = mot;
    }
    mot->suivant = actuel;
    prec->suivant = mot;
}

void ajouterPhraseDansListePhrase(t_Texte *texte, t_Phrase *phrase)
{
    if (phrase == NULL || phrase == NULL)
    {
        return ;
    }
    t_Phrase *actuel = texte->premier;
    t_Phrase *prec = NULL;
    while(actuel != NULL && actuel->num_phrase < phrase->num_phrase)
    {
        prec = actuel;
        actuel = actuel->suivant;
    }
    if (prec == NULL)
    {
        texte->premier = phrase;
    }
    phrase->suivant = actuel;
    prec->suivant = phrase;
}

t_Texte* creer_texte()
{
    t_Texte *texte = malloc(sizeof(t_Texte));
    if (texte != NULL)
    {
        texte->premier = NULL;
    }
    return texte;
}


void to_minuscule(char *chaine)
{
    for (int i = 0; i < strlen(chaine); i++)
    {
        chaine[i] = tolower((unsigned int)chaine[i]);
    }
}
#endif // TP4_H
