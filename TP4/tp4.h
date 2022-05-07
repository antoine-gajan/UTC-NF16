// A. Structures de données
typedef struct t_position
{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    int EstMajuscule;
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
    t_ListePositions positions;
    struct t_noeud *filsGauche;
    struct t_noeud *filsDroit;
}t_noeud;

typedef t_noeud t_Noeud;

typedef struct t_index
{
    t_Noeud *racine;
    int nb_mots_differents;
    int nb_mots_total;
}t_index;

typedef t_index t_Index;


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


