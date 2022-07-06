#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tp3.h"


// Création nouvel élément
t_mot *creerMot(char *mot) {
    t_mot *nouveauMot = malloc(sizeof(t_mot));
    if(nouveauMot != NULL)
    {
        nouveauMot->nombre_occurences = 1;
        nouveauMot->mot = strdup(mot); // => faire un free() à la fin du programme
        nouveauMot->suivant = NULL;
    }
    return nouveauMot;
}
/* ====== FIN creerMot ====== */

// Ajout mot dans une liste
t_mot *ajouterMot(t_mot *liste, char *mot) {
    if(mot == NULL) return liste;

    motMinuscule(mot); //on met le mot en minuscule

    if(liste == NULL) return creerMot(mot);

    t_mot *precedent = NULL, *courant  = liste;

    int place = 0;
    while(courant != NULL) {
        int compMot = strcmp(mot, courant->mot);

        if (compMot == 0) //strcmp() retourne 0 si les deux chaines sont égales
        {
            courant->nombre_occurences++;
            place = 1;
            break;
        } else if (compMot == 1) //strcmp() retourne 1 si le 1er param est après le 2e dans l'ordre alphabétique
        {
            //printf("mot apres\n");
            precedent = courant;
            courant = courant->suivant;
        } else if (compMot == -1) //strcmp() retourne -1 si le 1er param est avant le 2e dans l'ordre alphabétique
        {
            t_mot *tmp = creerMot(mot);
            if(precedent != NULL) //si le mot ne devient pas le premier dans l'ordre alphabétique
            {
                precedent->suivant = tmp;
            }
            else
            {
                liste = tmp;
            }
            tmp->suivant = courant;
            place = 1;
            break;
        }
    }

    if(!place) //si le mot n'a pas été placé (dans le cas ou tous les mots sont avant dans l'ordre alphabétique de celui qu'on veut ajouter)
    {
        t_mot *tmp = creerMot(mot);
        precedent->suivant = tmp;
        tmp->suivant = courant; //ici courant devrait être égal à NULL
    }
    return liste;
}

/* ====== FIN ajouterMot====== */


// Retrait occurence mot d'une liste
t_mot *retirerMot(t_mot *liste, char *mot) {
    if(mot == NULL) return liste;
    if(liste == NULL) return NULL;

    t_mot *precedent = NULL, *courant  = liste;

    motMinuscule(mot); //on met le mot en minuscule


    int compMot = strcmp(mot, courant->mot);
    while(compMot != 0)
    {
        precedent = courant;
        courant = courant->suivant;
        if(courant == NULL) break;
        compMot = strcmp(mot, courant->mot);
    }
    if(compMot == 0)
    {
        if(courant->nombre_occurences > 1)
            courant->nombre_occurences--;
        else
        {
            if(precedent == NULL) //cas où le mot à retirer est le 1er dans la liste
            {
                liste = courant->suivant;
            }
            else
            {
                precedent->suivant = courant->suivant;
            }
            free(courant->mot);
            free(courant);
        }
    }
    else
    {
        printf("Le mot n'existe pas\n");
    }

    return liste;
}
/* ====== FIN retirerMot ====== */


// Affichage mots d'un lexique
void afficherMots(t_mot *liste){
    char c = '0';

    if(liste == NULL) printf("Il n'y a aucun mot dans ce lexique.\n");

    while(liste != NULL)
    {
        if(*(liste->mot) != c)
        {
            c = *(liste->mot);
            printf("%c --- %s [%d]\n", toupper(c), liste->mot, liste->nombre_occurences);
        }
        else
            printf("  --- %s [%d]\n", liste->mot, liste->nombre_occurences);
        liste = liste->suivant;
    }
}
/* ====== FIN afficherMots ====== */


// Fusion listes
t_mot *fusionner(t_mot *listeA, t_mot *listeB){

    t_mot *liste = NULL;
    t_mot *lA = listeA, *lB = listeB;

    while(lA != NULL)
    {
        for(int i=0; i<lA->nombre_occurences; i++)
        {
            liste = ajouterMot(liste, lA->mot);
        }
        lA = lA->suivant;
    }

    while(lB != NULL)
    {
        for(int i=0; i<lB->nombre_occurences; i++)
        {
            liste = ajouterMot(liste, lB->mot);
        }
        lB = lB->suivant;
    }

    freeLexique(listeA);
    freeLexique(listeB);

    return liste;
}
/* ====== FIN fusionner ====== */


// Import fichier de mots dans une liste
t_mot *importerFichier(t_mot *liste){
    char *filename = "texte.txt";
    FILE * fichier = fopen(filename, "r");
    if(fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
    }

    char mot[60];
    while(fgets(mot, 60, fichier))
    {
        motMinuscule(mot);
        mot[strcspn(mot, "\n")] = 0;
        liste = ajouterMot(liste, mot);
    }
    fclose(fichier);
    printf("Le fichier a bien ete charge\n");
    return liste;
}
/* ====== FIN importerFichier ====== */


//fonctio pour mettre un mot en minuscule (modifie le paramètre)
void motMinuscule(char* mot)
{
    for(int i=0; i< strlen(mot); i++)
    {
        if(mot[i] >= 'A' && mot[i] <= 'Z')
        {
            mot[i] = mot[i] - 'A' + 'a';
        }
    }
}


// fonction utile pour vider le tampon clavier
void viderBuffer() {
    int c = '0';
    while (c!='\n' && c != EOF) { c = getchar(); }
}

//fonction pour libérer l'espace mémoire d'un lexique
void freeLexique(t_mot* lexique)
{
    if(lexique != NULL)
    {
        t_mot *courant = lexique, *precedant = NULL;
        while(courant->suivant != NULL)
        {
            precedant = courant;
            courant = courant->suivant;
            free(precedant->mot);
            free(precedant);
        }
        free(courant->mot);
        free(courant);
    }
}