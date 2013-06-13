#ifndef H_MENU
#define H_MENU

class Menu;

#include "Define.h"
#include "Moteur.h"

class Menu
{
  private:
    /* Surfaces pour le menu */
    SDL_Surface *images[6];
	
    /* Position et taille des boutons */
    SDL_Rect jvj, jvcp1, jvcp2, jvcp3, quitter;

    /* Constructeur par copie */	
    Menu(const Menu&);            
    Menu& operator=(const Menu&); 
    /* Définition des types de joueur */
    int typej1, typej2;

  public:
    /* Constructeur et Destructeur de la classe Menu */
    Menu();
    ~Menu();

    /* Initialisation du Menu */
    bool init(const std::string &file);
	
    /* Gestion du clic dans le menu */
    void clic(int x, int y);
    /* Fonction d'affichage */
    void affichage(SDL_Surface *screen);
    
    int getType(int i);
};

#endif
