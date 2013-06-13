#include "Ia.h"

using namespace std;

IA::IA()
{
}

IA::~IA()
{
}

int IA::calcScore(int cntpion, int cntjoueur)
{
  /* On regarde le nombre de pions allignés et on retourne une valeur en fonction du nombre de pions du joueur */
  switch(cntpion)
  {
    case 0: 
      return 0;
    case 1:
      return 1*cntjoueur;
    case 2:
      return 3*cntjoueur;
    case 3:
      return 100*cntjoueur;
    case 4:
      return 250*cntjoueur;
    default:
      return 90*cntjoueur;
  }
}


int IA::evalue(Jeu *jeu)
{
  /* On initialise le score à 0 */
  int score=0;

  /* On initialise le compteur de pions du joueur et le compteur de pions total */
  int cntjoueur, cntpion;
  int i,j;

  /* Incrementer le compteur d'evaluation pour l'alpha beta */
  evalue_cnt++;

  /* Si le jeu est fini */
  if(jeu->getFini())
  {
    /* Si l'IA a gagné, on retourn 1000 - le nombre de pions */
    if(jeu->getTypeGagne() == joueurCourant)
      score = 1000-comptePions(jeu);
    /* Si il y a égalité, on retourne 0 */
    else if(jeu->getTypeGagne() == Vide)
      score = 0;
    /* Sinon.. le joueur a gagné, alors on retourne -1000 + le nombre de pions */
    else
      score = -1000+comptePions(jeu);
    return score;
  }

  /* On calcule le score du joueur courant sur les lignes */
  for(i=0;i<6;i++)
  {
    cntpion=0;
    cntjoueur=0;
    /* On regarde chaque case */
    for(j=0;j<4;j++)
    {
      /* Si la case n'est pas vide */
      if(jeu->getCase(i,j)!=Vide)
      {
        /* On incrémente le compteur de pions totaux */
        cntpion++;
        /* Si la case est occupée par un pion du joueur courant, on incrémente le compteur du pions du joueur */
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        /* Sinon, on décrémente ce compteur */
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);

    cntpion=0;
    cntjoueur=0;
    for(j=1;j<5;j++)
    {
      if(jeu->getCase(i,j)!=Vide)
      {
        cntpion++;
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);

    cntpion=0;
    cntjoueur=0;
    for(j=2;j<6;j++)
    {
      if(jeu->getCase(i,j)!=Vide)
      {
        cntpion++;
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);

    cntpion=0;
    cntjoueur=0;
    for(j=3;j<7;j++)
    {
      if(jeu->getCase(i,j)!=Vide)
      {
        cntpion++;
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);
  }

  /* On calcule le score du joueur courant sur les colonnes */
  for(j=0;j<7;j++)
  {
    cntpion=0;
    cntjoueur=0;
    for(i=0;i<4;i++)
    {
      if(jeu->getCase(i,j)!=Vide)
      {
        cntpion++;
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);

    cntpion=0;
    cntjoueur=0;
    for(i=1;i<5;i++)
    {
      if(jeu->getCase(i,j)!=Vide)
      {
        cntpion++;
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);

    cntpion=0;
    cntjoueur=0;
    for(i=2;i<6;i++)
    {
      if(jeu->getCase(i,j)!=Vide)
      {
        cntpion++;
        if(jeu->getCase(i,j)==joueurCourant)
          cntjoueur++;
        else
          cntjoueur--;
      }
    }
    score += calcScore(cntpion,cntjoueur);
  }

  /* On calcule le score du joueur courant sur les diagonales */


  /* Diagonale 1 */
  cntpion=0;
  cntjoueur=0;
  for(i=0,j=3;i<4;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 2 */
  cntpion=0;
  cntjoueur=0;
  for(i=0,j=2;i<4;i++,j++)
  { 
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=1,j=2;i<5;i++,j++)
  { 
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 3 */
  cntpion=0;
  cntjoueur=0;
  for(i=0,j=1;i<4;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=1,j=2;i<5;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=2,j=3;i<6;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 4 */
  cntpion=0;
  cntjoueur=0;
  for(i=0;i<4;i++)
  {
    if(!jeu->estVide(i,i))
    {
      cntpion++;
      if(jeu->getCase(i,i)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=1;i<5;i++)
  {
    if(!jeu->estVide(i,i))
    {
      cntpion++;
      if(jeu->getCase(i,i)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=2;i<6;i++)
  {
    if(!jeu->estVide(i,i))
    {
      cntpion++;
      if(jeu->getCase(i,i)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 5 */
  cntpion=0;
  cntjoueur=0;
  for(i=1,j=0;i<5;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=2,j=1;i<6;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 6 */
  cntpion=0;
  cntjoueur=0;
  for(i=2,j=0;i<6;i++,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 7 */
  cntpion=0;
  cntjoueur=0;
  for(i=3,j=0;j<4;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 8 */
  cntpion=0;
  cntjoueur=0;
  for(i=4,j=0;j<4;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=3,j=1;j<5;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 9 */
  cntpion=0;
  cntjoueur=0;
  for(i=5,j=0;j<4;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=4,j=1;j<5;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=3,j=2;j<6;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 10 */
  cntpion=0;
  cntjoueur=0;
  for(i=5,j=1;j<5;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=4,j=2;j<6;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=3,j=3;j<7;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 11 */
  cntpion=0;
  cntjoueur=0;
  for(i=5,j=2;j<6;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  cntpion=0;
  cntjoueur=0;
  for(i=4,j=3;j<7;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);


  /* Diagonale 12 */
  cntpion=0;
  cntjoueur=0;
  for(i=5,j=3;j<7;i--,j++)
  {
    if(!jeu->estVide(i,j))
    {
      cntpion++;
      if(jeu->getCase(i,j)==joueurCourant)
        cntjoueur++;
      else
        cntjoueur--;
    }
  }
  score += calcScore(cntpion,cntjoueur);

  return score;

}

int IA::comptePions(Jeu *jeu)
{
  /* Pour chaque case du plateau, si la case n'est pas vide, on incrémente le compteur de jetons */
  int i,j,cnt=0;
  for(i=0;i<6;i++)
    for(j=0;j<7;j++)
    {
      if(jeu->getCase(i,j)!=Vide)
        cnt++;
    }
  return cnt;
}

void IA::calcIA(Jeu *jeu, int profondeur)
{
  int i,j,tmp;
  int mini=-1, minj=-1;
  int alpha = MINEVAL;
  int beta = MAXEVAL;

  /* On met le compteur d'évaluation à zéro */
  evalue_cnt = 0;

  /* On met en place le joueur courant */
  joueurCourant = jeu->getTour();

  /* Si la profondeur est nulle ou la partie est finie, on ne fait pas le calcul */
  if( (profondeur!=0) || (!jeu->getFini()) )
  {
    /* On parcourt les cases du plateau */
    for(i=0;i<6;i++)
      for(j=0;j<7;j++)
      {
        /* Si la case est vide, et la case est jouable */
        if( ( (jeu->estVide(i,j)) && (!jeu->estVide(i+1,j)) ) || ( (i==5) && (jeu->estVide(i,j)) ) )
        {
          /* On simule qu'on joue cette case */
          jeu->simuleJoue(i,j);
          /* On lance le minmax, en commençant par chercher le max */
          tmp = calcMax(jeu, profondeur-1,alpha,beta);
          /* Si ce score est plus petit que béta, on le stocke dans béta et l'on récupère la position correspondantes */
          if(beta>tmp)
          {
            beta = tmp;
            mini = i;
            minj = j;
          }
          /* On annule le coup */
          jeu->annuleCoup(i,j);
        }
      }
  }
  /* On jouera le coup le plus interessant */
  cout << "Valeur du coup " << mini << "," << minj << ":" << beta << endl;
  jeu->joue(mini,minj);
}

int IA::calcMax(Jeu *jeu, int profondeur, int alpha, int beta)
{
  int i,j,tmp;
  if( (profondeur==0) || (jeu->getFini()) )
  {
    return evalue(jeu);
  }
  for(i=0;i<6; i++)
  {
    for(j=0;j<7;j++)
    {
      if( ( jeu->estVide(i,j) && !jeu->estVide(i+1,j) ) || ( i==5 && jeu->estVide(i,j) ) )
      {
        jeu->simuleJoue(i,j);
        tmp = calcMin(jeu, profondeur-1,alpha,beta);
        jeu->annuleCoup(i,j);
        if(alpha<tmp)
        {
          alpha = tmp;
        }
        if(beta <= alpha)
        {
          return alpha;
        }
      }
    }
  }
  return alpha;
}

int IA::calcMin(Jeu *jeu, int profondeur, int alpha, int beta)
{
  int i,j,tmp;

  /* Si on est à la profondeur voulue ou le jeu est fini, on retourne l'évaluation */
  if( (profondeur==0) || (jeu->getFini()) )
  {
    return evalue(jeu);
  }
  /* On parcourt le plateau */ 
  for(i=0;i<6; i++)
  {
    for(j=0;j<7;j++)
    { 
      /* Si la case est vide et jouable */
      if( ( jeu->estVide(i,j) && !jeu->estVide(i+1,j) ) || ( i==5 && jeu->estVide(i,j) ) )
      {
        /* On simule le coup */
        jeu->simuleJoue(i,j);
        tmp = calcMax(jeu, profondeur-1,alpha,beta);
        /* On annule le coup */
        jeu->annuleCoup(i,j);
        /* On met a jours béta */
        if(beta>tmp)
	{
          beta = tmp;
        }
        /* Si béta est inferieur ou égal à alpha, alors on retourne la valeur de béta */
        if(beta<=alpha)
        {
          return beta;
        }
      }
    }
  }
  return beta;
}


