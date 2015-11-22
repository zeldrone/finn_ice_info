#include<allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>
#include "header.h"
#include "header_allegro.h"
#include <allegro.h>
#define LIGNE text_height(font)


int sauvegarde_niveau(int valeurs[15][19], char mot[50])
{
    int nb,i = 0,j = 0;
    FILE* noms_sauvegardes;
    FILE* sauvegarde;
    noms_sauvegardes= fopen("noms_sauvegardes.txt", "r+t");//ouvre le fichier pour stocker les noms des saves
    fscanf(noms_sauvegardes, "%d", &nb);//nbre de niveaux pre enregistres
    if (strlen(mot)<44)
    {
    strcat(mot, ".txt");//save dun fichier texte pour gerer le niveau creer 
    }
    else
    {
        allegro_message("Le nom est trop long!");
        return 1;
    }
    sauvegarde = fopen(mot, "w+");

    fseek(noms_sauvegardes, 0, SEEK_SET);// on change le nbre de niveau deja pre enregistre uniquement par le lvl editor
    fprintf(noms_sauvegardes, "%d ", ++nb);
    fseek(noms_sauvegardes, 0, SEEK_END);
    fprintf(noms_sauvegardes, " %s", mot);
    i=0;
    j=0;
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
                {
                    fprintf(sauvegarde, "%d ", valeurs[i][j]);// on creer le fichier correspondant au niveau qui vient detre creer 
                }
    }
    fclose(sauvegarde);
    fclose(noms_sauvegardes);
    return 0;
}
int conversion(int num, int *compteur)
{
    switch (num) // associe au tableau de valeurs les valeurs de la case vue a lecran quand on edite
    {
    case 0:
        num= 2;
        break;
    case 1:
        num= -2;
        break;
    case 2:
        num= -50;
        break;

    case 3:
        num= 100;
        break;
    case 4:
        num= 1;
        break;
    case 5:
        num= 66;
        break;
    case 6:
        num= -1;
        break;
    case 7:
        num= 0;
        break;
    case 8:
        num= 3;
        break;
    case 9:
        num= 5;
        break;
    case 10:
        num=4;
        break;
    case 11:
        num= 7;
        break;
    case 12:
        num=8;
        break;
    case 13:// teleporteur
        printf("%d", *compteur);
        num=101+((*compteur)%2)*10+(*compteur)-(*compteur)%2;)//gere que 1 fois sur 2, le tp vaut la valeur du tp precedent+10 
        (*compteur)++;
        break;
    default:
        num=-2;
    }
    return num;
}

int menu_oui_non(BITMAP* buffer, char* yolo)
{
    BITMAP* sauvegarde;
    BITMAP* ecran_noir;
    int compteur=0;
    ecran_noir= create_bitmap(192+5*32, 160);
    clear_to_color(ecran_noir, makecol(0, 0, 0));
    sauvegarde= create_bitmap(19*TSPRITE, 15*TSPRITE);
    textprintf_ex(ecran_noir, font, 0, 0, makecol(255, 255, 255),-1, "voulez-vous sauvegarder ce %s?", yolo);
    blit(ecran_noir, sauvegarde ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    textprintf_ex(ecran_noir, font, 0, LIGNE+7, makecol(255, 255, 255),-1, "-> oui        non");
    draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    rest(200);
    while(!key[KEY_ENTER])
    {
        if((key[KEY_LEFT])||(key[KEY_A]))
        {
            blit(sauvegarde, ecran_noir,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            textprintf_ex(ecran_noir, font, 0, LIGNE+7, makecol(255, 255, 255),-1, "-> oui        non");
            draw_sprite(buffer, ecran_noir, 192-2*32, 160);
            blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            compteur=0;
        }
        if((key[KEY_RIGHT]||key[KEY_D]))
        {
            blit(sauvegarde, ecran_noir,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            textprintf_ex(ecran_noir, font, 0, LIGNE+7, makecol(255, 255, 255),-1, "   oui     -> non");
            draw_sprite(buffer, ecran_noir, 192-2*32, 160);
            blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            compteur=1;
        }

    }
clear_keybuf();
return compteur;
}

void editeur_de_case(BITMAP* affiche[15][19], int valeurs[15][19]) //edite les cases: quand on clique change le motif de la case
{
    int compteur=0;
    int Case=0;
    int test=1,x=100,y=100;
    BITMAP* buffer;
    BITMAP* affiche2[NBSPRITE];
    init_mode_graphique(1, affiche2);// prend le tableau de beatmap affiche 2 et charge tourtes les images pour editer
    buffer= create_bitmap(TSPRITE*19, TSPRITE*15);// buffer qui fais la taille de lecran
    buffer= affiche_buffer(affiche);
    show_mouse(buffer);/:affiche la souris sur limage buffer
    blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);//on imprime tout ca sur lecran
    rest(500);
    while (test)
    {
        poll_mouse();//securite pour update les coordonnees de la souris
        show_mouse(buffer);//affiche la souris sur le buffer
        blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);//affiche le buffer tant que lon ne clique pas 

    if ((mouse_b & 1))//mouse_b = position de la souris, &1 = indique si jamais lutilisateur clique sur le bouton de gauche 
    {
        if (((int)(mouse_x-mouse_x%TSPRITE)/TSPRITE!=x)||((int)(mouse_y-mouse_y%TSPRITE)/TSPRITE!=y))// si on est sur une case qui nest pas la meme que la precedente 
        {
        Case=0;
        x= (int)(mouse_x-mouse_x%TSPRITE)/TSPRITE;//on met x et y aux valeurs de la case sur laquelle on vient de cliquer
        y=(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE;
        affiche[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]=affiche2[Case];// change la case sur laquelle on vient de cliquer a limage de la premiere case de affiche 2
        valeurs[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]= conversion(Case, &compteur);
        buffer= create_bitmap(TSPRITE*19, TSPRITE*15);
        buffer= affiche_buffer(affiche);
        show_mouse(buffer);
        blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);//copie le buffer
        rest(100);//car blit prend du temps avant de detruire le buffer
        destroy_bitmap(buffer);//detruit le buffer: on nettoie sa place memoire pour eviter des problemes
        }
        else//gere si jamais on a changer de case pour recommencer la boucle a zero pour eviter dafficher par ex une echelle sur la case, puis changer de case et que saffiche un tp (la valeur apres lechelle)
        {
            if (Case==13)
            {
                Case=-1;
                compteur--;
            }
        affiche[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]=affiche2[++Case];//incremente la case pour afficher pour afficher limage suivante
        valeurs[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]= conversion(Case, &compteur);//gere la valeur en dure de limage affichee par la ligne precedente
        buffer= create_bitmap(TSPRITE*19, TSPRITE*15);// creer emplacement memoire pour limage qui fais la taille de lecran
        buffer= affiche_buffer(affiche);
        show_mouse(buffer);
        blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
        rest(150);
        destroy_bitmap(buffer);
        }

    }
    if (key[KEY_ENTER])//si lutilisateur appuie sur entree
    {
        if (compteur%2==1)//si compteur est impair, affiche le pb pour les tp
        {
            allegro_message("Attention!\n les telporteurs sont lies 2 à 2! Il ne peut pas y en avoir un nombre impair !");
        }
        else test--;
    }

    if(mouse_b & 2)// 
    {
        if (Case==13) compteur--;//si la case quon quitte ets un tp, on decremente le compteur
        Case=7;//case de glace si clique droit
        x= (int)(mouse_x-mouse_x%TSPRITE)/TSPRITE;
        y=(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE;
        affiche[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]=affiche2[Case];
        valeurs[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]= conversion(Case, &compteur);
        buffer= create_bitmap(TSPRITE*19, TSPRITE*15);
        buffer= affiche_buffer(affiche);
        show_mouse(buffer);
        blit(buffer, screen ,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
        rest(100);
        destroy_bitmap(buffer);
    }
    }
    destroy_bitmap(buffer);
}
void worst_writing_ever(char mot[50], BITMAP* buffer, BITMAP* ecran_noir, int line, BITMAP* affiche[15][19]){

   int key_allegro;
   int memoire_char=0;//taille du mot jusqua maintenant 
   char key_ascii;
   char scancode;
   int i=0;
   draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    rest(200);
    while(!key[KEY_ENTER])
    {
        key_allegro=readkey();
        key_ascii= key_allegro & 0xff;//donne le charactere ascii de la touche qui a ete appuye
        scancode= key_allegro >> 8;

    if ((key_allegro==KEY_BACKSPACE)&&(i!=0))
    {
        i--;

    }
    if((key_ascii >= 32) && (key_ascii <= 126))//si ça fait partie de la table ascii
    {
        if (i<49)
        {
            mot[i]= key_ascii;//on prend la lettre dans le mot que l'utilisateur a ecrit, puis on laffiche 
            textprintf_ex(ecran_noir, font, memoire_char, line*LIGNE+5, makecol(255, 255, 255),-1, "%c", mot[i]);
            memoire_char+= text_length( font, "c");//on lui rajoute la largeur dun caractere, du coup la prochaine fois il saffichera 1 largeur de caractere plus loin
            destroy_bitmap(buffer);//detruit le buffer
            buffer=affiche_buffer(affiche);
            draw_sprite(buffer, ecran_noir, 192-2*32, 160);//on a recreer un buffer avec des murs partout on a remis le menu de ledito + le mot quon est e train decrire
            blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);//nous montre ce quon est en train de faire
            mot[i+1]='\0';//on sassure que la chaine sarrete
            i++;
        }
    }
    }
}

BITMAP* affiche_buffer(BITMAP* affiche[15][19])// elle prend un buffer et elle met des murs partout 
{
    BITMAP* buffer;
    buffer= create_bitmap(TSPRITE*19, TSPRITE*15);
    int i,j;

    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++){
                if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], TSPRITE*j, TSPRITE*i);
        }
    }

return buffer;
}
void level_editor()
{
    int i,j;
    BITMAP* buffer;
    BITMAP* ecran_noir;
    char mot[50];
    mot[0]='c';
    mot[1]='\0';
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(16);
    enable_hardware_cursor();//prend l'image du curseur de base
    BITMAP* affiche[15][19]={{load_bitmap("mur.bmp", NULL)}};//un foooooooond de murs
    ecran_noir= create_bitmap(192+5*32, 160);//crer un ecran noir
    clear_to_color(ecran_noir, makecol(255, 255, 0));
    buffer= create_bitmap(TSPRITE*19, TSPRITE*15);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, TSPRITE*19, TSPRITE*15, 0, 0)==0)
    {
    affiche[0][0]=load_bitmap("mur.bmp", NULL);
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++){
                affiche[i][j]=affiche[0][0];
                if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], TSPRITE*j, TSPRITE*i); //beatmap constitué de murs
        }
    }
    textprintf_ex(ecran_noir, font, 0, LIGNE, makecol(255,255,255),-1, "bienvenue sur l'editeur de niveau");
    draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);//Ici, on a une image rempli de murs, et par dessus une autre image avec le mess de bvn
    rest(1100);
    menu(buffer, affiche, mot);//fonction menue de l editeur
    destroy_bitmap(buffer);
    }
}
void menu(BITMAP* buffer, BITMAP* affiche[15][19], char mot[50]){//buffer=ecran noir afficher
    int x=1,i,j;
    BITMAP* ecran_noir;
    BITMAP* sauvegarde[15][19];
    BITMAP* ecran_selec;
    int valeurs[15][19];
    int line;
    ecran_noir= create_bitmap(192+5*32, 160);//on refait un ecran noir
    ecran_selec= create_bitmap(192+5*32, 160);
    clear_to_color(ecran_noir, makecol(0, 0, 0));//on colorie bien tout en noir
    textprintf_ex(ecran_noir, font, 0, LIGNE, makecol(255,255,255),-1, "Que souhaitez-vous faire?");
    textprintf_ex(ecran_noir, font, 0, 2*LIGNE+3, makecol(255,255,255),-1, "'dessin' pour commencer a dessiner");
    textprintf_ex(ecran_noir, font, 0, 3*LIGNE+3, makecol(255,255,255),-1, "'aide' pour voir l'aide au dessin!important!");
    blit(ecran_noir, ecran_selec, 0,0,0,0, 192+5*32, 160 );//on a ecrit sur lecran noir pour faire le menu
    line=4;//compteur de ligne
     affiche[0][0]=load_bitmap("mur.bmp", NULL);
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++){
                valeurs[i][j]=-2;//murs
                affiche[i][j]=affiche[0][0];//tout est initialise a murs, du coup lecran noir disparait
                if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], TSPRITE*j, TSPRITE*i);
        }
    }
     draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen,0,0,0,0, 21*TSPRITE, 15*TSPRITE);//on a notre fond avec des fonds et un ecran noir avec le menu
    while(x)
    {
    i=0;
    j=0;
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
            {

                sauvegarde[i][j]=affiche[i][j];//tableau de sauvegarde de affiche [i][j]
            }
    }
            worst_writing_ever(mot, buffer, ecran_noir, line, affiche);
            if (strcmp(mot, "dessin"))//compare le mot quon vient de rentrer a dessin et aide
            {
                if (strcmp(mot, "aide"))
                {
               allegro_message("Ce n'est pas une entree valide!");//pop up blindage
                }
                else// affiche laide pour editer
                {
                    clear_to_color(ecran_noir, makecol(0,0,0));
                    textprintf_ex(ecran_noir, font, 0, LIGNE+3, makecol(255,255,255),-1, "Afin de dessiner un niveau cliquez sur les cases.");
                    textprintf_ex(ecran_noir, font, 0, 2*(LIGNE+3), makecol(255,255,255),-1, "Un clic gauche fais afficher la possibilité suivante");
                    textprintf_ex(ecran_noir, font, 0, 3*(LIGNE+3), makecol(255,255,255),-1, "Un clic droit met une glace a l'emplacement indique");
                    textprintf_ex(ecran_noir, font, 0, 4*(LIGNE+3), makecol(255,255,255),-1, "Appuyez sur entrer quand vous avez termine");
                    textprintf_ex(ecran_noir, font, 0, 5*(LIGNE+3), makecol(255,255,255),-1, "Ce jeu n'est pas multijoueur ! Poser deux joueurs se soldera par un echec dans l'execution du niveau");
                    textprintf_ex(ecran_noir, font, 0, 6*(LIGNE+3), makecol(255,255,255),-1, "Les teleporteurs vont par paires et sont lies dans l'ordre dans lequel vous les implémentez !");
                    textprintf_ex(ecran_noir, font, 0, 7*(LIGNE+3), makecol(255,255,255),-1, "Une seule sortie ou tunnel!! Le tunnel eclipsera la sortie le cas echeant mais plusieurs d'entre eux conduiront a un echec");
                    textprintf_ex(ecran_noir, font, 0, 8*(LIGNE+3), makecol(255,255,255),-1, "Soyez creatifs!!!");
                }
            }
            else//fonction pour editer
            {
                editeur_de_case(affiche, valeurs);
                buffer=affiche_buffer(affiche);//nouveau tableau daffichage pour le snouvelles bonnes valeurs daffiche
                x=menu_oui_non(buffer, "dessin");//affiche niveau en fd decran et oui ou non pour save
                line++;
                if(x==0)//on save
                {
                    clear_to_color(ecran_noir, makecol(0,0,0));
                    textprintf_ex(ecran_noir, font, 0, 0, makecol(255,255,255),-1, "Entrez le nom de votre niveau");//sauvegarde du lvl
                    worst_writing_ever(mot, buffer, ecran_noir, 1, affiche);
                    if (sauvegarde_niveau(valeurs, mot));//si il a return 1, on repropose ce que lutilisateur veut faire
                    else
                    {
                        allegro_message("Niveau enregistre!");// si sauvegarde niveau return 0, le niveau est enregistre
                        x=0;
                    }
                }
                else// si lutilisateur a dit non pour save le niveau
                {

                        for (i=0; i<15; i++)
                            {
                                for(j=0; j<19; j++)
                                    {
                                        affiche[i][j]=sauvegarde[i][j];// affiche le dernier etat du niveau avant quil commence a dessiner
                                    }
                            }
                }
            }
            blit(ecran_selec, ecran_noir, 0,0,0,0, 192+5*32, 160 );// des que lon a fini, re affiche le menu avec possibilite de dessiner ou de daffichzer laide
        }
    }

