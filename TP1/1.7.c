// Exercice 1 - Question 7 - Programme qui d�clare un caract�re et l'initialise avec le caract�re '5', puis avec le caract�re correspondant au code ASCII 96.

int main(int argc, char* argv[])
{
    //Premi�re initialisation du caract�re
    char car = '5';
    printf("En initialisation a '5', le caractere est : %c", car);

    //Deuxi�me initialisation
    car = 98;
    printf("En initialisation avec le code ASCII 98, le caractere est : %c", car);


    return 0;
}
