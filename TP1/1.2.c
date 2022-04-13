// Exercice 1 - Question 2 - Programme qui permute les valeurs de deux variables lues au clavier

int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres réels
    double a = 0, b = 0;

    //Demande des 2 nombres à l'utilisateur
    printf("Entrez a : ");
    scanf("%lf", &a);
    printf("Entrez b : ");
    scanf("%lf", &b);

    //Affichage des 2 nombres
    printf("Avant permutation, a = %f et b = %f \n", a, b);

    //Permutation
    double temp = a;
    a = b;
    b = temp;

    printf("Apres permutation, a = %f et b = %f", a, b);

    return 0;
}
