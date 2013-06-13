#include "Objet.h"

Objet::Objet()
{
  int i;

  images.resize(5);
  for(i=0;i<5;i++)
    images[i] = NULL;
  curimage = 0;
  pos.x = 0;
  pos.y = 0;
  pos.w = 0;
  pos.h = 0;
}

Objet::~Objet()
{
}

void Objet::init()
{
  /* On met l'image à zéro et le type est Vide */
  curimage = 0;
  type = Vide;
}

void Objet::setPos(SDL_Rect *p)
{
  pos=*p;
}

void Objet::setImage(SDL_Surface *vide,SDL_Surface *o, SDL_Surface* x, SDL_Surface *gagneo, SDL_Surface *gagnex)
{
  images[0] = vide;
  images[1] = o;
  images[2] = x;
  images[3] = gagneo;
  images[4] = gagnex;
}

void Objet::affiche(SDL_Surface *dest)
{
  if(images[curimage])
    SDL_BlitSurface(images[curimage],NULL,dest,&pos);
}

bool Objet::estDedans(int x, int y)
{
  return ( (x>pos.x)&&(x<pos.x+pos.w)&&(y>pos.y)&&(y<pos.y+pos.h));
}

bool Objet::estVide()
{
  return type==Vide;
}


Case Objet::getType()
{
  return type;
}


void Objet::setType(Case t)
{
  switch(t)
  {
    /* Dans ces cas, on a directement le type et curimage */
    case Vide:
    case Rond:
    case Croix:
    type=t;
    curimage = t;
    break;
    /* Dans le cas Gagne, on met seulement à jour curimage */
    case Gagne:
      curimage = type+2;
    break;
  }
}

bool Objet::memeType(Objet &obj)
{
  return obj.type == type;
}
