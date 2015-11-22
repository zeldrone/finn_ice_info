#include "header.h"
#include "header_allegro.h"
#include <winalleg.h>
void getconsole()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int colonnes, lignes;
    GetConsoleSceenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    conlonnes=csbi.srWindow.Right-bcsbi.srWindow.Left+1;
    lignes = csbi.srWindow.Bottom-csbi.srWindow.Top+1;
    If (colonnes>87) POS_ECRAN_X=colonnes/4;
    POS_ECRAN_Y = lignes/4;
}
void intitialisation_rec(FILE* niveau_rec, char tab[15][19])
{
    int i,j;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
           fscanf(niveau_rec, "%d", &tab[i][j]);
        }
    }
}
void recherche_joueur(char valeurs[15][19], int* x, int*y)
{
    int i,j;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (valeurs[i][j]==2)
            {
                *y=i;
                *x=j;
            }
        }
    }
}

void recherche_sortie_et_ennemis(char tab[15][19], int* xsortie, int* ysortie, int* tunnel, int* nb_ennemis)
{
    int i,j;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {

   		 if(tab[i][j]==3)
   			 {
   				 *ysortie=i;
   				 *xsortie=j;
   			 }
        if (tab[i][j]==7)
        {
            *ysortie=i;
            *xsortie=j;
            *tunnel=1;
        }
   			 if (tab[i][j]==66) (*nb_ennemis)++;
        }
    }
}
int update_cases_glace(char tab[15][19])
{
    int i,j;
    int val=0;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if((tab[i][j]>=0)||(tab[i][j]==-50)) val++;
        }
    }
    return val;
}

int update_cases_eau(char tab[15][19])
{
    int i,j;
    int val=0;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if((tab[i][j]==-1)||(tab[i][j]==2)) val++;
        }
    }
    return val;
}
void initialisation_console(char tab[15][19], char affiche_console[15][19], int score )
{
    int i,j;

     for(i=0; i<15; i++)
    {
        gotoligcol(POS_ECRAN_Y+i,POS_ECRAN_X);
        for(j=0; j<19; j++)
        {
            printf(" %c ", affiche_console[i][j]);
        }
        if (i==0) printf("score: %d", score);
        if (i==1) printf("score niveau: 0");
        printf("\n");
    }

}
void affichage_score(int* score, int score_niveau) //Affichage du score pendant la partie
{
    gotoligcol (POS_ECRAN_Y+0, POS_ECRAN_X+64);
    printf ("     ");
    gotoligcol (POS_ECRAN_Y+0, POS_ECRAN_X+64);
    printf ("%d",*score);
    gotoligcol (POS_ECRAN_Y+1,POS_ECRAN_X+70);
    printf ("     ");
    gotoligcol (POS_ECRAN_Y+1,POS_ECRAN_X+70);
    printf ("%d",score_niveau);
}
 void initialisation_niveau(FILE* fichier, char valeurs[15][19])
 {
     int i,j,k;
     int coorx_debut, coory_debut, coorx, coory;
     int cases_spe, val_spe, zones_glaces;
     fscanf(fichier,"%d",&zones_glaces);
        k=0;
    j=0;
   	 while( k<15)
            {
                j=0;
       while( j<19)
            {
                valeurs[k][j]=-2;
                j++;
            }
        k=k+1;
    }
    for(i=0;i<zones_glaces;i++)
    {
   	 fscanf(fichier,"%d",&coorx_debut);
   	 fscanf(fichier,"%d",&coory_debut);
   	 fscanf(fichier,"%d",&coorx);
   	 fscanf(fichier,"%d",&coory);


   	 j=0;
   	 k=0;
   	 while(abs(j)<abs(coorx))
   		 {
   		     k=0;
   		 while(abs(k)<abs(coory))
   			 {
   				 valeurs[coory_debut+k][coorx_debut+j]=0;
   				 k=k+abs(coory)/coory;
   			 }
   			 j=j+abs(coorx)/coorx;
   		 }
    }
    i=0;
     fscanf(fichier,"%d",&cases_spe);

        for(i=0; i<cases_spe; i++)
        {
            fscanf(fichier,"%d",&coorx);
            fscanf(fichier,"%d",&coory);
            fscanf(fichier,"%d",&val_spe);
                valeurs[coory][coorx]=val_spe;
        }
 }


void deplacement(char tab[15][19], int *clef,int score_general, int* score, int *precedent, char changement[50][2], int* emplacement, int* potion, char affiche[15][19], int niveau){
int i,j,x,y,z=1, test, direction;
char move;
//on repère la case avec le joueur
for(i=0; i<15; i++){
    for(j=0; j<19; j++)
    {
        if (tab[i][j]==2)
            {
            y=i;
            x=j;
            }
    }
}
int direction_x=0, direction_y=0;
char case_suivante_joueur;
char buffer=-1, buffer2;
//si l'utilisateur appuie sur une case
if (kbhit()){

        changement[*emplacement][0]=x;
        changement[*emplacement][1]=y;
        *emplacement= *emplacement +1;

        move=getch();
        switch (move){
            // modification en fonction de la direction choisie, incrément du score.
            case 's':
                    case_suivante_joueur=tab[y+1][x];
                    changement[*emplacement][0]=x;
                    changement[*emplacement][1]=y+1;
                    direction_y=1;
                    break;

            case 'z':
                case_suivante_joueur= tab[y-1][x];
                changement[*emplacement][0]=x;
                changement[*emplacement][1]=y-1;
                direction_y=-1;
                    break;

            case 'q':
                case_suivante_joueur= tab[y][x-1];
                changement[*emplacement][0]=x-1;
                changement[*emplacement][1]=y;
                direction_x=-1;
                break;

            case 'd':
                case_suivante_joueur= tab[y][x+1];
                changement[*emplacement][0]=x+1;
                changement[*emplacement][1]=y;
                direction_x=-1;
                    break;
            case '2':
                case_suivante_joueur= tab[y+1][x];
                changement[*emplacement][0]=x;
                changement[*emplacement][1]=y+1;
                direction_y=1;
                break;

            case '8':
                case_suivante_joueur= tab[y-1][x];
                changement[*emplacement][0]=x;
                changement[*emplacement][1]=y-1;
                direction_y=-1;
                break;

            case '4':
                case_suivante_joueur= tab[y][x-1];
                changement[*emplacement][0]=x-1;
                changement[*emplacement][1]=y;
                direction_x=-1;
                break;

            case '6':
                case_suivante_joueur=tab[y][x+1];
                changement[*emplacement][0]=x+1;
                changement[*emplacement][1]=y;
                direction_x=1;
                break;
            case 'x':
                fin_de_niveau(niveau);
                break;
            default :(*emplacement)--;
}
if (case_suivante_joueur>=0)
                        {
                            if(*potion>0)
                            {
                                z=0;
                                (*potion)--;
                            }
                //on décale le personage et diminue la glace derrière lui
                    i=case_suivante_joueur;
                    tab[changement[*emplacement][1]][changement[*emplacement][0]]=tab[y][x];
                    *precedent= *precedent-z;
                    (*score)+=z;
                    tab[y][x]=*precedent;
                    *precedent=i;
                    *emplacement= *emplacement +1;
                    // test de la présence d'une clef
                    if (*precedent== 100)
                    {
                    *clef= *clef+1;
                    *precedent=0;
                    }
                        }
                    if ((case_suivante_joueur==-50)&&(*clef>0))
                        {
                        (*clef)--;
                        tab[changement[*emplacement][1]][changement[*emplacement][0]]=tab[y][x];
                        tab[y][x]=*precedent-z;
                        (*score)+=1;
                        *precedent=0;
                        *emplacement= *emplacement +1;

                    }
    switch (*precedent)
    {
case 4:

        *potion= *potion+6;
        *precedent=0;
    break;
case 5:
            changement[*emplacement][0]=changement[*emplacement-1][0] ;
            changement[*emplacement][1]= changement[*emplacement-1][1];
            changement[*emplacement-1][0]+= direction_x;
            changement[*emplacement-1][1]+= direction_y;
        while(tab[changement[*emplacement-1][1]+direction_y][changement[*emplacement-1][0]+direction_x]>=0)
        {
            tab[changement[*emplacement-1][1]+direction_y][changement[*emplacement-1][0]+direction_x]=tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]];
            // on met de l'eau a la place du rocher
            tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]]=-1;
            gotoligcol(POS_ECRAN_Y+changement[*emplacement-1][1],POS_ECRAN_X+3*(changement[*emplacement-1][0]));
            update_tab_affiche(tab, affiche);
            printf(" %c", affiche[changement[*emplacement-1][1]][changement[*emplacement-1][0]]);
            changement[*emplacement-1][0]+= direction_x;
            changement[*emplacement-1][1]+= direction_y;


        }
        tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]]=-1;
        *precedent=0;
        (*emplacement)++;
        break;
case 8:

    changement[*emplacement][0]=changement[*emplacement-1][0] ;
            changement[*emplacement][1]= changement[*emplacement-1][1];
        while(tab[changement[*emplacement-1][1]+direction_y][changement[*emplacement-1][0]+direction_x]>=0)
        {
            buffer2=tab[changement[*emplacement-1][1]+direction_y][changement[*emplacement-1][0]+direction_x];
            tab[changement[*emplacement-1][1]+direction_y][changement[*emplacement-1][0]+direction_x]=tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]];
            tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]]=buffer;
            buffer=buffer2;
            gotoligcol(POS_ECRAN_Y+changement[*emplacement-1][1],POS_ECRAN_X+2*changement[*emplacement-1][0]);
            update_tab_affiche(tab, affiche);
            printf(" %c", affiche[changement[*emplacement-1][1]][changement[*emplacement-1][0]]);
            changement[*emplacement-1][0]+= direction_x;
            changement[*emplacement-1][1]+= direction_y;
            tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]]=2;

        }
        *precedent=0;
        (*emplacement)++;

    break;
    }
    if (*precedent>100)
        {
            i=0;
            j=0;
            for(i=0; i<15; i++)
            {
                for(j=0; j<19; j++)
                {

                    if (tab[i][j]==*precedent+10)
                    {
                        tab[i][j]=2;
                        tab[changement[*emplacement-1][1]][changement[*emplacement-1][0]]=-1;
                        changement[*emplacement][1]=i;
                        changement[*emplacement][0]=j;
                        (*emplacement)++;
                        *precedent=0;
                    }
                }
            }
        }

}
}
int TEST_DIE( char tab[15][19],int clef, int lvl, int *score, int precedent, int mode_graphique){
 int i,j,x, y, xs, ys;
//on repère la case avec le joueur
i=0;
j=0;
for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
            {
                if (tab[i][j]==2)
                    {
                        y=i;
                        x=j;

                    }

                    }
            }

//test de la condition de mort: entouré de cases a valeur négatives

if ((((tab[y+1][x]<0)&&(tab[y-1][x]<0)&&(tab[y][x+1]<0)&&(tab[y][x-1]<0)&&(clef==0))||(((tab[y+1][x]<0)&&(tab[y-1][x]<0)&&(tab[y][x+1]<0)&&(tab[y][x-1]<0))&&((tab[y+1][x]!=-50)&&((tab[y-1][x]!=-50)&&(tab[y][x+1]!=-50)&&(tab[y][x-1]!=-50))))||(precedent==66))){
switch(afficher_mort(score, lvl,  mode_graphique))
{
    case 1: return 1;
    case 3: return 3;
}

}
return 0;
}

int afficher_mort(int* score, int niveau, int mode_graphique)
{
    int j, i;
    if (mode_graphique)
    {

        BITMAP* buffer;
        buffer=create_bitmap(TSPRITE*19, TSPRITE*15);
        clear_to_color(buffer, makecol(0,0,0));
        textprintf_ex(buffer, font, TSPRITE*9, TSPRITE*7, makecol(255,255,255),-1,"Vous avez perdu! Votre score est de %d", *score );
        textprintf_ex(buffer, font, TSPRITE*9, TSPRITE*7+LIGNE+3,makecol(255,255,255),-1,"Voulez-vous:");
        textprintf_ex(buffer, font, TSPRITE*9, TSPRITE*7+2*(LIGNE+3), makecol(255,255,255),-1,"1 quitter");
        textprintf_ex(buffer, font, TSPRITE*9, TSPRITE*7+3*(LIGNE+3), makecol(255,255,255),-1,"ou");
        textprintf_ex(buffer, font, TSPRITE*9, TSPRITE*7+4*(LIGNE+3), makecol(255,255,255),-1,"2 recommencer le niveau?");
        blit(buffer, screen, 0,0,0,0,TSPRITE*19, TSPRITE*15);

        while (j)
        {
            if(!key[KEY_1])
            {
                if(!key[KEY_2]);
                else
                {
                    return 1;
                }

            }
            else
            {
                textprintf_ex(buffer, font, TSPRITE*9, TSPRITE*7+5*(LIGNE+3),makecol(255,255,255),-1,"Au revoir!");
                blit(buffer, screen, 0,0,0,0,TSPRITE*19, TSPRITE*15);
                rest(500);
                return 3;
            }
        }

    }
    else
    {gotoligcol(5, 0);
printf("\t\t Vous avez perdu! Votre score est de %d\n", *score);
Sleep(300);
j=1;
while(j){
printf("Voulez-vous:\n1 quitter\n ou\n2 recommencer le niveau?\n");
scanf("%d", &i);
if (i==1){
printf("Au revoir!\n");
sleep(200);
j=0;
exit(0);
}
if(i==2) {

        jeu_graphique(niveau, score, mode_graphique, NULL);
        j=0;
}
}
}
}

void update_tab_affiche(char tab[15][19], char affiche[15][19]){
// declaration des variables
int i,j;
// boucle sur tout le tableau
for(i=0; i<15; i++){
    for(j=0; j<19; j++){
            //affectation de la valeur du caractère dans le tableau d'affichage
        switch (tab[i][j]){
    case -2: affiche[i][j]= 225-18;
    break;
         //les murs
    case 1://glace double
        affiche[i][j]= 127;
        break;
    case 0: affiche[i][j]=225-2;
    break;// la glace
    case -1: affiche[i][j]= 226-49;
    break;//l'eau
    case -50: affiche[i][j]= 225-19;
    break;//les serrures
    case 100: affiche[i][j]= 225-28;
    break;//les clés
    case 2:affiche[i][j]= 225-17;
    break; //le personnage
    case 3: affiche[i][j]=225-16;
            //la sortie
    break;
    case 66: // l'ennemi
        affiche[i][j]= 245;
        break;
    case 4: affiche[i][j]= 244;
    // la potion
    break;
    case 5: affiche[i][j]= 246;
    // le rocher
        break;
        case 7: affiche[i][j]= 'O';
        break;
        case 8: affiche[i][j]=175;
        break;

        }
        if (tab[i][j]>100) affiche[i][j]= 203;
        }

    }
}

void affichage(char changement[50][2], char affiche[15][19], int emplacement){
int i;
//on repère la case avec le joueur

for(i=0; i<emplacement; i++){
gotoligcol(POS_ECRAN_Y+changement[i][1],POS_ECRAN_X+3*changement[i][0]+1);
printf("%c", affiche[changement[i][1]][changement[i][0]]);

}
}

