#ifndef H_JEU
#define H_JEU

#include <fstream>

#include "Define.h"
#include "Objet.h"

enum TypeJoueur 
{
  Humain, Facile, Moyen, Difficile
};

//Classe du jeu
class Jeu
{
  private: 
    /* On définit le plateau jeu */
    Objet plateau[6][7];
    /* Définition des surfaces d'un Jeton Rouge, Jeton Jaune et d'un fond. */
    SDL_Surface *o, *x, *bg, *gagneo, *gagnex, *vide;
    /* Variable pour un tour */
    Case tour, typegagne;
    /* Booléen pour savoir si la partie est terminée */
    bool fini;

    /* Fonction de test pour savoir si 4 pieces sont alignées, et le jeu est fini */
    void verifFini();

    /* Type Joueur humain / ordi */
    TypeJoueur j1, j2;

  public:
    /* Constructeur et Destructeur de la classe */
    Jeu();
    ~Jeu();
		
    /* Fonction d'initialisation (chargement des surfaces) */
    bool init(const std::string &file);
		
    /* Gestion du jeu lors d'un clic */
    void clic(int x, int y);
		
    /* Fonction d'affichage */
    void affichage(SDL_Surface *screen);

    /* Fonction pour vider le plateau de jeu */
    void videJeu();

    /* Fonction qui retourne la valeur de fini */
    bool getFini();

    /* Fonction qui retourne le joueur courant */
    Case getTour();

    /* Fonction qui retourne qui a gagné */
    Case getTypeGagne();

    /* Fonction qui retourne le type de la case */
    Case getCase(int i, int j);

    /* Fonction qui retourne si le joueur courant est un humain */
    bool estHumain();

    /* Fonction qui retourne le type du joueur courant */
    TypeJoueur getTypeJoueur();

    /* Fonction qui retourne l'état de la case */
    bool estVide(int i, int j);

    /* Fonction qui simule le coup, pour la case i,j */
    void simuleJoue(int i,int j);
    /* Fonction qui joue la case i,j et qui teste si le jeu est fini */
    void joue(int i,int j);

    /* Fonction qui annule le coup a;b */
    void annuleCoup(int a, int b);

    /* Fonction qui met en place le type des joueurs */
    void setTypeJoueur(int i, int type);
};
#endif
