#ifndef TP4_H
#define TP4_H

#include <string.h>
#include "tp4.h"

#define TAILLE_MAX 100000


t_ListePositions* creer_liste_positions()
{
    //Allocation dynamique
    t_ListePositions* liste = malloc(sizeof(t_ListePositions));
    //Vérification de l'espace mémoire
    if (liste != NULL)
    {
        liste->debut = NULL;
        liste->nb_elements = 0;
    }
    //Retourner la liste de positions vide
    return liste;
}

int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase, int estMajuscule)
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
    pos->numero_ligne = ligne;
    pos->numero_phrase = num_phrase;
    pos->ordre = ordre;
    pos->EstMajuscule = estMajuscule;
    //Si la liste est vide, ajout en début de liste
    if (listeP->debut == NULL)
    {
        listeP->debut = pos;
    }
    //Si liste non vide, parcours pour savoir où on ajoute
    else
    {
        t_position *prec = NULL;
        t_position *actuel = listeP->debut;
        //Ordre par numéro de ligne
        while (actuel != NULL && pos->numero_ligne < actuel->numero_ligne)
        {
            prec = actuel;
            actuel = actuel->suivant;
        }
        //Ordre par ordre du mot dans la ligne
        while(actuel != NULL && pos->ordre < actuel->ordre)
        {
            prec = actuel;
            actuel = actuel->suivant
        }
        //Si on doit l'ajouter en tant que premier élément
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
    mot = strlwr(mot);
    if(index == NULL)
    {
        return NULL;
    }
    t_Noeud *actuel = index->racine;
    while (actuel != NULL && strcmp(actuel->mot, mot) != 0)
    {
        if (strcmp(actuel->mot, mot) < 0)
        {
            actuel = actuel->filsGauche;
        }
        else
        {
            actuel = actuel->filsDroit;
        }
    }
    return actuel;
}

int ajouter_noeud(t_Index *index, t_Noeud *noeud)
{
    if (index == NULL || noeud == NULL)
    {
        return 0;
    }
    t_Noeud *pere = NULL;
    t_Noeud *actuel = index->racine;
    while (actuel != NULL)
    {
        pere = actuel;
        if (strcmp(actuel->mot, noeud->mot) < 0)
        {
            actuel = actuel->filsGauche;
        }
        else
        {
            actuel = actuel->filsDroit;
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
    return 1;
}

int indexer_fichier(t_Index *index, char *filename)
{
    FILE *fichier = fopen(filename, "r");
    if (fichier == NULL)
    {
        return 0;
    }
    char ligne[TAILLE_MAX] = "";
    //Définition des variables
    int num_ligne = 1;
    int ordre = 1;
    int num_phrase = 1;
    int nb_mots = 0;
    //Parcours du fichier ligne par ligne
    while(fgets(ligne, TAILLE_MAX, fichier))
    {
        char *mot = strtok(ligne, " ");
        while (mot != NULL)
        {
            nb_mots ++;
            //Initialisation d'un booléen de changement de phrase à 0
            int changement_phrase = 0;
            //Conversion en minuscules
            char *mot_nouveau = strlwr(mot);
            //Occurence du mot est en majuscule ?
            int estMajuscule = (mot_nouveau != mot);
            //S'il y a un point dans le mot (fin de la phrase)
            if (strchr(mot_nouveau, '.') != NULL)
            {
                //On enlève le point collé au mot
                int size = strlen(mot_nouveau);
                mot_nouveau[size-1] = '\0';
                changement_phrase = 1;
            }
            //Si le mot n'est pas dans l'arbre
            t_noeud *noeud = rechercher_mot(index, mot_nouveau);

            if ( noeud == NULL)
            {
                noeud = malloc(sizeof(t_noeud));
                //Si l'allocation dynamique a fonctionné
                if (noeud != NULL)
                {
                    noeud->mot = mot_nouveau;
                    noeud->nb_occurences = 1;
                    noeud->positions->debut = NULL;
                    noeud->positions->nb_elements = 0;
                    //Ajout du noeud à l'arbre
                    ajouter_noeud(index, noeud);
                    //Ajout de la position à la liste des positions
                    ajouter_position(&(noeud->positions), num_ligne, ordre, num_phrase, estMajuscule);
                    index->nb_mots_differents ++;
                }
            }
            else
            {
                //Ajout de la position à la liste des positions
                ajouter_position(&(noeud->positions), num_ligne, ordre, num_phrase, estMajuscule);
                noeud->nb_occurences ++;
            }
            index->nb_mots_total ++;

            //Incrémentation du numéro de phrase si nécessaire
            if (changement_phrase == 1)
            {
                num_phrase ++;
                ordre = 1;
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
        parcoursInfixeAffichage(index->racine, NULL);
    }
}

void afficheNoeud(t_Noeud *noeud)
{
    // Affichage de l'élément
    printf("|-- %s\n", noeud->mot);
    //Affichage de ses occurences
    for (int i = 1; i < noeud->nb_occurences; i++)
    {
        printf("|---- (l: %d, o : %d, p : %d)\n")
    }
    printf("|\n");
}

//Fonction qui parcourt l'arbre
void parcoursInfixeAffichage(t_Noeud *noeud, char *dernier_car)
{
    // Si plus de noeud à afficher, on affiche rien
    if (noeud == NULL)
    {
        return ;
    }
    // Parcours du sous arbre gauche
    parcoursInfixeAffichage(noeud->filsGauche, dernier_car);
    //Affichage de l'alphabet si la lettre du mot précédent est différente de celle du mot actuel
    if (strupr(noeud->mot[0]) != *dernier_car)
    {
        //Affichage de la lettre en majuscule
        printf("%c\n", strupr(noeud->mot[0]));
        //Modification de la variable globale dernière lettre
        *dernier_car = strupr(noeud->mot[0]);
    }
    afficheNoeud(noeud);
    // Parcours du sous arbre droit
    parcoursInfixeAffichage(noeud->filsDroit, dernier_car);
}

void afficher_max_apparition(t_Index *index)
{
    t_Noeud *noeud_max = NULL
    parcoursInfixeMaxOccurences(index->racine, noeud_max);
    if (noeud_max != NULL)
    {
        printf("Mot apparaissant le plus dans le texte : %s\n", noeud_max->mot);
        printf("Nombre d'occurences : %d\n", noeud_max->nb_occurences);
    }

}

void parcoursInfixeMaxOccurences(t_Noeud *noeud, t_noeud *noeud_max)
{
    if (noeud == NULL)
    {
        return ;
    }
    //Parcours du sous arbre gauche
    parcoursInfixeMaxOccurences(noeud->filsGauche, noeud_max);
    if (noeud_max == NULL)
    {
        noeud_max = noeud;
    }
    //Si le nombre d'occurences du mot du noeud actuel est supérieur au max
    else if (noeud->nb_occurences > noeud_max->nb_occurences)
    {
        //Changement de la variable globale noeud_max contenant le noeud du mot le plus présent dans le texte
        noeud_max = noeud;
    }
    //Parcours du sous arbre droit
    parcoursInfixeMaxOccurences(noeud->filsDroit, noeud_max)
}


void afficher_occurences_mot(t_Index *index, char *mot)
void afficher_occurences_mot(t_Index *index, char *mot)

#endif // TP4_H
