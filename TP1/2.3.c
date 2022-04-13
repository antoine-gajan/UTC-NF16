// Exercice 2 - Question 3 - Table de multiplication

int main(int argc, char* argv[])
{
    char car = 0;
    do
    {
        //Demande du caractère
        printf("Quelle table de multiplication voulez-vous, tapez 0 (zero) pour sortir ?");
        car = getchar();
        //Test si le caractère est valide
        if (car >= '1' && car <= '9')
        {
            int nb_saisi = car - 48;
            //Boucle pour afficher la table
            for (int i = 0; i <= 9; i++)
            {
                printf("%d * %d = %d \n", nb_saisi, i, i * nb_saisi);
            }
        }
        //Message d'erreur
        else if (car == '0')
        {
            printf("Sortie du programme.");
        }
        else
        {
            printf("Ce n'est pas dans les possibilités du programme, recommencez !\n");
        }

    } while (car < '0' || car > '9');




    return 0;
}
