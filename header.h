#include <allegro.h>
#include <winalleg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void intitialisation_rec(FILE* niveau_rec, char tab[15][19]);
void recherche_joueur(char valeurs[15][19], int* x, int*y);
void recherche_sortie_et_ennemis(char tab[15][19], int* xsortie, int* ysortie, int* tunnel, int* nb_ennemis);
int update_cases_glace(char tab[15][19]);
int update_cases_eau(char tab[15][19]);
void initialisation_console(char tab[15][19], char affiche_console[15][19], int score);
void affichage_score(int* score, int score_niveau);
void initialisation_niveau(FILE* fichier, char valeurs[15][19]);
void deplacement(char tab[15][19], int *clef,int score_general, int* score, int *precedent, char changement[50][2], int* emplacement, int* potion, char affiche[15][19], int niveau);
int TEST_DIE( char tab[15][19],int clef, int lvl, int *score, int precedent, int mode_graphique);
int afficher_mort(int* score, int niveau, int mode_graphique);
void update_tab_affiche(char tab[15][19], char affiche[15][19]);
void affichage(char changement[50][2], char affiche[15][19], int emplacement);
void getconsole_size();
