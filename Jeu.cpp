#include "Jeu.h"

using namespace std;

Jeu::Jeu()
{
  /* On vide le plateau de jeu */
  videJeu();
    
  /* On met les valeurs des images à NULL */
  vide=NULL;
  o=NULL;
  x=NULL;
  bg=NULL;
  gagneo=NULL;
  gagnex=NULL;
}

Jeu::~Jeu()
{
  /* On libére les surfaces avec la fonction SDL */
  SDL_FreeSurface(o);
  SDL_FreeSurface(bg);
  SDL_FreeSurface(x);
  SDL_FreeSurface(gagneo);
  SDL_FreeSurface(gagnex);	
}

bool Jeu::init(const string &file)
{
  /* On crée un rectangle SDL */
  SDL_Rect r;
  int i,j;
  string s;

  /* On ouvre le fichier de paramétrage 
     On passe par un fichier de paramétrage, de facon à pouvoir modifier 
     le design, sans devoir recompiler */
  
  ifstream inputfile(file.c_str());

  /* On gère les erreurs retournées par l'ouverture du fichier */
  if(inputfile==NULL)
  {
    cerr << "Erreur dans l'ouverture de " << file << "." <<endl;
    return false;
  }

  /* Vérification de l'allocation des surfaces */
  if(vide!=NULL)
  {
    SDL_FreeSurface(vide), vide = NULL;
  }
  if(o!=NULL)
  {
    SDL_FreeSurface(o), o = NULL;
  }
  if(x!=NULL)
  {
    SDL_FreeSurface(x), x = NULL;
  }
  if(bg!=NULL)
  {
    SDL_FreeSurface(bg), bg = NULL;
  }
  if(gagneo!=NULL)
  {
    SDL_FreeSurface(gagneo), gagneo = NULL;
  }
  if(gagnex!=NULL)
  {
    SDL_FreeSurface(gagnex), gagnex = NULL;
  }

  /* On charge toutes les images dans les surfaces associées */
  inputfile >> s;
  bg = SDL_LoadBMP(s.c_str());
  inputfile >> s;
  vide = SDL_LoadBMP(s.c_str());
  inputfile >> s;
  o = SDL_LoadBMP(s.c_str());
  inputfile >> s;
  x = SDL_LoadBMP(s.c_str());
  inputfile >> s;
  gagneo = SDL_LoadBMP(s.c_str());
  inputfile >> s;
  gagnex = SDL_LoadBMP(s.c_str());


  /* On teste le retour du chargement */
  if( (vide==NULL) || (o==NULL) || (x==NULL) || (bg==NULL) || (gagnex==NULL) || (gagneo==NULL) )
  {
    cerr << "Probleme de chargement du Jeton Rouge, du Jeton Jaune ou de l'image de fond" << endl;
    return false;
  }

  /* On initialise le premier tour, avec le jeton Rouge qui commence */
  tour = Rond;

  /* Mis en place de la transparence */
  if(SDL_SetAlpha(vide,SDL_SRCALPHA,255)==-1)
    cerr << "Erreur avec la transparence de la case vide" << endl; 
  if(SDL_SetColorKey(o,SDL_SRCCOLORKEY,0)==-1)
    cerr << "Erreur avec la transparence du Jeton Rouge" << endl;
  if(SDL_SetColorKey(x,SDL_SRCCOLORKEY,0)==-1)
    cerr << "Erreur avec la transparence du Jeton Jaune" << endl;
  if(SDL_SetColorKey(gagneo,SDL_SRCCOLORKEY,0)==-1)
    cerr << "Erreur avec la transparence" << endl;
  if(SDL_SetColorKey(gagnex,SDL_SRCCOLORKEY,0)==-1)
    cerr << "Erreur avec la transparence" << endl;

  /* Mise en place de la largeur et l'hauteur d'une case */
  inputfile >> r.w >> r.h;

  /* Mise en place des surfaces des cases */
  for(i=0;i<6;i++)
    for(j=0;j<7;j++)
    {
      inputfile >> r.x >> r.y;
      /* On initialise les positions de chaque case */
      plateau[i][j].setPos(&r);
      /* On initialise les images de chaque case */
      plateau[i][j].setImage(vide,o,x,gagneo,gagnex);
    }
  return true;
}


void Jeu::videJeu()
{
  int i,j;

  /* On vide le plateau */
  for(i=0;i<6;i++)
    for(j=0;j<7;j++)	
      plateau[i][j].init();
	    
  /* On remet le jeton du joueur de départ à Jeton Rouge */
  tour = Rond;
    
  fini = false;
}


void Jeu::clic(int x, int y)
{
  int i,j;
  bool trouve=false;

  if(!fini)
  {
    /* On parcourt tout le plateau pour trouver la case associée */
    for(i=0;(i<6)&&(!trouve);i++)
      for(j=0;(j<7)&&(!trouve);j++)
      {
        /* Si le clic a touché cette colonne */
        if(plateau[i][j].estDedans(x,y))
        {
          /* Si la case la plus basse est vide on met le type de la case a jours
             Et on passe au joueur suivant */
          if((plateau[5][j].estVide()))
          {
            plateau[5][j].setType(tour);
            tour = (tour==Rond)?Croix:Rond;
          }
          else if((plateau[4][j].estVide()))
          {
            plateau[4][j].setType(tour);
            tour = (tour==Rond)?Croix:Rond;
          }
          else if( (plateau[3][j].estVide()) )
          {
            plateau[3][j].setType(tour);
            tour = (tour==Rond)?Croix:Rond;
          }
          else if( (plateau[2][j].estVide()) )
          {
            plateau[2][j].setType(tour);
            tour = (tour==Rond)?Croix:Rond;
          }
          else if( (plateau[1][j].estVide()) )
          {
            plateau[1][j].setType(tour);
            tour = (tour==Rond)?Croix:Rond;
          }
          else if( (plateau[0][j].estVide()) )
          {
            plateau[0][j].setType(tour);
            tour = (tour==Rond)?Croix:Rond;
          }
          /* On dit qu'on a trouvé la case associé */
          trouve = true;
        }
      }
  }

  /* Si le clic a touché une case, il faudra vérifier si la partie est terminée */
  if(trouve)
    verifFini();
}


void Jeu::affichage(SDL_Surface *screen)
{
  int k,l;

  /* Dessine le fond d'ecran */
  SDL_BlitSurface(bg,NULL,screen,NULL);

  /* Dessiner chaque case */
  for(k=0;k<6;k++)
    for(l=0;l<7;l++)
    {
      plateau[k][l].affiche(screen);
    }
}


bool Jeu::getFini()
{
  return fini;
}

void Jeu::verifFini()
{
  bool casevide = false;

  /* Test des regles sur les lignes */
  for(int i=0;i<6;i++)
  {
    if( !plateau[i][0].estVide() || !plateau[i][1].estVide() || !plateau[i][2].estVide() || !plateau[i][3].estVide() || !plateau[i][4].estVide() || !plateau[i][5].estVide())
    {
      if( (!plateau[i][0].estVide()) && ( plateau[i][0].memeType(plateau[i][1]) ) && ( plateau[i][0].memeType(plateau[i][2]) ) && ( plateau[i][0].memeType(plateau[i][3]) ) ) 
      {
        fini = true;
        typegagne = plateau[i][0].getType();
        plateau[i][0].setType(Gagne);
        plateau[i][1].setType(Gagne);
        plateau[i][2].setType(Gagne);
        plateau[i][3].setType(Gagne);
      }
      else if( (!plateau[i][1].estVide()) && ( plateau[i][1].memeType(plateau[i][2]) ) && ( plateau[i][1].memeType(plateau[i][3]) ) && ( plateau[i][1].memeType(plateau[i][4]) ) ) 
      {
        fini = true;
        typegagne = plateau[i][1].getType();
        plateau[i][1].setType(Gagne);
        plateau[i][2].setType(Gagne);
        plateau[i][3].setType(Gagne);
        plateau[i][4].setType(Gagne);
      }
      else if( (!plateau[i][2].estVide()) && ( plateau[i][2].memeType(plateau[i][3]) ) && ( plateau[i][2].memeType(plateau[i][4]) ) && ( plateau[i][2].memeType(plateau[i][5]) ) ) 
      {
        fini = true;
        typegagne = plateau[i][2].getType();
        plateau[i][2].setType(Gagne);
        plateau[i][3].setType(Gagne);
        plateau[i][4].setType(Gagne);
        plateau[i][5].setType(Gagne);
      }
      else if( (!plateau[i][3].estVide()) && ( plateau[i][3].memeType(plateau[i][4]) ) && ( plateau[i][3].memeType(plateau[i][5]) ) && ( plateau[i][3].memeType(plateau[i][6]) ) ) 
      {
        fini = true;
        typegagne = plateau[i][3].getType();
        plateau[i][3].setType(Gagne);
        plateau[i][4].setType(Gagne);
        plateau[i][5].setType(Gagne);
        plateau[i][6].setType(Gagne);
      }
    }
    else
    {
      casevide = true;
    }
  }

  /* Test des regles sur les colonnes */
  for(int j=0;j<7;j++)
  {
    if( !plateau[0][j].estVide() || !plateau[1][j].estVide() || !plateau[2][j].estVide() || !plateau[3][j].estVide() || !plateau[4][j].estVide() || !plateau[5][j].estVide() )
    {
      if( (!plateau[0][j].estVide()) && ( plateau[0][j].memeType(plateau[1][j]) ) && ( plateau[0][j].memeType(plateau[2][j]) ) && ( plateau[0][j].memeType(plateau[3][j]) ) ) 
      {
        fini = true;
        typegagne = plateau[0][j].getType();
        plateau[0][j].setType(Gagne);
        plateau[1][j].setType(Gagne);
        plateau[2][j].setType(Gagne);
        plateau[3][j].setType(Gagne);
      }
      else if( (!plateau[1][j].estVide()) && ( plateau[1][j].memeType(plateau[2][j]) ) && ( plateau[1][j].memeType(plateau[3][j]) ) && ( plateau[1][j].memeType(plateau[4][j]) ) ) 
      {
        fini = true;
        typegagne = plateau[1][j].getType();
        plateau[1][j].setType(Gagne);
        plateau[2][j].setType(Gagne);
        plateau[3][j].setType(Gagne);
        plateau[4][j].setType(Gagne);
      }
      else if( (!plateau[2][j].estVide()) && ( plateau[2][j].memeType(plateau[3][j]) ) && ( plateau[2][j].memeType(plateau[4][j]) ) && ( plateau[2][j].memeType(plateau[5][j]) ) ) 
      {
        fini = true;
        typegagne = plateau[2][j].getType();
        plateau[2][j].setType(Gagne);
        plateau[3][j].setType(Gagne);
        plateau[4][j].setType(Gagne);
        plateau[5][j].setType(Gagne);
      }
    }
    else
    {
      casevide = true;
    }
  }

  /* Test sur les diagonales */
  if( !plateau[5][0].estVide() || !plateau[5][1].estVide() || !plateau[5][2].estVide() || !plateau[5][3].estVide() || !plateau[5][4].estVide() || !plateau[5][5].estVide() || plateau[5][6].estVide() )
  {
    if( (!plateau[0][3].estVide()) && ( plateau[0][3].memeType(plateau[1][4]) ) && ( plateau[0][3].memeType(plateau[2][5]) ) && ( plateau[0][3].memeType(plateau[3][6]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][3].getType();
      plateau[0][3].setType(Gagne);
      plateau[1][4].setType(Gagne);
      plateau[2][5].setType(Gagne);
      plateau[3][6].setType(Gagne);
    }
    else if( (!plateau[0][2].estVide()) && ( plateau[0][2].memeType(plateau[1][3]) ) && ( plateau[0][2].memeType(plateau[2][4]) ) && ( plateau[0][2].memeType(plateau[3][5]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][2].getType();
      plateau[0][2].setType(Gagne);
      plateau[1][3].setType(Gagne);
      plateau[2][4].setType(Gagne);
      plateau[3][5].setType(Gagne);
    }
    else if( (!plateau[1][3].estVide()) && ( plateau[1][3].memeType(plateau[2][4]) ) && ( plateau[1][3].memeType(plateau[3][5]) ) && ( plateau[1][3].memeType(plateau[4][6]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][3].getType();
      plateau[1][3].setType(Gagne);
      plateau[2][4].setType(Gagne);
      plateau[3][5].setType(Gagne);
      plateau[4][6].setType(Gagne);
    }
    else if( (!plateau[0][1].estVide()) && ( plateau[0][1].memeType(plateau[1][2]) ) && ( plateau[0][1].memeType(plateau[2][3]) ) && ( plateau[0][1].memeType(plateau[3][4]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][1].getType();
      plateau[0][1].setType(Gagne);
      plateau[1][2].setType(Gagne);
      plateau[2][3].setType(Gagne);
      plateau[3][4].setType(Gagne);
    }
    else if( (!plateau[1][2].estVide()) && ( plateau[1][2].memeType(plateau[2][3]) ) && ( plateau[1][2].memeType(plateau[3][4]) ) && ( plateau[1][2].memeType(plateau[4][5]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][2].getType();
      plateau[1][2].setType(Gagne);
      plateau[2][3].setType(Gagne);
      plateau[3][4].setType(Gagne);
      plateau[4][5].setType(Gagne);
    }
    else if( (!plateau[2][3].estVide()) && ( plateau[2][3].memeType(plateau[3][4]) ) && ( plateau[2][3].memeType(plateau[4][5]) ) && ( plateau[2][3].memeType(plateau[5][6]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][3].getType();
      plateau[2][3].setType(Gagne);
      plateau[3][4].setType(Gagne);
      plateau[4][5].setType(Gagne);
      plateau[5][6].setType(Gagne);
    }
    else if( (!plateau[0][0].estVide()) && ( plateau[0][0].memeType(plateau[1][1]) ) && ( plateau[0][0].memeType(plateau[2][2]) ) && ( plateau[0][0].memeType(plateau[3][3]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][0].getType();
      plateau[0][0].setType(Gagne);
      plateau[1][1].setType(Gagne);
      plateau[2][2].setType(Gagne);
      plateau[3][3].setType(Gagne);
    }
    else if( (!plateau[1][1].estVide()) && ( plateau[1][1].memeType(plateau[2][2]) ) && ( plateau[1][1].memeType(plateau[3][3]) ) && ( plateau[1][1].memeType(plateau[4][4]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][1].getType();
      plateau[1][1].setType(Gagne);
      plateau[2][2].setType(Gagne);
      plateau[3][3].setType(Gagne);
      plateau[4][4].setType(Gagne);
    }
    else if( (!plateau[2][2].estVide()) && ( plateau[2][2].memeType(plateau[3][3]) ) && ( plateau[2][2].memeType(plateau[4][4]) ) && ( plateau[2][2].memeType(plateau[5][5]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][2].getType();
      plateau[2][2].setType(Gagne);
      plateau[3][3].setType(Gagne);
      plateau[4][4].setType(Gagne);
      plateau[5][5].setType(Gagne);
    }
    else if( (!plateau[1][0].estVide()) && ( plateau[1][0].memeType(plateau[2][1]) ) && ( plateau[1][0].memeType(plateau[3][2]) ) && ( plateau[1][0].memeType(plateau[4][3]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][0].getType();
      plateau[1][0].setType(Gagne);
      plateau[2][1].setType(Gagne);
      plateau[3][2].setType(Gagne);
      plateau[4][3].setType(Gagne);
    }
    else if( (!plateau[2][1].estVide()) && ( plateau[2][1].memeType(plateau[3][2]) ) && ( plateau[2][1].memeType(plateau[4][3]) ) && ( plateau[2][1].memeType(plateau[5][4]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][1].getType();
      plateau[2][1].setType(Gagne);
      plateau[3][2].setType(Gagne);
      plateau[4][3].setType(Gagne);
      plateau[5][4].setType(Gagne);
    }
    else if( (!plateau[2][0].estVide()) && ( plateau[2][0].memeType(plateau[3][1]) ) && ( plateau[2][0].memeType(plateau[4][2]) ) && ( plateau[2][0].memeType(plateau[5][3]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][0].getType();
      plateau[2][0].setType(Gagne);
      plateau[3][1].setType(Gagne);
      plateau[4][2].setType(Gagne);
      plateau[5][3].setType(Gagne);
    }
    else if( (!plateau[0][3].estVide()) && ( plateau[0][3].memeType(plateau[1][2]) ) && ( plateau[0][3].memeType(plateau[2][1]) ) && ( plateau[0][3].memeType(plateau[3][0]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][3].getType();
      plateau[0][3].setType(Gagne);
      plateau[1][2].setType(Gagne);
      plateau[2][1].setType(Gagne);
      plateau[3][0].setType(Gagne);
    }
    else if( (!plateau[0][4].estVide()) && ( plateau[0][4].memeType(plateau[1][3]) ) && ( plateau[0][4].memeType(plateau[2][2]) ) && ( plateau[0][4].memeType(plateau[3][1]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][4].getType();
      plateau[0][4].setType(Gagne);
      plateau[1][3].setType(Gagne);
      plateau[2][2].setType(Gagne);
      plateau[3][1].setType(Gagne);
    }
    else if( (!plateau[1][3].estVide()) && ( plateau[1][3].memeType(plateau[2][2]) ) && ( plateau[1][3].memeType(plateau[3][1]) ) && ( plateau[1][3].memeType(plateau[4][0]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][3].getType();
      plateau[1][3].setType(Gagne);
      plateau[2][2].setType(Gagne);
      plateau[3][1].setType(Gagne);
      plateau[4][0].setType(Gagne);
    }
    else if( (!plateau[0][5].estVide()) && ( plateau[0][5].memeType(plateau[1][4]) ) && ( plateau[0][5].memeType(plateau[2][3]) ) && ( plateau[0][5].memeType(plateau[3][2]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][5].getType();
      plateau[0][5].setType(Gagne);
      plateau[1][4].setType(Gagne);
      plateau[2][3].setType(Gagne);
      plateau[3][2].setType(Gagne);
    }
    else if( (!plateau[1][4].estVide()) && ( plateau[1][4].memeType(plateau[2][3]) ) && ( plateau[1][4].memeType(plateau[3][2]) ) && ( plateau[1][4].memeType(plateau[4][1]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][4].getType();
      plateau[1][4].setType(Gagne);
      plateau[2][3].setType(Gagne);
      plateau[3][2].setType(Gagne);
      plateau[4][1].setType(Gagne);
    }
    else if( (!plateau[2][3].estVide()) && ( plateau[2][3].memeType(plateau[3][2]) ) && ( plateau[2][3].memeType(plateau[4][1]) ) && ( plateau[2][3].memeType(plateau[5][0]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][3].getType();
      plateau[2][3].setType(Gagne);
      plateau[3][2].setType(Gagne);
      plateau[4][1].setType(Gagne);
      plateau[5][0].setType(Gagne);
    }
    else if( (!plateau[0][6].estVide()) && ( plateau[0][6].memeType(plateau[1][5]) ) && ( plateau[0][6].memeType(plateau[2][4]) ) && ( plateau[0][6].memeType(plateau[3][3]) ) ) 
    {
      fini = true;
      typegagne = plateau[0][6].getType();
      plateau[0][6].setType(Gagne);
      plateau[1][5].setType(Gagne);
      plateau[2][4].setType(Gagne);
      plateau[3][3].setType(Gagne);
    }
    else if( (!plateau[1][5].estVide()) && ( plateau[1][5].memeType(plateau[2][4]) ) && ( plateau[1][5].memeType(plateau[3][3]) ) && ( plateau[1][5].memeType(plateau[4][2]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][5].getType();
      plateau[1][5].setType(Gagne);
      plateau[2][4].setType(Gagne);
      plateau[3][3].setType(Gagne);
      plateau[4][2].setType(Gagne);
    }
    else if( (!plateau[2][4].estVide()) && ( plateau[2][4].memeType(plateau[3][3]) ) && ( plateau[2][4].memeType(plateau[4][2]) ) && ( plateau[2][4].memeType(plateau[5][1]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][4].getType();
      plateau[2][4].setType(Gagne);
      plateau[3][3].setType(Gagne);
      plateau[4][2].setType(Gagne);
      plateau[5][1].setType(Gagne);
    }
    else if( (!plateau[1][6].estVide()) && ( plateau[1][6].memeType(plateau[2][5]) ) && ( plateau[1][6].memeType(plateau[3][4]) ) && ( plateau[1][6].memeType(plateau[4][3]) ) ) 
    {
      fini = true;
      typegagne = plateau[1][6].getType();
      plateau[1][6].setType(Gagne);
      plateau[2][5].setType(Gagne);
      plateau[3][4].setType(Gagne);
      plateau[4][3].setType(Gagne);
    }
    else if( (!plateau[2][5].estVide()) && ( plateau[2][5].memeType(plateau[3][4]) ) && ( plateau[2][5].memeType(plateau[4][3]) ) && ( plateau[2][5].memeType(plateau[5][2]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][5].getType();
      plateau[2][5].setType(Gagne);
      plateau[3][4].setType(Gagne);
      plateau[4][3].setType(Gagne);
      plateau[5][2].setType(Gagne);
    }
    else if( (!plateau[2][6].estVide()) && ( plateau[2][6].memeType(plateau[3][5]) ) && ( plateau[2][6].memeType(plateau[4][4]) ) && ( plateau[2][6].memeType(plateau[5][3]) ) ) 
    {
      fini = true;
      typegagne = plateau[2][6].getType();
      plateau[2][6].setType(Gagne);
      plateau[3][5].setType(Gagne);
      plateau[4][4].setType(Gagne);
      plateau[5][3].setType(Gagne);
    }
  }
  else
  {
    casevide = true;
  }

  /* Si le jeu est totalement rempli, alors on met fini à vrai */
  if( !plateau[0][0].estVide() && !plateau[0][1].estVide() && !plateau[0][2].estVide() && !plateau[0][3].estVide() && !plateau[0][4].estVide() && !plateau[0][5].estVide() && !plateau[0][6].estVide() ) 
    fini = true;
}

//Fonction qui retourne le joueur courant
Case Jeu::getTypeGagne()
{
  return typegagne;
}

Case Jeu::getTour()
{
  /* Retourne le Jeton en cours */
  return tour;
}

Case Jeu::getCase(int i, int j)
{
  /* Retourne le type de la case ciblée */
  return plateau[i][j].getType();
}

bool Jeu::estHumain()
{
  if(tour==Rond)
    return j1==Humain;
  else
    return j2==Humain;
}

TypeJoueur Jeu::getTypeJoueur()
{
  if(tour==Rond)
    return j1;
  else
    return j2;
}

bool Jeu::estVide(int i, int j)
{
  /* Retourne si la case est vide */
  return plateau[i][j].estVide();
}

void Jeu::simuleJoue(int i,int j)
{
  plateau[i][j].setType(tour);
  tour = (tour==Rond)?Croix:Rond;
}

void Jeu::joue(int i, int j)
{
  plateau[i][j].setType(tour);
  verifFini();
  tour = (tour==Rond)?Croix:Rond;
}

void Jeu::annuleCoup(int a, int b)
{
  plateau[a][b].setType(Vide);
  tour = (tour==Rond)?Croix:Rond;
}

void Jeu::setTypeJoueur(int i, int type)
{
  if(i==1)
  {
    j1 = (TypeJoueur) type;
  }
  else
  {
    j2 = (TypeJoueur) type;
  }
}
