#include "string.h"

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
    pos->numero_ligne = ligne;
    pos->numero_phrase = num_phrase;
    pos->ordre = ordre;
    if (listeP->debut == NULL)
    {
        //Ajout en début de liste
        listeP->debut = pos;
    }
    else
    {
        //Tri
        while (pos->numero_ligne < listeP->debut->numero_ligne)
        {


        }
    }
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
    if(index == NULL)
    {
        return NULL;
    }
    t_Noeud *actuel = index->racine;
    while (actuel != NULL)
    {
        if (strcmp(actuel->mot, mot) < 0)
        {
            actuel = actuel->filsGauche;
        }
        else if (strcmp(actuel->mot, mot) == 0)
        {
            return actuel;
        }
        else
        {
            actuel = actuel->filsDroit;
        }
    }
}


