// Exercice 1 - Question 1 - Programme qui lit deux réels, les affiche, calcule leur somme et affiche le résultat

int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres réels
    double nb1 = 0, nb2 = 0;

    //Demande des 2 nombres à l'utilisateur
    printf("Entrez le nombre 1 : ");
    scanf("%lf", &nb1);
    printf("Entrez le nombre 2 : ");
    scanf("%lf", &nb2);

    //Affichage des 2 nombres
    printf("Vous avez donné les nombres %f et %f \n", nb1, nb2);

    //Calcul de la somme
    double somme = nb1 + nb2;
    printf("%f + %f = %f", nb1, nb2, somme);

    return 0;
}
