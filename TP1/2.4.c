// Exercice 2 - Question 4 - Switch

int main(int argc, char* argv[])
{
    //Demande du caractère
    printf("Entrez un caractere : ");
    char car = getchar();

    //Condition avec switch
    switch (car)
    {
    case '1':
        printf("un");
        break;

    case '2':
        printf("deux");
        break;

    case '3':
        printf("trois");
        break;

    default:
        printf("autre caractere");
    }

    return 0;
}
