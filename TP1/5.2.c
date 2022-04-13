//Exercice 5 - Question 2 - Transformation

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    char chaine[10];
    printf("Entrez une chaine : ");
    scanf("%s", &chaine);
    int i = 0;
    while (chaine[i] != '\0')
    {
        if (chaine[i] >= 'a' && chaine[i] <= 'z')
        {
            chaine[i] = chaine[i] + 'A' - 'a';
        }
        i ++;
    }
    printf("La chaine transformee est %s", chaine);
    return 0;
}
