// Exercice 1 - Question 5 - Programme qui lit un entier et l'affiche en d�cimal, en octal et en hexad�cimal

int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres r�els
    int nb = 0;

    //Demande du nombre entier
    printf("Entrez le nombre entier : ");
    scanf("%d", &nb);

    //Affichage
    printf("%d en decimal = %o en octal = %x en hexadecimal", nb, nb, nb);

    return 0;
}
