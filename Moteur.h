#ifndef H_MOTEUR
#define H_MOTEUR

class Moteur;

#include <fstream>

#include "Define.h"
#include "Jeu.h"
#include "Menu.h"
#include "Ia.h"

class Moteur
{
  private:
    Jeu *jeu;
    Menu *menu;
    IA *ia;		

    SDL_Surface *imgj1,*imgj2;
		
    bool dansMenu;
  public:
    /* Constructeur et Destructeur de la classe Moteur */
    Moteur();
    ~Moteur();

    /* Fonction qui gére le clic */
    void clic(int , int);
    /* Fonction qui gére l'affichage */
    void affichage(SDL_Surface *screen);
    /* Fonction d'initialisation */
    bool init();
    /* Fonction qui initialise le jeu et le remet à zéro */
    void initJeu();
    /* Fonction qui demande de passer en mode Jeu */
    void setFonctionsJeu();
    /* Fonction qui demande de passer en mode Menu */
    void setFonctionsMenu();
    /* Fonction qui change d'état de jeu */
    void echangeFonctions();
		
    void fin();

    /* Fonction qui mets à jour le type des joueurs */
    void misAJourTypeJoueurs();
    void verif();
};
#endif
