#include <stdio.h>
#include "arbre.h"

int choixArbre()
{
    int choixLexique = 0;
    while( choixLexique != 1 && choixLexique != 2)
    {
        printf("\nQuel arbre voulez-vous utiliser ? (1 ou 2)\n");
        scanf("%d", &choixLexique);
        fflush(stdin);
    }

    return choixLexique;
}

int main() {

    T_Arbre arbre = NULL, arbre2 = NULL;
    t_mot *lexique = NULL, *lexique2 = NULL;

    char choixMenu;
    do {
        printf("\n========================================");
        printf("\n  [1] Creer un nouvel arbre");
        printf("\n  [2] Afficher un arbre");
        printf("\n  [3] Ajouter un mot dans un arbre");
        printf("\n  [4] Retirer un mot d'un arbre");
        printf("\n  [5] Verifier si un arbre est parfait");
        printf("\n  [6] Verifier si un arbre est equilibre");
        printf("\n  [7] Transformer un arbre en un lexique en liste lineairement chainee et afficher le lexique");
        printf("\n  [8] Tester la similarite entre deux textes");
        printf("\n  [9] Quitter");
        printf("\n========================================");
        printf("\nVotre choix : ");
        choixMenu = getchar();
        fflush(stdin);

        char mot[60];

        switch (choixMenu) {
            case '1':
                printf("\nCreation nouvel arbre\n");
                break;
            case '2':
                printf("\n");
                if(choixArbre()-1)
                {
                    if(afficherArbre(arbre2, '!') == '!')
                        printf("L'arbre est vide");
                }
                else
                {
                    if(afficherArbre(arbre, '!') == '!')
                        printf("L'arbre est vide");
                }

                break;
            case '3':
                if(choixArbre()-1)
                {
                    printf("\nEntrez le mot a ajouter : ");
                    gets(mot);
                    fflush(stdin);
                    arbre2 = ajouterOccurrence(arbre2, mot);
                }
                else
                {
                    printf("\nEntrez le mot a ajouter : ");
                    gets(mot);
                    fflush(stdin);
                    arbre = ajouterOccurrence(arbre, mot);
                }

                break;
            case '4':
                if(choixArbre()-1)
                {
                    printf("\nEntrez le mot a supprimer : ");
                    gets(mot);
                    fflush(stdin);
                    arbre2 = supprimerOccurrence(arbre2, mot);
                }
                else
                {
                    printf("\nEntrez le mot a supprimer : ");
                    gets(mot);
                    fflush(stdin);
                    arbre = supprimerOccurrence(arbre, mot);
                }

                break;
            case '5':
                if(choixArbre()-1)
                {
                    if(estParfait(arbre2)) printf("\nL'arbre est parfait\n");
                    else printf("\nL'arbre n'est pas parfait\n");
                }
                else
                {
                    if(estParfait(arbre)) printf("\nL'arbre est parfait\n");
                    else printf("\nL'arbre n'est pas parfait\n");
                }

                break;
            case '6':
                if(choixArbre()-1)
                {
                    if(arbre2 == NULL)
                    {
                        printf("L'arbre est vide\n");
                        break;
                    }
                    if(estEquilibre(arbre2)) printf("\nL'abre est equilibre\n");
                    else printf("\nL'arbre n'est pas equilibre\n");
                }
                else
                {
                    if(arbre == NULL)
                    {
                        printf("L'arbre est vide\n");
                        break;
                    }
                    if(estEquilibre(arbre)) printf("\nL'abre est equilibre\n");
                    else printf("\nL'arbre n'est pas equilibre\n");
                }

                break;
            case '7': //test transformeListe()
                if(choixArbre()-1)
                {
                    lexique2 = transformeListe(lexique, arbre2);
                    afficherMots(lexique2);
                }
                else
                {
                    lexique = transformeListe(lexique, arbre);
                    afficherMots(lexique);
                }
                break;
            case '8':
                printf("\nL'indice de Jaccart est : %.3f", indiceJaccart(arbre, arbre2));
                break;
        //DEBUG
            case 'i':
                if(arbre != NULL) break;
                printf("initialisation arbre\n");
                arbre = ajouterOccurrence(arbre, "binaire");
                arbre = ajouterOccurrence(arbre, "arbre");
                arbre = ajouterOccurrence(arbre, "avion");
                arbre = ajouterOccurrence(arbre, "arme");
                arbre = ajouterOccurrence(arbre, "recherche");
                arbre = ajouterOccurrence(arbre, "bac");
                arbre = ajouterOccurrence(arbre, "travail");
                arbre = ajouterOccurrence(arbre, "piston");
                arbre = ajouterOccurrence(arbre, "acier");
                if(arbre2 != NULL) break;
                printf("initialisation arbre\n");
                arbre2 = ajouterOccurrence(arbre2, "binaire");
                arbre2 = ajouterOccurrence(arbre2, "arbre");
                arbre2 = ajouterOccurrence(arbre2, "avion");
                arbre2 = ajouterOccurrence(arbre2, "arme");
                arbre2 = ajouterOccurrence(arbre2, "recherche");
                arbre2 = ajouterOccurrence(arbre2, "bac");
                arbre2 = ajouterOccurrence(arbre2, "travail");
                arbre2 = ajouterOccurrence(arbre2, "piston");
                arbre2 = ajouterOccurrence(arbre2, "acier");
                break;
            case 'a':
                afficherDetails(arbre, arbre);
                break;
            default:
                break;
        }
    } while (choixMenu != '9');

    libererMemoire(arbre);
    libererMemoire(arbre2);
    freeLexique(lexique);
    freeLexique(lexique2);
    return 0;
}
