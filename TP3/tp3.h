#ifndef TP3_H
#define TP3_H
#include <stdio.h>

// Structure de l'électeur
typedef struct electeur {
    char* nom;
    long cin_num;
    int choix;
    struct electeur* suivant;
}electeur;

// Pointeur sur la structure electeur
typedef electeur* T_Electeur;



// ----------- B. Fonctions à implémenter : ----------------

T_Electeur creationelecteur(void);

void afficheliste(T_Electeur);

void ajoutelecteur(T_Electeur *, char [], long, int );

int comptelecteur(T_Electeur);

int trouvelecteur(T_Electeur, long);

void Supprimelecteur(T_Electeur *,long);

void decoupeliste(T_Electeur,T_Electeur *,T_Electeur *,T_Electeur*);

void triliste(T_Electeur *);

T_Electeur fusionlistes(T_Electeur, T_Electeur);

int compteGD(T_Electeur);

void libereliste(T_Electeur);


#endif
