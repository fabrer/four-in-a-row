#include "Main.h"
#include "Moteur.h"

Moteur moteur;

using namespace std;

int main(int argc, char **argv)
{
  SDL_Event event;
  SDL_Surface *screen;
  int done = 0;

  string s = "data/input_Jeu.txt";
  ifstream in(s.c_str());
  if(!in)
  {
    cerr << "Fail"<<endl;
    return 1;
  }

  /* On initialise le jeu */
  if(SDL_Init(SDL_INIT_VIDEO)!=0) 
  {
    cout << "Probleme pour initialiser SDL: " << SDL_GetError() << endl;
    return 1;
  }

  /* On met un titre à la fenetre */
  SDL_WM_SetCaption("Puissance4 - MinMax", NULL);

  /* On ouvre une fenetre */
  screen = SDL_SetVideoMode(WIDTH,HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
  if(screen==NULL)
    done = 1;

  /* On initialise le moteur de jeu */
  if(!moteur.init())
    return 1;

  while(!done)
  {
    /* Gestion des evenements */
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          done=1;
          break;
        case SDL_KEYUP:
          /* Si l'on relache la touche Q, alors le jeu se ferme */
          if(event.key.keysym.sym==SDLK_q)
            moteur.fin();
          /* Si l'on relache la touche ECHAP, alors le jeu bascule sur le menu ou le jeu */
          else if(event.key.keysym.sym==SDLK_ESCAPE)
            moteur.echangeFonctions();
          /* Si l'on relache la touche R, alors le jeu redemarre */
          else if(event.key.keysym.sym==SDLK_r)
          {
            moteur.initJeu();
            moteur.setFonctionsJeu();
          }
          break;
        case SDL_MOUSEBUTTONUP:
          moteur.clic(event.button.x, event.button.y);
          break;
        default:
        break;
      }
    }
    moteur.affichage(screen);
    moteur.verif();
    SDL_Flip(screen);
  }
  SDL_Quit();
  (void) argc;
  (void) argv;
  return 0;
}
