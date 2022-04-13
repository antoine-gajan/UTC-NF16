// Exercice 1 - Question 3 - Programme qui calcule le pourcentage x d'un nombre y. Ce nombre ainsi que le pourcentage sont saisis au clavier

int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres réels
    double x = 0, y = 0;

    //Demande des 2 nombres à l'utilisateur
    printf("Entrez le pourcentage x (en pourcent) : ");
    scanf("%lf", &x);
    printf("Entrez le nombre y : ");
    scanf("%lf", &y);

    //Calcul du pourcentage
    double pourcentage = x / 100 * y;
    printf("%f pour cent de %f = %f", x, y, pourcentage);

    return 0;
}
