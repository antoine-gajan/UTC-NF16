// Exercice 1 - Question 7 - Programme qui déclare un caractère et l'initialise avec le caractère '5', puis avec le caractère correspondant au code ASCII 96.

int main(int argc, char* argv[])
{
    //Première initialisation du caractère
    char car = '5';
    printf("En initialisation a '5', le caractere est : %c", car);

    //Deuxième initialisation
    car = 98;
    printf("En initialisation avec le code ASCII 98, le caractere est : %c", car);


    return 0;
}
