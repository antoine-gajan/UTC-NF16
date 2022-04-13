// Exercice 2 - Question 1 - Programme qui teste si un caractère saisi au clavier est un chiffre ou si c'est un caractère compris entre 'a' et 'z' ou encore entre 'A' et 'Z'.

int main(int argc, char* argv[])
{
    //Demande du caractère
    printf("Entrez un caractere : ");
    char car = getchar();

    //Test et affichage
    if (car >= '0' && car <= '9')
    {
        printf("%c est un chiffre.", car);
    }
    else if (car >= 'a' && car <= 'z')
    {
        printf("%c est une lettre minuscule.", car);
    }
    else if (car >= 'A' && car <= 'Z')
    {
        printf("%c est une lettre majuscule.", car);
    }

    return 0;
}
