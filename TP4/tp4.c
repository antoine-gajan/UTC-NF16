#ifndef TP4_H
#define TP4_H

#include <string.h>
#include <stdlib.h>
#include "tp4.h"
#define TAILLE_MAX 1000


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
    //Initialisation des attributs
    pos->numero_ligne = ligne;
    pos->numero_phrase = num_phrase;
    pos->ordre = ordre;
    pos->suivant = NULL;
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

        //Ordre par numéro de ligne et ordre du mot dans la ligne
        while (actuel!=NULL && (actuel->numero_ligne < ligne || actuel->ordre < ordre))
            {
                prec = actuel;
                actuel=actuel->suivant;
            }
        if (actuel != NULL && actuel->numero_ligne == ligne && actuel->ordre == ordre)
        {
            printf("Erreur: position dejà existante\n");
            return 0;
        }
        //Ajout au début et liste non vide
        if (prec == NULL)
        {
            pos->suivant = listeP->debut;
            listeP->debut = pos;
        }
        //Ajout en fin de liste
        else if(actuel == NULL)
        {
            prec->suivant=pos;
        }
        //Ajout en milieu de liste
        else
        {
            pos->suivant=actuel;
            prec->suivant=pos;
        }
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
        arbre->liste_lignes = NULL;
        arbre->liste_phrases = NULL;
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
        if (strcmp(actuel->mot, mot) > 0)
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
    //Si un noeud avec le même mot existe déjà, on n'ajoute pas le noeud et renvoie une erreur
    if(rechercher_mot(index,noeud->mot)==NULL)
    {
        t_Noeud *pere=NULL;
        t_Noeud *actuel=index->racine;
        //Parcours de l'arbre pour trouver où ajouter le noeud
        while(actuel!=NULL)
        {
            pere=actuel;
            if(strcmp(actuel->mot,noeud->mot)>0)
            {
                actuel=actuel->filsGauche;
            }
            else
            {
                actuel=actuel->filsDroit;
            }
        }
        //Si le père est NULL, on ajoute le noeud à la racine
        if(pere==NULL)
        {
            index->racine = noeud;
        }
        //Sinon on regarde si c'est le fils gauche ou droit du père
        else
        {
            if(strcmp(pere->mot,noeud->mot) > 0)
            {
                pere->filsGauche = noeud;
            }
            else
            {
                pere->filsDroit = noeud;
            }
        }
        return 1;
    }
    //Affichage code erreur
    else
    {
        printf("Erreur: noeud dejà existant\n");
        return 0;
    }
}

//Fonction qui indexe le fichier dans un ABR
int indexer_fichier(t_Index *index, char *filename)
{
    //Définition des variables
    int nb_mots=1;
    int num_phrase=1;
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";
    unsigned long taille;
    int changer_phrase=0;
    t_Phrase *phrase_courante=NULL;
    int nouvelle_phrase=1;
    t_Phrase *ligne_courante=NULL;
    int nouvelle_ligne=1;

    //Ouverture du fichier
    fichier = fopen(filename, "r");
    //Si l'ouverture du fichier a réussi, on lit le fichier
    if (fichier != NULL)
    {
        int ligne=1;
        int ordre;
        const char *sep = " ";
        //Lecture du fichier ligne par ligne
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
            ordre=1;
            //Conversion de la chaine en minuscule
            to_minuscule(chaine);

            //Si la chaine comporte un point ou un \n, c'est soit fin de phrase, soit fin de ligne
            taille = strlen(chaine);
            if (chaine[taille - 1] == '\n')
            {
                //Suppression du \n en fin de chaine
                chaine[taille - 1] = '\0';
            }
            //Extraction d'un mot de la ligne
            char *mot = strtok (chaine, sep);
            //Tant qu'on n'est pas en fin de ligne
            while (mot != NULL)
            {
                taille = strlen(mot);
                if (mot[taille-1] == '.')
                {
                    //On remplace le . de fin de phrase
                    mot[taille - 1] = '\0';
                    changer_phrase=1;
                }

                t_Noeud *noeud = rechercher_mot(index, mot);

                //Si le mot n'est pas dans l'index, creation du noeud
                if (noeud==NULL)
                {
                    //Allocation dynamique du noeud
                    noeud=malloc(sizeof(t_Noeud));
                    //Création de la liste de positions
                    t_ListePositions *listeP = creer_liste_positions();
                    if(noeud != NULL && listeP != NULL)
                    {
                        //Ajout des attributs
                        noeud->mot = malloc(sizeof(mot));
                        strcpy(noeud->mot, mot);

                        noeud->nb_occurences=1;

                        noeud->filsGauche=NULL;
                        noeud->filsDroit=NULL;
                        //Ajout de la position du mot à la liste des positions du mot
                        ajouter_position(listeP, ligne, ordre, num_phrase);
                        noeud->positions = listeP;
                        //Ajout du noeud à l'index
                        ajouter_noeud(index, noeud);
                        //Mise à jour des attributs de l'index
                        index->nb_mots_differents++;
                        index->nb_mots_total++;
                    }
                    else
                    {
                        printf("Erreur: allocation memoire\n");
                        return 0;
                    }
                }
                //Si le mot existe dans l'index, ajout de la position
                else
                {
                    noeud->nb_occurences++;
                    ajouter_position(noeud->positions, ligne, ordre, num_phrase);
                    //Modification des attributs de l'index
                    index->nb_mots_total++;
                }
                //Si une nouvelle phrase doit être crée (changement de la valeur du booléen à l'itération précédente)
                if (nouvelle_phrase==1)
                {
                    phrase_courante = initialiser_phrase(mot);
                    nouvelle_phrase=0;
                }
                //Sinon, on ajoute le mot à la phrase courante
                else
                {
                    ajouter_mot(phrase_courante,mot);
                }
                //Si un une nouvelle ligne doit être crée, on l'initialise avec le premier mot de la ligne
                if (nouvelle_ligne==1)
                {
                    ligne_courante = initialiser_phrase(mot);
                    nouvelle_ligne=0;
                }
                //Sinon on ajoute le mot à la ligne courante
                else
                {
                    ajouter_mot(ligne_courante,mot);
                }
                //Extraction du mot suivant
                mot = strtok(NULL, sep);
                ordre++;
                nb_mots++;
                //Si un . a été rencontré avant, changement de phrase
                if (changer_phrase==1)
                {
                    //On ajoute la phrase complète à l'index
                    ajouter_phrase(index,phrase_courante);
                    //Incrémentation du numéro de phrase
                    num_phrase++;
                    //Mise à jour des booléens
                    changer_phrase = 0;
                    nouvelle_phrase=1;
                }
            }
            ligne++;
            ajouter_ligne(index,ligne_courante);
            nouvelle_ligne=1;
        }
        fclose(fichier);
        return nb_mots;
    }
    else
    {
        printf("Erreur: fichier non trouve\n");
        return 0;
    }
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
        char dernier[] = "(";
        parcours_infixe_affichage(index->racine, dernier);
    }
}

void afficheNoeud(t_Noeud *noeud)
{
    // Affichage de l'élément
    printf("|-- %s\n", noeud->mot);
    //Affichage de ses occurences
    t_Position *pos = noeud->positions->debut;
    while (pos != NULL)
    {
        printf("|---- (l: %d, o : %d, p : %d)\n", pos->numero_ligne, pos->ordre, pos->numero_phrase);
        pos = pos->suivant;
    }
    printf("|\n");
}

//Fonction qui parcourt l'arbre
void parcours_infixe_affichage(t_Noeud *noeud, char *dernier_car)
{
    // Si plus de noeud à afficher, on affiche rien
    if (noeud == NULL)
    {
        return;
    }
    // Parcours du sous arbre gauche
    parcours_infixe_affichage(noeud->filsGauche, dernier_car);
    //Affichage de l'alphabet si la lettre du mot précédent est différente de celle du mot actuel
    if (*dernier_car == '(' || majuscule((noeud->mot)[0]) != *dernier_car)
    {
        printf("\n%c\n", majuscule((noeud->mot)[0]));
        *dernier_car = majuscule((noeud->mot)[0]);
    }
    //Affichage du noeud
    afficheNoeud(noeud);
    // Parcours du sous arbre droit
    parcours_infixe_affichage(noeud->filsDroit, dernier_car);
}

void afficher_max_apparition(t_Index *index)
{
    //Si l'arbre est vide
    if (index == NULL || index->racine == NULL)
    {
        printf("L'arbre est vide.\n");
        return;
    }
    //Recherche du noeud dont le mot apparait le plus souvent
    t_Noeud *noeud_max = max_occurences(index->racine);
    if (noeud_max != NULL)
    {
        //Affichage de ses caractéristiques
        printf("Mot apparaissant le plus dans le texte : %s\n", noeud_max->mot);
        printf("Nombre d'occurences : %d\n", noeud_max->nb_occurences);
    }
}

//Fonction récursive qui renvoie le noeud ayant le maximum d'occurences sur un arbre
t_Noeud* max_occurences(t_Noeud *noeud)
{
    //Si le noeud est non null
    if (noeud != NULL)
    {
        //Recherche du max dans les sous arbres
        t_Noeud * max_gauche = max_occurences(noeud->filsGauche);
        t_Noeud * max_droit = max_occurences(noeud->filsDroit);
        //Distinction des cas pour trouver le max
        if (max_gauche != NULL && max_droit != NULL)
        {
            if (max_gauche->nb_occurences > max_droit->nb_occurences)
            {
                if (noeud->nb_occurences > max_gauche->nb_occurences)
                {
                    return noeud;
                }
                else
                {
                    return max_gauche;
                }
            }
            else
            {
                if (noeud->nb_occurences > max_droit->nb_occurences)
                {
                    return noeud;
                }
                else
                {
                    return max_droit;
                }
            }
        }
        else if (max_gauche != NULL)
        {
            if (noeud->nb_occurences > max_gauche->nb_occurences)
            {
                return noeud;
            }
            else
            {
                return max_gauche;
            }
        }
        else if (max_droit != NULL)
        {
            if (noeud->nb_occurences > max_droit->nb_occurences)
            {
                return noeud;
            }
            else
            {
                return max_droit;
            }
        }
        else
        {
            return noeud;
        }
    }
    return NULL;
}

//Fonction pour initialiser une phrase avec un mot
t_Phrase *initialiser_phrase(char * mot)
{
    //Allocation dynamique de la mémoire
    t_Phrase *phrase = malloc(sizeof(t_Phrase));
    if (phrase != NULL)
    {
        //Ajout des attributs (et allocation dynamique pour le mot)
        phrase->mot = malloc(strlen(mot) * sizeof(char));
        strcpy(phrase->mot, mot);
        phrase->suivant = NULL;
    }
    return phrase;
}

//Fonction pour ajouter un mot à une phrase
void ajouter_mot(t_Phrase *phrase, char *mot)
{
    if (phrase != NULL)
    {
        //Si pas de phrase suivante crée, on en initialise une nouvelle avec le mot courant
        if (phrase->suivant == NULL)
        {
            phrase->suivant = initialiser_phrase(mot);
        }
        //Sinon, on ajoute le mot à la phrase suivante déjà crée
        else
        {
            ajouter_mot(phrase->suivant, mot);
        }
    }
}

//Fonction pour ajouter une phrase à l'index
void ajouter_phrase(t_Index *index, t_Phrase *phrase)
{
    //Allocation dynamique de la mémoire pour la liste de phrases
    t_ListePhrases * nouv = malloc(sizeof(t_ListePhrases));
    if (nouv != NULL)
    {
        //Ajout des attributs
        nouv->phrase = phrase;
        nouv->suivant = NULL;
        //Si pas de listes de phrases présente, on l'ajoute en début de liste
        if (index->liste_phrases == NULL)
        {
            index->liste_phrases = nouv;
        }
        //Sinon on parcourt la liste et on l'ajoute en fin de liste
        else
        {
            t_ListePhrases *courant = index->liste_phrases;
            while (courant->suivant != NULL)
            {
                courant = courant->suivant;
            }
            courant->suivant = nouv;
        }
    }
}

//Fonction qui permet d'ajouter une ligne à une phrase
void ajouter_ligne(t_Index *index, t_Phrase *p)
{
    //Allocation dynamique d'une nouvelle phrase
    t_ListePhrases * nouv = malloc(sizeof(t_ListePhrases));
    if (nouv != NULL)
    {
        //Ajout des attributs
        nouv->phrase = p;
        nouv->suivant = NULL;
        //Si la liste de lignes est vide, on l'ajoute au début
        if (index->liste_lignes == NULL)
        {
            index->liste_lignes = nouv;
        }
        //Sinon on l'ajoute en fin de liste
        else
        {
            t_ListePhrases *courant = index->liste_lignes;
            while (courant->suivant != NULL)
            {
                courant = courant->suivant;
            }
            courant->suivant = nouv;
        }
    }
}

//Fonction qui affiche les occurences d'un mot
void afficher_occurences_mot(t_Index *index, char *mot)
{
    //Déclaration des variables
    int debut_phrase;
    int i = 1;
    t_ListePhrases *p = index->liste_phrases;
    t_Phrase *m = NULL;
    //Mise en minuscule du mot
    to_minuscule(mot);
    t_Noeud *noeud = rechercher_mot(index, mot);
    //Si le mot existe bien dans l'ABR
    if (noeud != NULL)
    {
        //Mise en mjuscule de la première lettre du mot
        mot[0] = majuscule(mot[0]);
        //Affichage
        printf("Mot = \"%s\"\n", mot);
        printf("Occurences = %d\n", noeud->nb_occurences);
        //Parcours des positions et affichage
        t_Position *pos = noeud->positions->debut;
        while (pos != NULL)
        {
            debut_phrase = 1;
            while (i < pos->numero_phrase)
            {
                p = p->suivant;
                i++;
            }
            //Affichage du numéro de ligne et d'ordre du mot
            printf("| Ligne %d, mot %d : ", pos->numero_ligne, pos->ordre);
            m = p->phrase;
            //Affichage des mots de la phrase
            while (m != NULL)
            {
                //Si c'est le premier mot de la phrase, on le met en majuscule
                if (debut_phrase)
                {
                    m->mot[0] = majuscule(m->mot[0]);
                    printf("%s", m->mot);
                    to_minuscule(m->mot);
                    debut_phrase = 0;
                }
                //Sinon on affiche juste le mot
                else
                {
                    printf("%s", m->mot);
                }
                //Ajout d'un espace entre les mots
                if (m->suivant != NULL)
                {
                    printf(" ");
                }
                //Passage au mot suivant
                m = m->suivant;
            }
            //En fin de ligne, on ajoute le point et le \n
            printf(".\n");
            pos = pos->suivant;
        }
    }
    else
    {
        printf("Le mot '%s' n'est pas dans l'index\n", mot);
    }
}

//Fonction qui construit le texte et l'écrit dans un nouveau fichier
void construire_texte(t_Index *index, char *filename)
{
    int debut_phrase = 1;
    //Ouverture du fichier en écriture
    FILE *fichier;
    fichier = fopen(filename, "w");
    //Si l'ouverture a fonctionné
    if (fichier != NULL)
    {
        //Initialisation de l et lp, qui représentent la liste de lignes et la liste de phrases
        t_ListePhrases *l = index->liste_lignes;
        t_ListePhrases *lp = index->liste_phrases;
        //m est le premier mot de la phrase
        t_Phrase *m = lp->phrase;
        //Tant qu'il reste des lignes à écrire
        while (l != NULL)
        {
            t_Phrase *p = l->phrase;
            //Tant qu'il reste des mots à écrire
            while (p != NULL)
            {
                //Si on n'est pas en fin de phrase (il y a encore des mots après)
                if (m->suivant != NULL)
                {
                    m = m->suivant;
                    //Si on est en début de phrase
                    if (debut_phrase == 1)
                    {
                        //On met la première lettre en majuscule
                        p->mot[0] = majuscule(p->mot[0]);
                        fprintf(fichier, "%s ", p->mot);
                        to_minuscule(p->mot);
                        //Mise à jour du booléen début_phrase à 0
                        debut_phrase = 0;
                    }
                    //Sinon on écrit le mot en minuscule
                    else
                    {
                        fprintf(fichier, "%s ", p->mot);
                    }
                }
                //Si on est en fin de phrase
                else
                {
                    lp = lp->suivant;
                    //On initialise m avec le premier mot de la phrase suivante
                    if (lp != NULL)
                    {
                        m = lp->phrase;
                    }
                    //Cas particulier : c'est une phrase constituée d'un seul mot
                    if (debut_phrase == 1)
                    {
                        p->mot[0] = majuscule(p->mot[0]);
                        fprintf(fichier, "%s. ", p->mot);
                        to_minuscule(p->mot);
                    }
                    //Si on est en fin de phrase "classique", on ajoute le point à la fin du mot et l'espace qui suit
                    else
                    {
                        fprintf(fichier, "%s. ", p->mot);
                        debut_phrase = 1;
                    }
                }
                //Passage à la phrase suivante
                p = p->suivant;
            }
            //Passage à la ligne suivante
            fprintf(fichier, "\n");
            l = l->suivant;
        }
        //Fermeture du fichier
        fclose(fichier);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
}

//Fonction qui transforme une chaine en minuscule
void to_minuscule(char *chaine)
{
    //Parcours de chaque lettre et mise en minuscule
    for (int i=0;i<strlen(chaine);i++)
    {
        if(chaine[i]>='A' && chaine[i]<='Z')
        {
            chaine[i]=chaine[i]+32;
        }
    }
}

//Fonction qui renvoie le caractère majuscule correspondant
char majuscule(char car)
{
    if(car>='a' && car<='z')
    {
        return car-32;
    }
    else
    {
        return car;
    }
}

int hauteur(t_Noeud *racine)
{
    //Si l'arbre est vide, la hauteur vaut -1
    if (racine == NULL)
    {
        return -1;
    }
    //Si on est au niveau d'une feuille, la hauteur vaut 0
    else if (racine->filsGauche == NULL && racine->filsDroit == NULL)
    {
        return 0;
    }
    else
    {
        int hauteur_gauche = hauteur(racine->filsGauche);
        int hauteur_droite = hauteur(racine->filsDroit);
        if (hauteur_droite > hauteur_gauche)
        {
            return 1 + hauteur_droite;
        }
        else
        {
            return 1 + hauteur_gauche;
        }
    }
}

int equilibre(t_Noeud *racine)
{
    if (racine == NULL)
    {
        return 1;
    }
    else if (abs(hauteur(racine->filsGauche) - hauteur(racine->filsDroit)) <= 1)
    {
        return equilibre(racine->filsGauche) && equilibre(racine->filsDroit);
    }
    else
    {
        return 0;
    }
}

void libererIndex(t_Index *index)
{
    //Libération de l'arbre
    libererArbre(index->racine);
    //Liberation des liste de phrases
    free(index->liste_lignes);
    free(index->liste_phrases);
    //Libération de l'index
    free(index);

}

void libererArbre(t_Noeud *racine)
{
    if (racine != NULL)
    {
        //Liberation des sous arbres gauche et droit
        libererArbre(racine->filsGauche);
        libererArbre(racine->filsDroit);
        //Libération de la liste des positions
        t_Position *pos = racine->positions->debut;
        while (pos != NULL)
        {
            t_Position *copie = pos;
            pos = pos->suivant;
            free(copie);
        }
        free(racine->positions);
        //Libération du noeud
        free(racine);
    }
}

void libererListePhrases(t_ListePhrases *liste)
{
    t_Phrase *p = liste->phrase;

    while (p != NULL)
    {
        t_Phrase *copie = p;
        p = p->suivant;
        libererPhrase(copie);
    }
    free(liste);
}

void libererPhrase(t_Phrase *p)
{
    while (p != NULL)
    {
        t_Phrase *copie = p;
        p = p->suivant;
        free(copie->mot);
        free(copie);
    }
}

//Fonction pour vider le buffer
void vider_buffer()
{
    while (getchar() != '\n');
}
#endif // TP4_H
