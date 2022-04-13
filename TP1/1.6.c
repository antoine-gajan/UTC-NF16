// Exercice 1 - Question 6 - Programme qui lit un entier et affiche à l'écran si c'est 0, un nombre pair ou un nombre impair

int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres réels
    int nb = 0;

    //Demande du nombre entier
    printf("Entrez le nombre entier : ");
    scanf("%d", &nb);

    //Affichage
    if (nb == 0)
    {
        printf("Le nombre saisi est zero.");
    }
    else if (nb % 2 == 0)
    {
        printf("%d est un nombre pair.", nb);
    }
    else
    {
        printf("%d est un nombre impair.", nb);
    }

    return 0;
}
