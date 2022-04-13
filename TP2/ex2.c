#define NMAX 10

typedef struct Un_Tableau_Entier
{
    int tableau[NMAX];
    int ncase;
} Un_Tableau_Entier;

typedef struct menu
{
    char tableau[20][60];
    int n;
} menu;

typedef struct tonneau
{
    double d;
    double D;
    double L;
    char *chose;
}tonneau;

double volume(tonneau *t)
{
    return 3.14159 * t->L * (t->d/2 + 2/3*(t->D/2-t->d/2))/2;
}
