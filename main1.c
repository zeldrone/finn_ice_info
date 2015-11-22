#include<allegro.h>
#include <winalleg.h>

#include "header.h"
#include "header_allegro.h"

void gotoligcol( int lig, int col )
{
// ressources
COORD mycoord;
mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void mes_niveaux(int* score, int mode_graphique)
{
    FILE* nom_des_fichiers;
    FILE* fichier=NULL;
    int i,x=1;
    char mot[50];
    char chaine[50];
    nom_des_fichiers= fopen("noms_sauvegardes.txt", "r");
    fscanf(nom_des_fichiers, "%d", &i);
    while(x)
    {
    printf("quel est le nom du niveau?\n");
    scanf("%s", mot);
    if (strlen(mot)<44)
    {
        strcat(mot, ".txt");
        x=0;
    }
    else printf("ce nom est trop long\n");
    }
    x=1;
        while(i)
    {
        x=1;

        while(x)
        {
        fscanf(nom_des_fichiers, "%s", chaine);
        x=0;
            if(strcmp(mot , chaine));
            else
            {
                i=0;
                jeu_graphique(0, score, mode_graphique, mot );
            }
        }
        i--;
        }
        i;

    }


void fonction_scores (score)
{
    printf (" ");
}
void fonction_options (int* score, int* mode_graphique, int *mode_son)
{
    int choix;
    printf ("souhaitez-vous:\n1 activer le son\n2 paser en mode graphique\n3 passer en mode graphique et rejoindre le cote obscur de la force\n");
    scanf("%d", &choix );
    switch (choix)
    {
    case 1:
        *mode_son=1;
        break;
    case 2:
        *mode_graphique=1;
        break;
    case 3:
        *mode_graphique=2;
    }

}
void fonction_admin (int mode_graphique, int* score)
{
    char entre;
    char x=1;
    printf ("A quel niveau souhaitez-vous acceder?\n");
   while(x)
   {
    entre= getch();
     switch (entre)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        jeu_graphique(entre-1, score, mode_graphique, NULL);
        x=0;
        break;
    default:
        printf("ce n'est pas une entree valide!\nveuillez essayer a nouveau:");
    }
   }
}

int main()//Preparation du menu du PRJ01
{
    int x=0;
    int score=0, niveau=0;
    char imput [50];
    int mode_graphique=0, mode_son=0;
    FILE* fichier_score;
    fichier_score= fopen("scores.txt", "r+");

    while (x==0)//Infini au cas ou l'utilisateur n'ecrit pas qq chose de correct
    {
        printf("\t\t\t MENU \n");
            printf("\tmettez IMPERATIVEMENT la console en PLEIN ECRAN\n");
            printf ("\t    ecrivez sans fautes d'orthographe! \n");
            printf ("Ecrivez 'jouer' pour commencer a jouer ! \n");
            printf ("Ecrivez 'reprendre' pour reprendre votre partie sauvegardee ! \n");
            printf ("Ecrivez 'tutoriel' si vous jouez pour la premiere fois ! \n");
            printf ("Ecrivez 'options' pour modifier vos options ! \n");
            printf ("Ecrivez 'quitter' pour quitter le jeu !\n");

                scanf ("%s",imput);
                if (strcmp (imput,"jouer")==0)
                    {
                            if (mode_graphique!=0)
                            {
                            // si c'est le premier niveau joué

                                    // on initiallise allegro
                                    allegro_init();
                                    // on initialise le mode couleur
                                    set_color_depth(16);
                                    // on installe le clavier
                                    install_keyboard();
                                    // on démarre le mode graphique
                                    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 19*TSPRITE, 15*TSPRITE,0,0);

                            }
                            for(niveau=0; niveau<5; niveau++)
                            {
                                switch(jeu_graphique(niveau, &score, mode_graphique, NULL))
                                {
                                    case 1: niveau--;
                                    break;
                                    case 3: niveau=5;

                                    //si l'utilisateur rentre le bon trucs, appelle la fonction
                                    x++;
                                }
                            }
                            if (mode_graphique)
                            {
                                BITMAP* buffer;
                                buffer=create_bitmap(TSPRITE*19, TSPRITE*15);
                                clear_to_color(buffer);
                                if(menu_oui_non(buffer, "score"));
                                else
                                {
                                    textprintf_ex(buffer, font, 192-2*32, 160);

                                }


                            }

                    }
                else if (strcmp (imput,"reprendre")==0)
                    {
                    jeu_graphique(5, &score, mode_graphique, NULL);
                    x++;
                    }
                else if (strcmp (imput, "tutoriel")==0)
                    {
                        strcat(imput, ".txt");
                        jeu_graphique(0, &score, mode_graphique, imput);
                        system("cls");

                    }
                else if (strcmp (imput, "scores")==0)
                    {
                    fonction_scores;
                    x++;
                    }
                else if (strcmp (imput, "options")==0)
                    {
                    fonction_options(&score, &mode_graphique, &mode_son);
                    system("cls");
                    }
                else if (strcmp (imput, "quitter")==0)
                    {
                    return 0;
                    }
                else if (strcmp (imput, "admin")==0)
                    {
                    fonction_admin(mode_graphique, &score);
                    x++;
                    }
                else if(strcmp (imput, "editer")==0)
                    {
                       level_editor();
                    }
                else if(strcmp (imput, "niveaux")==0)
                {
                    mes_niveaux(&score, mode_graphique);
                }
                else
                {
                    printf ("Ce n'est pas un choix correct, veuillez recommencer\n");
                    Sleep(500);

                }
    }
    return 0;
} END_OF_MAIN();
