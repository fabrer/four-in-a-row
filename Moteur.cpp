#include "Moteur.h"

using namespace std;

Moteur::Moteur()
{
  /* Création du jeu et du menu */
  jeu = new Jeu();
  menu = new Menu();
  ia = new IA();
	
  dansMenu = true;
}

Moteur::~Moteur()
{
  delete jeu;
  delete menu;
}

bool Moteur::init()
{
  ifstream input;
  string s1,s2;

  /* Ouverture du fichier de paramétrage */
  input.open("data/input.txt");

  imgj1 = SDL_LoadBMP("data/imgj1.bmp");
  imgj2 = SDL_LoadBMP("data/imgj2.bmp");

  /* On récupère les noms des fichiers pour paramétrer le jeu et le menu */
  input >> s1 >> s2;
  return (jeu->init(s1) && (menu->init(s2)));
}

void Moteur::clic(int x, int y)
{
  /* Si on est dans le menu */
  if(dansMenu)
  {
    menu->clic(x,y);
  }
  else
  {	
    if(jeu->getFini())
      jeu->videJeu();
    else
      jeu->clic(x,y);
  }
}

void Moteur::affichage(SDL_Surface *screen)
{

  SDL_Rect z;
  z.x = 600;
  z.y = 200;
  /* Si on est dans le menu */
  if(dansMenu)
    menu->affichage(screen);
  else
  {
    jeu->affichage(screen);
    /* Afficher le tour en cour */
    if(jeu->getTour()==Rond)
      SDL_BlitSurface(imgj1,NULL,screen,&z);
    else
      SDL_BlitSurface(imgj2,NULL,screen,&z);
  }
}

void Moteur::initJeu()
{
  jeu->videJeu();
}

void Moteur::misAJourTypeJoueurs()
{
  jeu->setTypeJoueur(1,menu->getType(1));
  jeu->setTypeJoueur(2,menu->getType(2));
}


void Moteur::echangeFonctions()
{
  dansMenu = !dansMenu;
  misAJourTypeJoueurs();
}

void Moteur::setFonctionsJeu()
{
  dansMenu = false;
  misAJourTypeJoueurs();
}

void Moteur::setFonctionsMenu()
{
  dansMenu = true;
}

void Moteur::fin()
{
  SDL_Event ev;
  /* Le jeu est fini, on va émettre un événement SDL_QUIT */
  ev.type = SDL_QUIT;
  SDL_PushEvent(&ev);
}

void Moteur::verif()
{
  if(!dansMenu)
  {
    if(!jeu->getFini())
    {
      /* On vérifie si c'est un ordi le joueur courant */
      if(!jeu->estHumain())
      {
        switch(jeu->getTypeJoueur())
        {
          case Facile:
            ia->calcIA(jeu,3);
            break;
          case Moyen:
            ia->calcIA(jeu,7);
            break;
          case Difficile:
            ia->calcIA(jeu,9);
            break;
          default:
            break;
        }
      }
    }
  }
}
