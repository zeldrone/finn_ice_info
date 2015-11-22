#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NBSPRITE 18

void update_tab_affiche(char tab[15][19], char affiche[15][19]);
void update_affichage_graphique(char tab[15][19], BITMAP* affiche[15][19], BITMAP* affiche2[11], int mode_graphique);
void affichage_graphique(BITMAP* affiche[15][19], int mode_graphique, int score, int score_niveau, BITMAP* affiche2[NBSPRITE], char tab[15][19]);
int deplacement_graphique(char tab[15][19], int* score, int* clef, int precedent, int* potion, BITMAP* affiche[15][19], BITMAP* affiche2[11], int mode_graphique, int score_general, int niveau);
int jeu_graphique(int niveau, int* score, int mode_graphique, char mot[50]);
BITMAP* affiche_buffer(BITMAP* affiche[15][19]);
void init_mode_graphique(int mode_graphique,BITMAP* affiche2[11]);
void level_editor();
void menu(BITMAP* buffer, BITMAP* affiche[15][19], char mot[50]);
