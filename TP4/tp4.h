#include <stdio.h>
#include <stdlib.h>

// A. Structures de données
typedef struct t_position
{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct t_position* suivant;
} t_position;

typedef t_position t_Position;

typedef struct t_listePositions
{
    t_Position *debut;
    int nb_elements;
}t_listePositions;

typedef t_listePositions t_ListePositions;

typedef struct t_noeud
{
    char *mot;
    int nb_occurences;
    t_ListePositions *positions;
    struct t_noeud *filsGauche;
    struct t_noeud *filsDroit;
}t_noeud;

typedef t_noeud t_Noeud;

//Structures supplémentaires (question 9)

typedef struct t_Phrase{
    char *mot;
    struct t_Phrase *suivant;
} t_Phrase;

typedef struct t_ListePhrases{
    t_Phrase *phrase;
    struct t_ListePhrases *suivant;
}t_ListePhrases;

//Structure index modifié pour question 9 et 10
typedef struct t_Index{
    t_Noeud *racine;
    int nb_mots_differents;
    int nb_mots_total;
    t_ListePhrases *liste_phrases;
    t_ListePhrases *liste_lignes;
}t_Index;

typedef t_Index t_index;





// B. Fonctions à implémenter
t_ListePositions* creer_liste_positions();

//Faire un tri pour savoir où ajouter
int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase);

//Faire un malloc classique
t_Index* creer_index();

//Parcours de l'arbre binaire
t_Noeud* rechercher_mot(t_Index *index, char *mot);

// strcmp puis gauche droite pour aller à feuille
int ajouter_noeud(t_Index *index, t_Noeud *noeud);

//lecture fichier
int indexer_fichier(t_Index *index, char *filename);

//Affichage de l'arbre, while sur fichier, while sur phrase et tant que pas point, test si mot est présent test si retour à la ligne
void afficher_index(t_Index *index);

//Parcours de l'arbre, recherche du max (attention exponentielle), tableau
void afficher_max_apparition(t_Index *index);

//Rechercher mot puid afficher occurences, mettre en place structure alternative (attention, ça ajoute des opérations à l'insertion)
void afficher_occurences_mot(t_Index *index, char *mot);


//Fonctions supplémentaires
t_Noeud* max_occurences(t_Noeud *noeud);
t_Phrase *initialiser_phrase(char * mot);
void parcours_infixe_affichage(t_Noeud *noeud, char *dernier_car);
void afficheNoeud(t_Noeud *noeud);
void ajouter_phrase(t_Index* index, t_Phrase *phrase);
void ajouter_mot(t_Phrase *liste, char *mot);
void ajouter_ligne(t_Index *index, t_Phrase *phrase);
void construire_texte(t_Index *index, char *filename);

void to_minuscule(char *chaine);
char majuscule(char c);




