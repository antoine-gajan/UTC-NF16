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
    if(rechercher_mot(index,noeud->mot)==NULL)
    {
        t_Noeud *pere=NULL;
        t_Noeud *actuel=index->racine;
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
        if(pere==NULL)
        {
            index->racine = noeud;
        }
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
    else
    {
        printf("Erreur: noeud dejà existant\n");
        return 0;
    }
}

int indexer_fichier(t_Index *index, char *filename)
{
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

    fichier = fopen(filename, "r");

    if (fichier != NULL)
    {
        int ligne=1;
        int ordre;
        const char *sep = " ";

        while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
            ordre=1;
            to_minuscule(chaine);
            printf("Ligne %d : %s\n", ligne, chaine); //Test debug

            taille = strlen(chaine);
            if (chaine[taille - 1] == '\n')
            {
                chaine[taille - 1] = '\0';
            }

            char *mot = strtok (chaine, sep);
            while (mot != NULL)
            {
                taille = strlen(mot);
                if (mot[taille-1] == '.')
                {
                    mot[taille - 1] = '\0';
                    changer_phrase=1;
                }

                printf ("Mot ajoute : %s\n", mot); //test debug

                t_Noeud *noeud = rechercher_mot(index, mot);

                //Si le mot n'est pas dans l'index, creation du noeud
                if (noeud==NULL)
                {
                    noeud=malloc(sizeof(t_Noeud));
                    t_ListePositions *listeP = creer_liste_positions();
                    if(noeud != NULL && listeP != NULL)
                    {
                        noeud->mot = malloc(sizeof(mot));
                        strcpy(noeud->mot, mot);

                        noeud->nb_occurences=1;

                        noeud->filsGauche=NULL;
                        noeud->filsDroit=NULL;

                        ajouter_position(listeP, ligne, ordre, num_phrase);
                        noeud->positions = listeP;

                        ajouter_noeud(index, noeud);

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
                    index->nb_mots_total++;
                }

                if (nouvelle_phrase==1)
                {
                    phrase_courante = initialiser_phrase(mot);
                    nouvelle_phrase=0;
                }
                else
                {
                    ajouter_mot(phrase_courante,mot);
                }

                if (nouvelle_ligne==1)
                {
                    ligne_courante = initialiser_phrase(mot);
                    nouvelle_ligne=0;
                }
                else
                {
                    ajouter_mot(ligne_courante,mot);
                }

                mot = strtok(NULL, sep);
                ordre++;
                nb_mots++;
                if (changer_phrase==1)
                {
                    ajouter_phrase(index,phrase_courante);
                    num_phrase++;
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
        afficheNoeud(noeud);
    }
    else
    {
        afficheNoeud(noeud);
    }
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
        //Affichage de ses caractéristiques
        printf("Mot apparaissant le plus dans le texte : %s\n", noeud_max->mot);
        printf("Nombre d'occurences : %d\n", noeud_max->nb_occurences);
    }
}

//Fonction récursive qui renvoie le noeud ayant le maximum d'occurences sur un arbre
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
    //Sinon, on retourne le noeud père, seul noeud de l'arbre car on a atteint une feuille
    else
    {
        return noeud;
    }
}

t_Phrase *initialiser_phrase(char * mot)
{
    t_Phrase *phrase = malloc(sizeof(phrase));
    if (phrase != NULL)
    {
        phrase->mot = malloc(strlen(mot) * sizeof(char));
        strcpy(phrase->mot, mot);
        phrase->suivant = NULL;
    }
    return phrase;
}

void ajouter_mot(t_Phrase *liste, char *mot)
{
    if (liste != NULL)
    {
        if (liste->suivant == NULL)
        {
            liste->suivant = initialiser_phrase(mot);
        }
        else
        {
            ajouter_mot(liste->suivant, mot);
        }
    }
}

void ajouter_phrase(t_Index *index, t_Phrase *phrase)
{
    t_ListePhrases * nouv = malloc(sizeof(t_ListePhrases));
    if (nouv != NULL)
    {
        nouv->phrase = phrase;
        nouv->suivant = NULL;
        if (index->liste_phrases == NULL)
        {
            index->liste_phrases = nouv;
        }
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

void ajouter_ligne(t_Index *index, t_Phrase *p)
{
    t_ListePhrases * nouv = malloc(sizeof(t_ListePhrases));
    if (nouv != NULL)
    {
        nouv->phrase = p;
        nouv->suivant = NULL;
        if (index->liste_lignes == NULL)
        {
            index->liste_lignes = nouv;
        }
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

void afficher_occurences_mot(t_Index *index, char *mot)
{
    int debut_phrase;
    int i = 1;
    t_ListePhrases *p = index->liste_phrases;
    t_Phrase *m = NULL;
    to_minuscule(mot);
    t_Noeud *noeud = rechercher_mot(index, mot);
    if (noeud != NULL)
    {
        mot[0] = majuscule(mot[0]);
        printf("Mot = \"%s\"\n", mot);
        printf("Occurences = %d\n", noeud->nb_occurences);
        t_Position *pos = noeud->positions->debut;
        while (pos != NULL)
        {
            debut_phrase = 1;
            while (i < pos->numero_phrase)
            {
                p = p->suivant;
                i++;
            }
            printf("| Ligne %d, mot %d : ", pos->numero_ligne, pos->ordre);
            m = p->phrase;
            while (m != NULL)
            {
                if (debut_phrase)
                {
                    m->mot[0] = majuscule(m->mot[0]);
                    printf("%s", m->mot);
                    to_minuscule(m->mot);
                    debut_phrase = 0;
                }
                else
                {
                    printf("%s", m->mot);
                }
                if (m->suivant != NULL)
                {
                    printf(" ");
                }
                m = m->suivant;
            }
            printf(".\n");
            pos = pos->suivant;
        }
    }
    else
    {
        printf("Le mot '%s' n'est pas dans l'index\n", mot);
    }
}

void construire_texte(t_Index *index, char *filename)
{
    int debut_phrase = 1;
    FILE *f = fopen(filename, "w");
    if (f != NULL)
    {
        t_ListePhrases *l = index->liste_lignes;
        t_ListePhrases *lp = index->liste_phrases;
        t_Phrase *m = lp->phrase;

        while (l != NULL)
        {
            t_Phrase *p = l->phrase;
            while (p != NULL)
            {
                if (m->suivant != NULL)
                {
                    m = m->suivant;
                    if (debut_phrase == 1)
                    {
                        p->mot[0] = majuscule(p->mot[0]);
                        fprintf(f, "%s ", p->mot);
                        to_minuscule(p->mot);
                        debut_phrase = 0;
                    }
                    else
                    {
                        fprintf(f, "%s ", p->mot);
                    }
                }
                else
                {
                    lp = lp->suivant;
                    if (lp != NULL)
                    {
                        m = lp->phrase;
                    }
                    if (debut_phrase == 1)
                    {
                        p->mot[0] = majuscule(p->mot[0]);
                        fprintf(f, "%s. ", p->mot);
                        to_minuscule(p->mot);
                    }
                    else
                    {
                        fprintf(f, "%s. ", p->mot);
                        debut_phrase = 1;
                    }
                }
                p = p->suivant;
            }
            fprintf(f, "\n");
            l = l->suivant;
        }
        fclose(f);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
}


void to_minuscule(char *chaine)
{
    for (int i=0;i<strlen(chaine);i++)
    {
        if(chaine[i]>='A' && chaine[i]<='Z')
        {
            chaine[i]=chaine[i]+32;
        }
    }
}

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

void vider_buffer()
{
    while (getchar() != '\0');
}
#endif // TP4_H
