//
// Created by Barnabé on 23/11/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "arbre.h"
#include "tp3.h"

T_Arbre creerNoeud(char* mot)
{
    T_Noeud *noeud = malloc(sizeof(T_Noeud));
    if(noeud != NULL)
    {
        noeud->mot = strdup(mot);
        noeud->nombre_occurrences = 1;
        noeud->fils_droit = NULL;
        noeud->fils_gauche = NULL;
    } else printf("\nerreur allocation memoire\n");
    return noeud;
}

T_Arbre ajouterOccurrence(T_Arbre arbre, char* mot)
{
    if(mot == NULL) return arbre;
    motMinuscule(mot);
    if(arbre == NULL) return creerNoeud(mot);


    int cmpMot = strcmp(mot, arbre->mot);

    if(cmpMot == 0) arbre->nombre_occurrences++;

    else if(cmpMot == 1) arbre->fils_droit = ajouterOccurrence(arbre->fils_droit, mot);
    else if(cmpMot == -1) arbre->fils_gauche = ajouterOccurrence(arbre->fils_gauche, mot);

    return arbre;

    //version itérative
        /*
    T_Arbre pere = NULL, courant = arbre;
    int cmpMot = strcmp(mot, arbre->mot);
    int place = 0;
    while(!place)
    {
        if (cmpMot == 0) {
            courant->nombre_occurrences++;
            place = 1;
        }
        else if (cmpMot == 1) //le mot doit aller à droite
        {
            pere = courant;
            if(courant->fils_droit == NULL)
            {
                courant->fils_droit = creerNoeud(mot);
                place = 1;
            }
            else courant = courant->fils_droit;
        }
        else if (cmpMot == -1) //le mot doit aller à gauche
        {
            if(courant->fils_gauche == NULL)
            {
                courant->fils_gauche = creerNoeud(mot);
                place = 1;
            }
            else courant = courant->fils_gauche;
        }
        cmpMot = strcmp(mot, courant->mot);
    }
    return arbre;*/
}

T_Arbre supprimerOccurrence(T_Arbre arbre, char *mot)
{
    if(mot == NULL || arbre == NULL) return arbre;

    T_Arbre pereCourant = NULL, courant = arbre;

    motMinuscule(mot);

    int cmpMot;
    int fils = 0; //1 : courant est fils gauche de pere, 2 : courant est fils droit de pere
    while(courant != NULL) //boucle pour trouver le mot
    {
        cmpMot = strcmp(mot, courant->mot);
        if (cmpMot == 0)
        {
            break;
        }
        else if (cmpMot == 1) //on doit aller à droite
        {
            pereCourant = courant;
            fils = 2;
            courant = courant->fils_droit;
        }
        else if (cmpMot == -1) //on doit aller à gauche
        {
            pereCourant = courant;
            fils = 1;
            courant = courant->fils_gauche;
        }
    }

    if(courant == NULL) //si le mot n'existe pas dans l'arbre
    {
        printf("Le mot %s n'est pas contenu dans l'arbre", mot);
        return arbre;
    }

    if(courant->nombre_occurrences > 1) //si on doit juste enlever une occurence
    {
        courant->nombre_occurrences--;
        return arbre;
    }
    //sinon on va enlever le noeud

    if(courant->fils_gauche == NULL && courant->fils_droit == NULL) //si courant n'a pas de fils
    {
        if(pereCourant != NULL) {
            if (fils == 1) pereCourant->fils_gauche = NULL;


            else if (fils == 2) pereCourant->fils_droit = NULL;
        }

        if(arbre == courant)
        {
            libererMemoire(arbre);
            arbre = NULL;
        }
        else libererMemoire(courant);
        return arbre;
    }
    if(courant->fils_gauche == NULL || courant->fils_droit == NULL) //si courant n'a qu'un seul fils
    {
        if(courant->fils_gauche == NULL)
        {
            if(fils == 1) //1 : courant est fils gauche de pere, 2 : courant est fils droit de pere
            {
                pereCourant->fils_gauche = courant->fils_droit;
            } else if(fils == 2)
            {
                pereCourant->fils_droit = courant->fils_droit;
            }
        }
        else if(courant->fils_droit == NULL)
        {
            if(fils == 1)
            {
                pereCourant->fils_gauche = courant->fils_gauche;
            } else if(fils == 2)
            {
                pereCourant->fils_droit = courant->fils_gauche;
            }
        }
        return arbre;
    }

    //dernier cas si courant a deux fils
    T_Arbre succ = successeur(arbre, courant);

    //deux possibilités : soit succ est le fils droit de courant
    //                    soit succ est dans le sous arbre gauche du fils droit de courant ou au dessus dans l'arbre

    //si succ est fils droit de courant (dans ce cas la succ n'a pas de fils gauche)
    if(succ == courant->fils_droit)
    {
        if(fils == 1)
            pereCourant->fils_gauche = succ;
        else if (fils == 2)
            pereCourant->fils_droit = succ;
        else if(fils == 0) //le mot à supprimer est le premier dans l'arbre
            arbre = succ;
        succ->fils_gauche = courant->fils_gauche;
        courant->fils_gauche = NULL; //on met les fils à nul sinon ils seront supprimer dans libererMemoire()
        courant->fils_droit = NULL;
        libererMemoire(courant);
        return arbre;
    }
    //Sinon
    pere(arbre, succ)->fils_gauche = succ->fils_droit;//on peut optimiser

    if(fils == 1)
        pereCourant->fils_gauche = succ;
    else if (fils == 2)
        pereCourant->fils_droit = succ;
    else if(fils == 0) //le mot à supprimer est le premier dans l'arbre
        arbre = succ;

    succ->fils_gauche = courant->fils_gauche;
    succ->fils_droit = courant->fils_droit;
    courant->fils_gauche = NULL; //on met les fils à nul sinon ils seront supprimer dans libererMemoire()
    courant->fils_droit = NULL;
    libererMemoire(courant);
    return arbre;
}

char afficherArbre(T_Arbre arbre, char c)
{
    if(arbre == NULL) return c;

    c = afficherArbre(arbre->fils_gauche, c);
    if(c != arbre->mot[0])
    {
        c = arbre->mot[0];
        printf("%c --- %s [%d]\n", toupper(c), arbre->mot, arbre->nombre_occurrences);
    }
    else
        printf("  --- %s [%d]\n", arbre->mot, arbre->nombre_occurrences);
    c = afficherArbre(arbre->fils_droit, c);
    return c;
}
//fonction pour debug
void afficherDetails(T_Arbre racine, T_Arbre noeud)
{
    if(racine == NULL || noeud == NULL) return;

    printf("\n-----\n");
    printf("mot: %s\noccurence: %d\n", noeud->mot, noeud->nombre_occurrences);
    printf("fils gauche: %s\nfils droit: %s\n", noeud->fils_gauche ==NULL ? "null" : noeud->fils_gauche->mot, noeud->fils_droit ==NULL ? "null" : noeud->fils_droit->mot);
    printf("pere: %s\n", pere(racine, noeud) == NULL ? "null" : pere(racine, noeud)->mot);
    printf("successeur: %s\n",  successeur(racine, noeud) == NULL ? "null" : successeur(racine, noeud)->mot);

    afficherDetails(racine, noeud->fils_gauche);
    afficherDetails(racine, noeud->fils_droit);
}

int estParfaitSousArbre(T_Arbre arbre, int h)
{
    if(arbre == NULL && h >= 0) return 0;

    if(h == 0) return 1;

    return (estParfaitSousArbre(arbre->fils_gauche, h-1) && estParfaitSousArbre(arbre->fils_droit, h-1));
}


int estParfait(T_Arbre arbre)
{
    if(arbre == NULL){
        printf("\nL'arbre est vide.\n");
        return 0;
    }
    int h = hauteur(arbre);
    if(h == 0) return 1;

    return (estParfaitSousArbre(arbre->fils_gauche, h-1) && estParfaitSousArbre(arbre->fils_droit, h-1));
}

int estEquilibre(T_Arbre arbre)
{
    if(arbre == NULL) return 1;
    return abs(hauteur(arbre->fils_gauche) - hauteur(arbre->fils_droit)) <= 1 && estEquilibre(arbre->fils_gauche) && estEquilibre(arbre->fils_droit);
}

t_mot* transformeListe(t_mot* liste, T_Arbre arbre) //optimiser
{
    if(arbre == NULL) return liste;
    liste = transformeListe(liste, arbre->fils_gauche);
    liste = ajouterMot(liste, arbre->mot);
    liste = transformeListe(liste, arbre->fils_droit);
    return liste;
}

float indiceJaccart(T_Arbre arbre1, T_Arbre arbre2)
{
    t_mot * liste1 = NULL, *liste2 = NULL;
    liste1 = transformeListe(liste1, arbre1);
    liste2 = transformeListe(liste2, arbre2);

    int tailleUnion = 0;
    int tailleIntersec = 0;
    while(liste1 != NULL || liste2 != NULL)
    {
        if(liste1 != NULL && liste2 != NULL && !strcmp(liste1->mot, liste2->mot))
        {
            tailleIntersec++;
            tailleUnion--;
        }
        if(liste1 != NULL)
        {
            liste1 = liste1->suivant;
            tailleUnion += liste1->nombre_occurences;
        }
        if (liste2 != NULL)
        {
            liste2 = liste2->suivant;
            tailleUnion += liste2->nombre_occurences;
        }
    }

    return (float)tailleIntersec/ (float)tailleUnion;
}

T_Arbre rotation_gauche(T_Noeud *noeud)
{
    T_Noeud *y = noeud->fils_droit;

    if(y != NULL)
    {
        noeud->fils_droit = y->fils_gauche;
        y->fils_gauche = noeud;
    }
    return y;
}

T_Arbre rotation_droite(T_Noeud *noeud)
{
    T_Noeud *y = noeud->fils_gauche;
    if(y != NULL)
    {
        noeud->fils_gauche = y->fils_droit;
        y->fils_droit = noeud;
    }
    return y;
}

//autres fonctions



T_Arbre successeur(T_Arbre racine, T_Arbre noeud)
{
    if(noeud->fils_droit != NULL)
        return minimum(noeud->fils_droit);

    T_Arbre p = pere(racine, noeud);
    while(p != NULL && noeud == p->fils_droit)
    {
        noeud = p;
        p = pere(racine, noeud);
    }
    return p;
}

T_Arbre pere(T_Arbre racine, T_Arbre noeud)
{
    if(racine == noeud) return NULL;
    int cmpMot = strcmp(noeud->mot, racine->mot);
    T_Arbre pere = racine;
    while(cmpMot != 0) //boucle pour trouver le mot
    {
        pere = racine;

        if (cmpMot == 1) //le mot doit aller à droite
        {
            racine = racine->fils_droit;
        }
        else if (cmpMot == -1) //le mot doit aller à gauche
        {
            racine = racine->fils_gauche;
        }
        cmpMot = strcmp(noeud->mot, racine->mot);
    }
    return pere;
}

T_Arbre minimum(T_Arbre arbre)
{
    while(arbre->fils_gauche != NULL)
        arbre = arbre->fils_gauche;
    return  arbre;
}

int maxInt(int x, int y)
{
    return x > y ? x : y;
}
int hauteur(T_Arbre arbre)
{
    if(arbre == NULL) return -1;
    return maxInt(hauteur(arbre->fils_gauche), hauteur(arbre->fils_droit)) + 1;
}


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

void libererMemoire(T_Arbre arbre) //libere la mémoire d'un noeud et tous ses fils
{
    if(arbre != NULL)
    {
        libererMemoire(arbre->fils_droit);
        libererMemoire(arbre->fils_gauche);
        free(arbre->mot);
        free(arbre);
        arbre = NULL;
    }
}