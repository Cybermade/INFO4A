//HAMIDOU Mohammed Nazim IE4-I911
//compilation :g++ P3.cpp -o P3 Labyrinthe.o -Wall
//lancement : ./P3

// Partie 3 du projet : poursuite de robots

#include <iostream>
#include "Labyrinthe.h"
#include <algorithm>
#include <math.h>

using namespace std;

// Attend que duree (en secondes) se soit écoulée depuis le dernier appel.
void synchro(double duree)
{
    static clock_t jalon = clock();
    jalon = jalon + (clock_t)(duree * CLOCKS_PER_SEC);
    ;
    while (clock() < jalon)
        ;
}

///============================================================================
/// Vous devez compléter l'implémentation de cette classe qui hérite de
/// La classe Labyrinthe. Toutes les méthodes publiques de Labyrinthe sont
/// disponibles. Vous pouvez ajouter des attributs et des méthodes.
///============================================================================

class Laby : public Labyrinthe
{
private:
    // Positions des robots
    int idRobotA;
    int idRobotB;

    // ------- Ajoutez ici des attributs supplémentaires si applicable --------

    // ------------------------------------------------------------------------
public:
    // Produit un labyrinthe avec une densité de cases blanches égale à density.
    // Les positions initiale des deux robots sont situées dans les coins supérieur gauche
    // et inférieur droit. Les codes des robots ne sont pas placés dans le grilles, dont
    // toutes les cases vides sont initialisées à 0.
    Laby(int nLignes, int nColonnes, double density);

    // Construit un labyrinthe d'après un descripteur.
    Laby(char *descr);

    int getIdRobotA() { return idRobotA; }
    int getIdRobotB() { return idRobotB; }
    void setIdRobotA(int id) { idRobotA = id; }
    void setIdRobotB(int id) { idRobotB = id; }

    // Produit un identifiant aléatoire de case vide (PAS un mur)/
    int caseRandom();

    // Réalise un mouvemement du robot prédateur. La grille ne doit contenir que des cases
    // vides et des murs.
    // L'attribut idRobotA est modifié. La grille n'est pas modifiée.
    // Retourne false si les robots sont en contact (dans ce cas A n'est pas déplacé),
    // et true si les robots n'étaient pas en contact avant le déplacement de A.
    // Au moins un algorithme de déplacement doit être implémenté. Les algorithmes
    // implémentés doivent être numéroté à partir de 1. Par exemple, si deux algorithmes sont
    // implémentés, ils sont numérotés 1 et 2. Le paramètre algo désigne l'algorithme à
    // utiliser. Si un seul algorithme est utilisé, sa valuer doit être 1.
    bool deplaceRobotA(int algo);

    // Réalise un mouvemement du robot proie. Mêmes convension que deplaceRobotB.
    bool deplaceRobotB(int algo);

    // Place les robots (identifiés par les valeurs 2 et 3) dans la grille. Efface l'écran.
    // Affiche la grille. Enlève les robots de lagrille (pour ne pas perturber distMin).
    void visualisation();

    // Lance une poursuite dans le labyrinthe courant. Si silent == true, aucun affichage n'est
    // réalisé, sinon il y a affichage de chaque étape.
    // Une étape = un mouvement de chaque robot. Si le nombre d'étape atteint timeout, la
    // valeur timeout+1 est retournée, sinon le nombre d'étape avant contact des robots est
    // retourné. Si random == true, les position initiales des robots sont aléatoires, sinon ce
    // sont les coins supérieur gauche et inféieur droit.
    // Les paramètres algoA et algoB indiquent le algorithmes utilisé pour les robots.
    int course(int timeout, bool silent, bool random, int algoA, int algoB);

    // Réalise nCourses courses et retourne la médiane des valeurs retournées par les
    // appels à la méthode courses. Le apramètres algoA et algoB donnent les algorithmes
    // à utiliser pour les robots A et B.
    int evalue(int nCourses, int timeOut, int algoA, int algoB);
};

// Constructeur fourni par O. Bailleux. Peut être complété si nécessaire.
Laby::Laby(int nLignes, int nColonnes, double density) : Labyrinthe(nLignes, nColonnes)
{
    setAff(" XAB.");
    idRobotA = getID(0, 0);
    idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
    genLaby((int)(density * getNbColonnes() * getNbLignes()));
    // Ajouter les initialisations supplémentaire nécessaires, si applicable
}

// Constructeur fourni gracieusement par O. Bailleux. Peut être complété si nécessaire.
Laby::Laby(char *descr) : Labyrinthe(descr)
{
    setAff(" XAB.");
    idRobotA = getID(0, 0);
    idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
    // Ajouter les initialisations supplémentaire nécessaires, si applicable
}

// Méthode fournie par O. Bailleux
void Laby::visualisation()
{
    // Les robots sont placés dans la grille avant l'affichage
    modifie(getIdRobotA(), 2);
    modifie(getIdRobotB(), 3);

    system("clear");
    affiche();

    // Les robots sont retirés de la grille pour ne pas perturber la recherche de chemins
    // optimaux par la méthode distMin.
    modifie(getIdRobotA(), 0);
    modifie(getIdRobotB(), 0);
}

// Méthode fournie par O. Bailleux
int Laby::course(int timeout, bool silent, bool random, int algoA, int algoB)
{
    if (random)
    { // Course avec positions initiales des robots aléatoire
        idRobotB = caseRandom();
        idRobotA = caseRandom();
    }
    else
    { // Course avec départ dans les coins opposés.
        idRobotA = getID(0, 0);
        idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
    }

    int nEtapes = 0;
    bool contact = false;

    // Arret quand les robots se touchent ou de nombre maxi d'étapes atteint
    while (!contact && nEtapes < timeout)
    {
        // On déplace le robot A
        contact = !deplaceRobotA(algoA);

        // On déplace le robot B sauf s'il est en contact avec A
        if (!contact)
            contact = !deplaceRobotB(algoB);

        nEtapes++;
        if (!silent)
        { // Délai et affichage seulement si on est pas en mode silencieux
            synchro(0.1);
            visualisation();
        }
    }

    if (contact)
        return nEtapes;
    else
        return timeout + 1;
}

// Méthode fournie par O. Bailleux
int Laby::evalue(int nCourses, int timeout, int algoA, int algoB)
{
    int *tab = new int[nCourses]; // Tableau des scores

    for (int i = 0; i < nCourses; i++)
    { // On lance une course et récupère le score
        cout << i << " / " << nCourses;
        tab[i] = course(timeout, true, true, algoA, algoB);
        cout << " --> " << tab[i] << endl;
    }

    // Tri du tableau de score pour calcul de la médiane.
    sort(tab, tab + nCourses);
    return tab[nCourses / 2];
}

///============================================================================
/// Méthodes à compléter. Vous pouvez ajouter les méthodes supplémentaires
/// pour simplifier votre programme et le rendre plus lisible.
///============================================================================

int Laby::caseRandom()
{
    int caserd = rand() % (getNbLignes() * getNbColonnes());
    while (lit(caserd) == 1)
    {
        caserd = rand() % (getNbLignes() * getNbColonnes());
    }
    return caserd;
}

// Méthode à compléter
bool Laby::deplaceRobotA(int algo)
{
    int nbcol = getNbColonnes();
    int nblig = getNbLignes();
    int colA = getCol(getIdRobotA());
    int ligA = getLigne(getIdRobotA());
    int IDs[4] = {0};
    int comp = 0;
    int idtemp;

    int distmin = 0;
    int dist;

    if (getIdRobotA() == getIdRobotB())
        return false;

    if (algo == 1) //au hasard parmis les min 
    {
        if (colA - 1 >= 0 && !lit(getID(ligA, colA - 1)))//si case vide
        {
            setIdRobotA(getID(ligA, colA - 1));//je déplace A vers la case voisine

            dist = distMin(getIdRobotA(), getIdRobotB());// je calcule ma distance min

            distmin = dist;// j'initialise distmin

            IDs[comp++] = getIdRobotA();//je mets l'id de cette case dans mon tableau
            
        }
        if (colA + 1 < nbcol && !lit(getID(ligA, colA + 1)))
        {
            setIdRobotA(getID(ligA, colA + 1));

            dist = distMin(getIdRobotA(), getIdRobotB());

            if (dist < distmin || distmin == 0)//le distmin==0 sert si aucun if n'a été lancé
            {
                distmin = dist;
                comp = 0;
                IDs[comp++] = getIdRobotA();//distance minimal donc je mets dans mon tableau mon nouvel id à la place de l'id d'avant
            }
            else if (dist == distmin)
                IDs[comp++] = getIdRobotA();//sinon si la distance minimal est égale à celle d'avant je rajoute dans mon tableau cet id à celui d'avant
                
            
        }
        if (ligA - 1 >= 0 && !lit(getID(ligA - 1, colA)))
        {
            setIdRobotA(getID(ligA - 1, colA));

            dist = distMin(getIdRobotA(), getIdRobotB());

            if (dist < distmin || distmin == 0)
            {
                distmin = dist;
                comp = 0;
                IDs[comp++] = getIdRobotA();
            }
            else if (dist == distmin)
                IDs[comp++] = getIdRobotA();
                
        }
        if (ligA + 1 < nblig && !lit(getID(ligA + 1, colA)))
        {
            setIdRobotA(getID(ligA + 1, colA));

            dist = distMin(getIdRobotA(), getIdRobotB());

            if (dist < distmin || distmin == 0)
            {
                distmin = dist;
                comp = 0;
                IDs[comp++] = getIdRobotA();
            }
            else if (dist == distmin)
                IDs[comp++] = getIdRobotA();
                
        }
            
        setIdRobotA(IDs[rand() % comp]);//je prends une id au hasard parmi ceux qui ont la même distance entre A et B.
        return true;
    }
    if (algo == 2) //min
    {
        distmin = distMin(idRobotA, idRobotB);
        idtemp = idRobotA;
        if (colA - 1 >= 0 && !lit(getID(ligA, colA - 1)) && distmin > distMin(getID(ligA, colA - 1), idRobotB))
        {
            idtemp = getID(ligA, colA - 1);
            distmin = distMin(idtemp, idRobotB);
        }
        if (colA + 1 < nbcol && !lit(getID(ligA, colA + 1)) && distmin > distMin(getID(ligA, colA + 1), idRobotB))
        {
            idtemp = getID(ligA, colA + 1);
            distmin = distMin(idtemp, idRobotB);
        }
        if (ligA - 1 >= 0 && !lit(getID(ligA - 1, colA)) && distmin > distMin(getID(ligA - 1, colA), idRobotB))
        {
            idtemp = getID(ligA - 1, colA);
            distmin = distMin(idtemp, idRobotB);
        }
        if (ligA + 1 < nblig && !lit(getID(ligA + 1, colA)) && distmin > distMin(getID(ligA + 1, colA), idRobotB))
        {
            idtemp = getID(ligA + 1, colA);
            distmin = distMin(idtemp, idRobotB);
        }

        setIdRobotA(idtemp);
        return true;
    }
    return false;
}

bool Laby::deplaceRobotB(int algo)
{
    int nbcol = getNbColonnes();
    int nblig = getNbLignes();
    int colB = getCol(getIdRobotB());
    int ligB = getLigne(getIdRobotB());
    int IDs[4] = {0};
    int comp = 0;
    int idtemp;
    int distmax ;
    
    if (getIdRobotA() == getIdRobotB())
        return false;

    if (algo == 1) //hasard
    {
        if (colB - 1 >= 0 && !lit(getID(ligB, colB - 1)))
            IDs[comp++] = getID(ligB, colB - 1);
        if (colB + 1 < nbcol && !lit(getID(ligB, colB + 1)))
            IDs[comp++] = getID(ligB, colB + 1);
        if (ligB - 1 >= 0 && !lit(getID(ligB - 1, colB)))
            IDs[comp++] = getID(ligB - 1, colB);
        if (ligB + 1 < nblig && !lit(getID(ligB + 1, colB)))
            IDs[comp++] = getID(ligB + 1, colB);

        setIdRobotB(IDs[rand() % comp]);
    }
    if (algo == 2) //max
    {
        distmax = distMin(idRobotA, idRobotB);
        idtemp = idRobotB;
        if (colB - 1 >= 0 && !lit(getID(ligB, colB - 1)) && distmax < distMin(getID(ligB, colB - 1), idRobotA))
        {//je prends toujours la distance minimal la plus grande entre les 5 cases potentiels possible (case B et ses 4 voisines)
            idtemp = getID(ligB, colB - 1);
            distmax = distMin(idtemp, idRobotA);
        }
        if (colB + 1 < nbcol && !lit(getID(ligB, colB + 1)) && distmax < distMin(getID(ligB, colB + 1), idRobotA))
        {
            idtemp = getID(ligB, colB + 1);
            distmax = distMin(idtemp, idRobotA);
        }
        if (ligB - 1 >= 0 && !lit(getID(ligB - 1, colB)) && distmax < distMin(getID(ligB - 1, colB), idRobotA))
        {
            idtemp = getID(ligB - 1, colB);
            distmax = distMin(idtemp, idRobotA);
        }
        if (ligB + 1 < nblig && !lit(getID(ligB + 1, colB)) && distmax < distMin(getID(ligB + 1, colB), idRobotA))
        {
            idtemp = getID(ligB + 1, colB);
            distmax = distMin(idtemp, idRobotA);
        }

        setIdRobotB(idtemp);
    }

    return true;
}

///============================================================================
/// Quelques descripteurs qui seront utilisés pour évaluer les algos de poursuite
///============================================================================

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.8
char descripteur1[] = 
{ 20, 30,
0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 
0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 
0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 
1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes sans murs
char descripteur2[] = 
{ 20, 30,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.9
char descripteur3[] = 
{ 20, 30,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.7
char descripteur4[] =
{ 20, 30,
0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 
0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 
0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 
1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 
1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 
1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 
0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 
1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
};
///============================================================================
/// Exemple d'utilisation.
///============================================================================

void testPoursuite()
{
    int dureeMax = 300;
    Laby laby(30, 60, 0.9);

    int duree = laby.course(dureeMax, false, true, 1, 2);
    

    if (duree > dureeMax)
    {
        cout << "Echec apres " << dureeMax << " etapes" << endl;
    }
    else
    {
        cout << "Succes apres " << duree << " etapes" << endl;
    }
}

void testEval()
{
    Laby laby(descripteur2);

    int score = laby.evalue(100, 100, 1, 2);

    cout << "Mediane : " << score << endl;
}

int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));

    testPoursuite();
    testEval();

    return 0;
}
