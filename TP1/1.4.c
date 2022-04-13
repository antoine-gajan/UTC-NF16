// Exercice 1 - Question 4 - Programme qui donne une température en degré Celsius à partir d'une température Fahrenheit
int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres réels
    double fahrenheit = 0;

    //Demande de la température en fahrenheit à l'utilisateur
    printf("Entrez la température en Fahrenheit : ");
    scanf("%lf", &fahrenheit);

    //Calcul de la température en Celsius
    double celsius = (fahrenheit - 32) * 5 / 9;
    printf("%.3f degres Fahrenheit = %.3f degres Celsius", fahrenheit, celsius);

    return 0;
}
