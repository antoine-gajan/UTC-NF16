// Exercice 1 - Question 4 - Programme qui donne une temp�rature en degr� Celsius � partir d'une temp�rature Fahrenheit
int main(int argc, char* argv[])
{
    //Initialisation des 2 nombres r�els
    double fahrenheit = 0;

    //Demande de la temp�rature en fahrenheit � l'utilisateur
    printf("Entrez la temp�rature en Fahrenheit : ");
    scanf("%lf", &fahrenheit);

    //Calcul de la temp�rature en Celsius
    double celsius = (fahrenheit - 32) * 5 / 9;
    printf("%.3f degres Fahrenheit = %.3f degres Celsius", fahrenheit, celsius);

    return 0;
}
