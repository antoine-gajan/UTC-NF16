// Exercice 1 - Question 5 - Programme qui lit un entier et l'affiche en décimal, en octal et en hexadécimal

int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres réels
    int nb = 0;

    //Demande du nombre entier
    printf("Entrez le nombre entier : ");
    scanf("%d", &nb);

    //Affichage
    printf("%d en decimal = %o en octal = %x en hexadecimal", nb, nb, nb);

    return 0;
}
