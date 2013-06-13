#ifndef H_OBJET
#define H_OBJET

#include <vector>
#include "Define.h"

//Type d'une case
enum Case 
{
  Vide=0, Rond, Croix, Gagne
};

class Objet
{
  private:
    /* Les surfaces des cases */
    std::vector<SDL_Surface *> images;
    /* L'image à afficher */
    int curimage;
    /* Type de la case */
    Case type;
    /* Position de la case */
    SDL_Rect pos;

  public:
    /* Constructeur et Destructeur de la classe Objet */
    Objet();
    ~Objet();

    /* Fonction d'initialisation et remise à zéro */
    void init();

    /* Mise en place de la case */
    void setPos(SDL_Rect *p);
    /* Récupération de la position */
    SDL_Rect *getPos();

    /* Mise en place des images */
    void setImage(SDL_Surface *, SDL_Surface *, SDL_Surface *, SDL_Surface *, SDL_Surface *);

    /* Fonction d'affichage */
    void affiche(SDL_Surface *dest);
    /* La position (x,y) est dans la case? */
    bool estDedans(int x, int y);

    /* Est-ce l'objet obj est du même type? */
    bool memeType(Objet &obj);

    /* On récupère le type de l'objet */
    Case getType();

    /* Mise en place du type */
    void setType(Case t);

    /* Est-ce que la case est vide? */
    bool estVide();
};
#endif
