//
// Created by Barnabé on 23/11/2021.
//

#ifndef TP4_ARBRE_H
#define TP4_ARBRE_H
#include "tp3.h"

typedef struct Noeud
{
    char *mot;
    int nombre_occurrences;
    struct Noeud *fils_droit;
    struct Noeud *fils_gauche;
} T_Noeud;
typedef T_Noeud* T_Arbre;

void afficherDetails(T_Arbre arbre, T_Arbre noeud);

T_Arbre creerNoeud(char*);
T_Arbre ajouterOccurrence(T_Arbre arbre, char* mot);
T_Arbre supprimerOccurrence(T_Arbre arbre, char* mot);
char afficherArbre(T_Arbre, char c);
int estParfait(T_Arbre arbre);
int estEquilibre(T_Arbre arbre);
t_mot* transformeListe(t_mot* liste, T_Arbre arbre);
float indiceJaccart(T_Arbre, T_Arbre);

T_Arbre successeur(T_Arbre, T_Arbre);
T_Arbre minimum(T_Arbre);
T_Arbre pere(T_Arbre, T_Arbre);
int hauteur(T_Arbre);
int maxInt(int, int);

void libererMemoire(T_Arbre);
void motMinuscule(char *mot);
#endif //TP4_ARBRE_H
