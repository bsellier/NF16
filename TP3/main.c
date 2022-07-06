#include <stdio.h>
#include "tp3.h"

int choixLexique()
{
    int choixLexique = 0;
    while( choixLexique != 1 && choixLexique != 2)
    {
        printf("\nQuel lexique voulez-vous utiliser ? (1 ou 2)\n");
        scanf("%d", &choixLexique);
        fflush(stdin);
    }

    return choixLexique;
}

int main()
{

    char choixMenu = '0' ;

    t_mot *lexique1 = NULL;
    t_mot *lexique2 = NULL;

    do {
        printf("\n========================================");
        printf("\n  [1] Afficher un lexique");
        printf("\n  [2] Ajouter un mot dans un lexique");
        printf("\n  [3] Retirer un mot d'un lexique");
        printf("\n  [4] Fusionner deux lexiques");
        printf("\n  [5] Charger un fichier dans un lexique");
        printf("\n  [6] Quitter");
        printf("\n========================================");
        printf("\nVotre choix : ");
        choixMenu = getchar();
        viderBuffer();

        char mot[60];
        int lex;

        switch (choixMenu) {
            case '1' : //Afficher lexique
                if(choixLexique() == 1)
                    afficherMots(lexique1);
                else
                    afficherMots(lexique2);
                break;

            case '2' : //Ajouter un mot dans un lexique
                lex = choixLexique();
                printf("\nEntrez le mot a ajouter : ");
                gets(mot);
                fflush(stdin);

                if(lex == 1)
                    lexique1 = ajouterMot(lexique1, mot);
                else
                    lexique2 = ajouterMot(lexique2, mot);

                break;

            case '3' : //Retirer un mot d'un lexique
                lex = choixLexique();
                printf("\nEntrez le mot a retirer : ");
                gets(mot);
                if(lex == 1)
                    lexique1 = retirerMot(lexique1, mot);
                else
                    lexique2 = retirerMot(lexique2, mot);
                break;

            case '4' : //Fusionner deux lexiques
                printf("Fusion des deux lexiques.\n");
                lexique1 = fusionner(lexique1, lexique2);
                lexique2 = NULL;
                break;

            case '5' :
                printf("\n");
                lex = choixLexique();
                if(lex == 1)
                    lexique1 = importerFichier(lexique1);
                else if(lex == 2)
                    lexique2 = importerFichier(lexique2);

                break;
            default:
                break;
        }
    } while (choixMenu != '6');

//libération de la mémoire allouée
    freeLexique(lexique1);
    freeLexique(lexique2);

    printf("\n\n*** FIN DU PROGRAMME ***\n");

    return 0;
}
