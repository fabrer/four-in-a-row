#include "Menu.h"

using namespace std;

/* Moteur du jeu */
extern Moteur moteur;

Menu::Menu()
{
  /* On initialise les images à NULL */
  int i;
  for(i=0;i<6;i++)
    images[i] = NULL;
}

Menu::~Menu()
{
  int i;
  /* On libere les espaces alloués aux images */
  for(i=0;i<6;i++)
  {
    SDL_FreeSurface(images[i]) , images[i] = NULL;
  }
}

bool Menu::init(const string &file)
{
  /* Ouverture du fichier de paramétrage */
  ifstream input(file.c_str());

  /* Test si le fichier s'est bien ouvert */
  if(input==NULL)
  {
    cerr << "Erreur dans l'ouverture du fichier " << file << endl;
    return false;
  }

  /* Récupération du nom de l'image pour le menu */
  string nom;

  /* On charge l'image de fond */
  input >> nom;
  images[0] = SDL_LoadBMP(nom.c_str());
	
  /* On récupère la surface de l'image "Joueur vs Joueur" */
  input >> nom;
  images[1] = SDL_LoadBMP(nom.c_str());
  input >> jvj.x >> jvj.y;
	
  /* Initialisation de la position du bouton "Joueur vs CPU1" */
  input >> nom;
  images[2] = SDL_LoadBMP(nom.c_str());
  input >> jvcp1.x >> jvcp1.y;

  /* On récupère la surface de l'image "Joueur vs CPU2" */
  input >> nom;
  images[3] = SDL_LoadBMP(nom.c_str());
  input >> jvcp2.x >> jvcp2.y;

  /* On récupère la surface de l'image "Joueur vs CPU3" */
  input >> nom;
  images[4] = SDL_LoadBMP(nom.c_str());
  input >> jvcp3.x >> jvcp3.y;

  /* On récupère la surface de l'image Quitter */
  input >> nom;
  images[5] = SDL_LoadBMP(nom.c_str());

  /* On teste le retour du chargement */
  int i;
  for(i=0;i<6;i++)
  if(images[i]==NULL)
  {
    cerr << "Probleme de chargement d'une des images du menu" << endl;
    return false;
  }
  /* Mise en place de la transparence */
  for(i=1;i<6;i++)
    SDL_SetColorKey(images[i],SDL_SRCCOLORKEY,255);

  /* Initialisation de la position du bouton quitter */
  input >> quitter.x >> quitter.y;
	
  /* On récupére la taille des images */
  jvj.w = images[1]->w;
  jvj.h = images[1]->h;
	
  jvcp1.w = images[2]->w;
  jvcp1.h = images[2]->h;

  jvcp2.w = images[3]->w;
  jvcp2.h = images[3]->h;

  jvcp3.w = images[4]->w;
  jvcp3.h = images[4]->h;

  quitter.w = images[5]->w;
  quitter.h = images[5]->h;

  /* On ferme le fichier ouvert en lecture */
  input.close();

  return true;
}

void Menu::clic(int x, int y)
{
  /* Est-ce qu'on est dans le bouton joueur vs joueur? */
  if((jvj.x<x)&&(jvj.x+jvj.w>x)&&(jvj.y<y)&&(jvj.y+jvj.h>y))
  {
    typej1=0;
    typej2=0;
    moteur.initJeu();
    moteur.setFonctionsJeu();
  }
  /* Est-ce qu'on est dans le bouton joueur vs CPU1? */
  else if((jvcp1.x<x)&&(jvcp1.x+jvcp1.w>x)&&(jvcp1.y<y)&&(jvcp1.y+jvcp1.h>y))
  {
    typej1=0;
    typej2=1;
    moteur.initJeu();
    moteur.setFonctionsJeu();
  }
  /* Est-ce qu'on est dans le bouton joueur vs CPU2? */
  else if((jvcp2.x<x)&&(jvcp2.x+jvcp2.w>x)&&(jvcp2.y<y)&&(jvcp2.y+jvcp2.h>y))
  {
    typej1=0;
    typej2=2;
    moteur.initJeu();
    moteur.setFonctionsJeu();
  }
  /* Est-ce qu'on est dans le bouton joueur vs CPU3? */
  else if((jvcp3.x<x)&&(jvcp3.x+jvcp3.w>x)&&(jvcp3.y<y)&&(jvcp3.y+jvcp3.h>y))
  {
    typej1=0;
    typej2=3;
    moteur.initJeu();
    moteur.setFonctionsJeu();
  }
  /* Est-ce qu'on est dans le bouton Quitter */
  else if((quitter.x<x)&&(quitter.x+quitter.w>x)&&(quitter.y<y)&&(quitter.y+quitter.h>y))
    moteur.fin();
}

void Menu::affichage(SDL_Surface *screen)
{
  /* Si on a une image, on l'affiche */
  if(images[0] && images[1] && images[2] && images[3] && images[4] && images[5])
  {
    SDL_BlitSurface(images[0],NULL,screen,NULL);
    SDL_BlitSurface(images[1],NULL,screen,&jvj);
    SDL_BlitSurface(images[2],NULL,screen,&jvcp1);
    SDL_BlitSurface(images[3],NULL,screen,&jvcp2);
    SDL_BlitSurface(images[4],NULL,screen,&jvcp3);
    SDL_BlitSurface(images[5],NULL,screen,&quitter);
  }
}

int Menu::getType(int i)
{
  if(i==1)
    return typej1;
  else
    return typej2;
}

