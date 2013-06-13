#ifndef H_IA
#define H_IA

#include "Jeu.h"

/* On définit les constante de l'évaluation */
const int MINEVAL=-100000;
const int MAXEVAL=100000;

/* Classe qui gére l'intelligence artificielle */
class IA
{
  private:
    Case joueurCourant;
    int evalue_cnt;

  public:
    /* Constructeur de la classe IA */
    IA();
    /* Destructeur de la classe IA */
    ~IA();

    /* Fonction qui calcule le prochain coup optimal */
    void calcIA(Jeu *j, int profondeur);

    /* Fonctions de calculMinMax */
    int calcMin(Jeu *j, int profondeur, int alpha, int beta);
    int calcMax(Jeu *j, int profondeur, int alpha, int beta);

    /* Fonction évaluant le score du joueur courant */
    int calcScore(int, int);

    /* Fonction qui évalue l'état du plateau de jeu */
    int evalue(Jeu *j);

    /* Fonction comptant le nombre total de pions présents sur le plateau */
    int comptePions(Jeu *j);
};

#endif
