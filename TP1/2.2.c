// Exercice 2 - Question 2 - Programme qui lit une suite d'entiers strictement positifs et qui s'arrête si on saisit la valeur -1.

int main(int argc, char* argv[])
{
    int nb = 0;
    //Boucle pour continuer tant que les entiers sont strictements positifs et différents de -1
    do
    {
        //Demande d'un entier strictement positif
        printf("Entrez un entier strictement positif : ");
        scanf("%d", &nb);

    } while (nb > 0 && nb != -1);

    return 0;
}
