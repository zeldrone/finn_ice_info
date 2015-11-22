#include <allegro.h>
#include <winalleg.h>
#include "header_allegro.h"
#include "header.h"
void fin_de_niveau(int niveau)
{
    FILE* sauvegarde;
    sauvegarde= fopen("niveausauvegarde.txt", "w");
    fprintf(sauvegarde, "%d", niveau);
    exit(0);
}
int deplacement_graphique(char tab[15][19], int* score, int* clef, int precedent, int* potion, BITMAP* affiche[15][19], BITMAP* affiche2[NBSPRITE], int mode_graphique, int score_general, int niveau)
{

    clear_keybuf();
    int i,j,x,y;
    int z=1;
    int direction_x=0, direction_y=0;
    int test=1, buffer=0, buffer1=-1, buffer2;
    int coord_case_suiv[2]={0};
        for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (tab[i][j]==2)
            {
                x=j;
                y=i;
            }
        }
    }
i=0;
j=0;
    if(!key[KEY_W])
    {
        if(!key[KEY_S])
        {
            if(!key[KEY_A]) //allegro gère le clavier en qwerty
            {
                if(!key[KEY_D])
                {
                    if(!key[KEY_X]) test=0;
                    else fin_de_niveau(niveau);
                }
                else
                {
                    coord_case_suiv[0]=x+1;
                    coord_case_suiv[1]=y;
                    direction_x=1;
                }
            }
            else
            {
                coord_case_suiv[0]=x-1;
                coord_case_suiv[1]=y;
                direction_x=-1;
            }
        }
        else
        {
            coord_case_suiv[0]=x;
            coord_case_suiv[1]=y+1;
            direction_y=1;
        }
    }
    else
    {
        coord_case_suiv[0]=x;
        coord_case_suiv[1]=y-1;
        direction_y=-1;
    }
    if (test)
    {
        if(*potion>0)
        {
            *potion=*potion-1;
            z=0;
        }
        if (tab[coord_case_suiv[1]][coord_case_suiv[0]]>=0)
        {
            buffer=tab[coord_case_suiv[1]][coord_case_suiv[0]];
            tab[coord_case_suiv[1]][coord_case_suiv[0]]=tab[y][x];
            tab[y][x]=precedent-z;
            (*score)+=z;
        }
        if (buffer==100)
        {
            (*clef)++;
            return 0;
        }
        if((tab[coord_case_suiv[1]][coord_case_suiv[0]]==-50)&&(*clef>0))
        {
            (*clef)--;
            tab[coord_case_suiv[1]][coord_case_suiv[0]]=tab[y][x];
            tab[y][x]=precedent-z;
            (*score)+=z;
            return 0;
        }
        switch (buffer)
        {

    case 4:
        *potion= *potion+6;
        return 0;
    break;
    case 5:
            coord_case_suiv[0]+= direction_x;
            coord_case_suiv[1]+= direction_y;
        while(tab[coord_case_suiv[1]+direction_y][coord_case_suiv[0]+direction_x]>=0)
        {
            tab[coord_case_suiv[1]+direction_y][coord_case_suiv[0]+direction_x]=tab[coord_case_suiv[1]][coord_case_suiv[0]];
            // on met de l'eau a la place du rocher
            tab[coord_case_suiv[1]][coord_case_suiv[0]]=-1;
            coord_case_suiv[0]+= direction_x;
            coord_case_suiv[1]+= direction_y;
            update_affichage_graphique(tab, affiche, affiche2, mode_graphique);
            affichage_graphique(affiche, mode_graphique, score_general, *score, affiche2, tab);
            tab[coord_case_suiv[1]][coord_case_suiv[0]]=5;
            rest(50);
        }
        tab[coord_case_suiv[1]][coord_case_suiv[0]]=-1;
        return 0;
    break;

    case 8:
                while(tab[coord_case_suiv[1]+direction_y][coord_case_suiv[0]+direction_x]>=0)
        {
            buffer2=tab[coord_case_suiv[1]+direction_y][coord_case_suiv[0]+direction_x];
            tab[coord_case_suiv[1]+direction_y][coord_case_suiv[0]+direction_x]=tab[coord_case_suiv[1]][coord_case_suiv[0]];
            // on met de l'eau a la place du rocher
            tab[coord_case_suiv[1]][coord_case_suiv[0]]=buffer1;
            buffer1=buffer2;
            coord_case_suiv[0]+= direction_x;
            coord_case_suiv[1]+= direction_y;
            update_affichage_graphique(tab, affiche, affiche2, mode_graphique);
            affichage_graphique(affiche, mode_graphique, score_general, *score, affiche2, tab);
            tab[coord_case_suiv[1]][coord_case_suiv[0]]=2;
            rest(50);
        }
        return 0;
        break;

        }
        if (buffer>100)
        {
    i=0;
    j=0;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {

                if (tab[i][j]==buffer+10)
                {
                    tab[i][j]=2;
                    tab[coord_case_suiv[1]][coord_case_suiv[0]]=-1;
                    return 0;
                }
        }
    }
        }
    return buffer;
    }
    else return precedent;
}

void affichage_graphique(BITMAP* affiche[15][19], int mode_graphique, int score, int score_niveau, BITMAP* affiche2[NBSPRITE], char tab[15][19])
{
    int i,j,k,l;
    BITMAP* buffer;
    BITMAP* fond;
    int compteur=0;

    buffer= create_bitmap(19*TSPRITE, 15*TSPRITE);
    if (mode_graphique==2)
    {
        fond=load_bitmap("fond_star_wars.bmp", NULL);
        draw_sprite(buffer, fond,0,0);
    }

    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], j*TSPRITE, i*TSPRITE);
        }
    }
    textprintf_ex(buffer, font, 15*TSPRITE, TSPRITE-13, makecol(255, 0,0),-1, "score: %d", score);
    textprintf_ex(buffer, font, 15*TSPRITE, TSPRITE+3, makecol(255, 0,0),-1, "score niveau: %d", score_niveau);
    blit(buffer, screen, 0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    destroy_bitmap(buffer);
}

void init_mode_graphique(int mode_graphique,BITMAP* affiche2[NBSPRITE])
{
    int i;
    i=0;
    switch(mode_graphique)
    {
    case 1:
        affiche2[0]=load_bitmap("pingouin.bmp", NULL);
        // le personnage
        affiche2[1]=load_bitmap("mur.bmp", NULL);
        // les murs
        affiche2[2]=load_bitmap("serrure.bmp", NULL);
        // les serrures
        affiche2[3]=load_bitmap("clef.bmp", NULL);
        // les clef
        affiche2[4]=load_bitmap("glace_double.bmp", NULL);
        // la glace double
        affiche2[5]=load_bitmap("ghost.bmp", NULL);
        // les ennemis
        affiche2[6]=load_bitmap("eau.bmp", NULL);
        // l'eau
        affiche2[7]=load_bitmap("glace.bmp", NULL);
        // la glace
        affiche2[8]=load_bitmap("sortie.bmp", NULL);
        // la porte de sortie
        affiche2[9]=load_bitmap("rocher1.bmp", NULL);
        // les rochers
        affiche2[10]=load_bitmap("potion.bmp", NULL);
        // les potions
        affiche2[11]=load_bitmap("tunnel1.bmp", NULL);
        // les tunnels
        affiche2[12]=load_bitmap("turbo.bmp", NULL);

        affiche2[13]=load_bitmap("teleport.bmp", NULL);
        affiche2[14]=load_bitmap("teleport2.bmp", NULL);
        affiche2[15]=load_bitmap("teleport3.bmp", NULL);
        affiche2[16]=load_bitmap("teleport4.bmp", NULL);


        break;
    case 2:
        affiche2[0]=load_bitmap("Darth-Vader.bmp", NULL);
        affiche2[1]=NULL;
        affiche2[2]=load_bitmap("master_yoda.bmp", NULL);
        affiche2[3]=load_bitmap("sabre_laser18.bmp", NULL);
        affiche2[4]=load_bitmap("star_wars_double.bmp", NULL);
        affiche2[5]=load_bitmap("X-wing.bmp", NULL);
        affiche2[6]=load_bitmap("Space.bmp", NULL);
        affiche2[7]=load_bitmap("star_wars_floor.bmp", NULL);
        affiche2[8]=load_bitmap("Death_Star.bmp", NULL);
        //affiche2[9]=load_bitmap(".bmp", NULL);
        //affiche2[10]=load_bitmap(".bmp", NULL);*/
        //affiche2[11]=load_bitamp(".bmp", NULL);
        break;
    }
}

void update_affichage_graphique(char tab[15][19], BITMAP* affiche[15][19], BITMAP* affiche2[NBSPRITE], int mode_graphique)
{
    int i,j, k,l;
    int teleport=0;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            switch (tab[i][j])
            {
            case -2: // les murs

                affiche[i][j]=affiche2[1];
                break;
            case -1: // l'eau
                affiche[i][j]=affiche2[6];
                break;
            case 0: // la glace
                affiche[i][j]=affiche2[7];
                break;
            case 1: // la glace double
                affiche[i][j]=affiche2[4];
                break;
            case 2: // le personnage
                affiche[i][j]=affiche2[0];
                break;
            case 3: // la sortie
                affiche[i][j]=affiche2[8];
                break;
            case 4: // les potions
                affiche[i][j]=affiche2[10];
                break;
            case 5: // les rochers
                affiche[i][j]=affiche2[9];
                break;
            case 100: // les clef
                affiche[i][j]=affiche2[3];
                break;
            case -50: // les serrures
                affiche[i][j]=affiche2[2];
                break;
            case 66:
                affiche[i][j]=affiche2[5];
                // les ennemis
                break;
            case 7: affiche[i][j]= affiche2[11];
            // les tunnels
            break;
            case 8: affiche[i][j]= affiche2[12];
            break;

            }
            if (tab[i][j]>100)
            {
                for(k=0; k<15; k++)
                {
                    for(l=0; l<19; l++)
                    {
                        if ((tab[k][l]==tab[i][j]+10)&&(teleport<4))
                        {
                            affiche[k][l]=affiche2[13+teleport];
                            affiche[i][j]=affiche2[13+teleport];
                            teleport++;
                        }


                    }
                }
            }
        }
    }
}

void init_move_ennemis(char tab[15][19], int nb_ennemis, int coord_ennemis[nb_ennemis][2], FILE* ennemis[nb_ennemis], int niveau, int compteurs_ennemis[nb_ennemis], int compteur_max[nb_ennemis], int precedent_ennemi[nb_ennemis])
 {
     int i,j, a=0;
    char nom[30];
    for(i=0; i<nb_ennemis; i++)
    {
        sprintf(nom, "ennemi.niveau%d.%d.txt", niveau, i);
        ennemis[i]=fopen(nom, "r");
        compteurs_ennemis[i]=1;
        precedent_ennemi[i]=0;
        fscanf(ennemis[i], "%d", &compteur_max[i]);
    }
    i=0;
    for(i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (tab[i][j]==66)
            {
                coord_ennemis[a][0]=j;
                coord_ennemis[a][1]=i;
                a++;
            }
        }
    }
}

int move_ennemis(FILE* ennemis, char tab[15][19], int precedent_ennemi, int coord[2], int compteur, char changement[50][2], int* emplacement )
{
    int move;
    int direction_x=0, direction_y=0;
    if(ennemis!=NULL)
    {
    fseek(ennemis, 2*compteur, SEEK_SET);
    fscanf(ennemis, "%d", &move);
    }
    switch(move)
    {
    case 1:
        direction_x=1;
        break;
    case 2:
        direction_x=-1;
        break;
    case 3:
        direction_y=1;
        break;
    case 4:
        direction_y=-1;
        break;
    }
    move= tab[coord[1]+direction_y][coord[0]+direction_x];

    tab[coord[1]+direction_y][coord[0]+direction_x]= tab[coord[1]][coord[0]];
    tab[coord[1]][coord[0]]= precedent_ennemi;
    changement[*emplacement][0]=coord[0];
    changement[(*emplacement)++][1]=coord[1];
    coord[1]+= direction_y;
    coord[0]+=direction_x;
    changement[*emplacement][0]=coord[0];
    changement[(*emplacement)++][1]=coord[1];
    return move;
}
int jeu_graphique(int niveau, int* score, int mode_graphique, char mot[50])
{
    // si le mode est graphique


    BITMAP* affiche[15][19];
    BITMAP* affiche2[NBSPRITE]={NULL};

    FILE *niveau_rec;
    FILE *fichier[6]= {NULL};

    fichier[0] = fopen("niveau1.txt","r");
    fichier[1] = fopen("niveau2.txt","r");
    fichier[2] = fopen("niveau3.txt","r");
    fichier[3] = fopen("niveau4.txt","r");
    fichier[4] = fopen("niveau5.txt","r");
    fichier[5] = fopen("niveausauvegarde.txt","r");

    int precedent=0;
    int i,j;
    int x,y;
    char valeurs[15][19];
    int xsortie,ysortie;
    int score_niveau=0;
    int cle=0, potion=0;
    int nb_ennemis=0,nb_cases_glace=0, nb_cases_eau;
    char affiche_console[15][19];
    char changement[50][2];
    int emplacement=0;
    int tunnel=0;
    int boucle=1;
        if (niveau==5)
    {
        fscanf(fichier[5],"%d", &i);
        niveau=i;
    }

    i=0;
    system("cls");

    if (fichier[niveau]!=NULL) initialisation_niveau(fichier[niveau], valeurs);

    if ((mot!= NULL)&&(strcmp(mot, "tutoriel")))
    {

        niveau_rec= fopen(mot, "r");
        intitialisation_rec(niveau_rec, valeurs);
    }
     if (mot!=NULL)
    {
        if (strcmp(mot, "tutoriel.txt")==0)
        {
            fichier[niveau]= fopen(mot, "r");
            if (fichier[niveau]!=NULL)initialisation_niveau(fichier[niveau], valeurs);

        }
    }
    if (mode_graphique!=0)
    {
    init_mode_graphique(mode_graphique, affiche2);

    update_affichage_graphique(valeurs, affiche, affiche2, mode_graphique);

    }
    else
    {
        update_tab_affiche(valeurs, affiche_console);
        initialisation_console(valeurs, affiche_console, *score);
    }
    if (mot!=NULL)
    {
        if (strcmp(mot, "tutoriel.txt")==0)
        {
            if (mode_graphique==0)
            {
            gotoligcol(POS_ECRAN_Y+16, POS_ECRAN_X);
            }
        printf ("\tRegles :\n");
                    printf ("1) Le but du jeu est d'atteindre la sortie. \n");
                    printf ("2) Utilisez les touches 2,4,6,8 du pavé ou les touches z,q,s,d pour vous deplacer. \n");
                    printf ("3) Lorsque vous passez sur un bloc de glace, il disparait et laisse place a de l'eau. \n");
                    printf ("4) Vous ne pouvez pas passer sur de l'eau, donc si vous vous entourez d'eau, vous perdez \n");
                    printf ("5) Certains niveaux contiennent des doubles glaces : lorsque vous passez dessus, ils deviennent des blocs de glace simple. \n");
                    printf ("6) Certains niveaux contiennent des bonus utilisables ! \n");
                    printf ("7) Comme par exemple une potion de legerete, pour passer sans casser la glace. \n");
                    printf ("8) Les potions %c vous permettent de passer sans détruire la glace pendant 6 mouvements! \n", 244);
                    printf ("10) Certains niveaux contiennent des serrures ! \n");
                    printf ("11) Une cle sera disponible dans le niveau pour ouvrir la serrure et terminer le niveau. \n");
                    printf ("9) Les rochers %c sont mobiles et détruisent tout sur leur passage, attention aux clef! \n");
                    printf ("12) S'amuser !\n");

        }
    }



    recherche_sortie_et_ennemis(valeurs, &xsortie, &ysortie, &tunnel, &nb_ennemis);
    recherche_joueur(valeurs, &x, &y);
    nb_cases_glace= update_cases_glace(valeurs);
    i=0;
    int coord_ennemis[nb_ennemis][2];
    FILE* ennemis[nb_ennemis];
    int compteurs_ennemis[nb_ennemis];
    int compteur_max[nb_ennemis];
    int precedent_ennemi[nb_ennemis];
    int compteur=0;
    init_move_ennemis(valeurs, nb_ennemis, coord_ennemis, ennemis, niveau, compteurs_ennemis, compteur_max, precedent_ennemi);
    while(boucle)
    {
            while(((x!=xsortie)||(y!=ysortie))||(nb_cases_eau!=nb_cases_glace))
            {
                getconsole_size();
                emplacement=0;
                i=0;
                nb_cases_eau=0;
                if (mode_graphique!=0)
                {
                    precedent=deplacement_graphique(valeurs, &score_niveau, &cle, precedent, &potion, affiche, affiche2, mode_graphique, *score, niveau);
                }
                else
                {
                    deplacement(valeurs, &cle,*score, &score_niveau, &precedent, changement, &emplacement, &potion, affiche_console, niveau);
                }
                if (compteur==5)
                {

                    for(i=0; i<nb_ennemis; i++)
                    {
                        precedent_ennemi[i]=move_ennemis(ennemis[i], valeurs, precedent_ennemi[i], coord_ennemis[i], compteurs_ennemis[i], changement, &emplacement);

                        if (compteurs_ennemis[i]>=compteur_max[i]) compteurs_ennemis[i]=1;
                        else compteurs_ennemis[i]++;
                        if (precedent_ennemi[i]==2)
                        {
                            if (mode_graphique)
                            {
                                update_affichage_graphique(valeurs, affiche, affiche2, mode_graphique);
                                affichage_graphique(affiche, mode_graphique, *score, score_niveau, affiche2, valeurs);
                            }
                            else
                            {
                                update_tab_affiche(valeurs, affiche_console);
                                affichage(changement, affiche_console, emplacement);
                            }
                            switch(afficher_mort(score, niveau, mode_graphique))
                            {
                                case 1:return 1;
                                case 3: return 3;
                            }
                        }
                    }
                    compteur=0;
                }
                if (mode_graphique!=0)
                {

                    update_affichage_graphique(valeurs, affiche, affiche2, mode_graphique);
                    affichage_graphique(affiche, mode_graphique, *score, score_niveau, affiche2, valeurs);
                }
                else
                {
                    update_tab_affiche(valeurs, affiche_console);
                    affichage(changement, affiche_console, emplacement);
                    affichage_score(score, score_niveau);
                }

                nb_cases_eau= update_cases_eau(valeurs);
                recherche_joueur(valeurs, &x, &y);
                if((x!=xsortie)||(y!=ysortie))
                {
                    switch (TEST_DIE(valeurs, cle, niveau, score, precedent, mode_graphique))
                    {
                        case 1: return 1;
                        case 3: return 3;

                    }
        }
        if ((x==xsortie)&&(y==ysortie)&&(nb_cases_eau!=nb_cases_glace))
        {
            system("cls");
           printf("\n\nVous avez oublie %d cases!", nb_cases_glace-nb_cases_eau);
           Sleep(1000);
            afficher_mort(score, niveau, mode_graphique);

        }
        compteur++;
        Sleep(80);

    }
    if(tunnel)
    {
        tunnel=0;
        initialisation_niveau(fichier[niveau], valeurs);
         precedent=0;
        if(mode_graphique==0)
        {
           gotoligcol(POS_ECRAN_Y,POS_ECRAN_X);

            update_tab_affiche(valeurs, affiche_console);
            initialisation_console(valeurs, affiche_console, *score);
        }
        nb_cases_glace= update_cases_glace(valeurs);
        nb_cases_eau= 0;
        recherche_sortie_et_ennemis(valeurs, &xsortie, &ysortie, &tunnel, &nb_ennemis);
        recherche_joueur(valeurs, &x, &y);
    }
    else
    {
        boucle=0;
    }
    }

    (*score)+=score_niveau;
    return 0;
}
