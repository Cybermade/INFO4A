#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <iostream>

using namespace std;

class Labyrinthe
{
private:
    int NB_LIGNES;
    int NB_COLONNES;
    char lel;
    char AFF_VIDE = '-'; //Caractère représentant les cases vides pour l’affichage
    char AFF_MUR = 'X';  //Caractère représentant les murs pour l’affichage
    char AFF_BORD = ' ';
    char *Grille=NULL;
    int *Pile=NULL;
    int Sommet ;
    int pop();
    void push(int x);

public:
    Labyrinthe(int nLignes, int nColonnes);
    Labyrinthe(char data[]);
    ~Labyrinthe();
    int getLongueur();
    int getLargeur();
    int getID(int ligne, int colonne);
    int getLigne(int id);
    int getCol(int id);
    void modifie(int ligne, int colonne, char x);
    void affiche();
    char lit(int ligne, int colonne);
    bool connexe();
    void genLaby(int nb);
    //int distMin(int id1, int id2);*/
};
#endif