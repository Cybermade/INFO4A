//HAMIDOU Mohammed Nazim IE4-I911
//Compilation : g++ HAMIDOUP4.cpp -o P4 -Wall
//Lancement : ./P4

#include <iostream>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <math.h>
///COULEURS POUR AFFICHAGE DES ROBOTS POUR LA CONTRIBUTION PERSONNELLE
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

using namespace std;
class Labyrinthe
{
private:
    int NB_COLONNES; //longueur
    int NB_LIGNES;   //largeur
    int NB_MOTIFS;   //Motifs
    char *Grille = NULL;
    char *Motifs = NULL;
    int *Pile = NULL;
    int Sommet = 0;
    void push(int x);
    int pop();

public:
    /// Constructeurs et destructeurs
    Labyrinthe(int nLignes, int nColonnes); //Crée un labyrinthe vide.
    Labyrinthe(char data[]);                //Crée un labyrinthe à partir d'un descripteur.
    ~Labyrinthe();                          //Détruit le labyrinthe courant.
    /// Méthodes d'accès
    int getID(int ligne, int colonne);            //Retourne l'identifiant d'une cellule.
    int getLigne(int id);                         //Retourne la ligne de la cellule d'identifiant id.
    int getCol(int id);                           //Retourne la colonne de la cellule d'identifiant id.
    void modifie(int ligne, int colonne, char x); //Modifie la valeur d'une cellule.
    char lit(int ligne, int colonne);             //Retourne la valeur de la cellule de coordonnées (i,j).
    /// Méthode d'accès supplémentaires
    int getNbLignes();            //Retourne le nombre de lignes de la grille.
    int getNbColonnes();          //Retourne le nombre de lignes de la grille.
    int lit(int id);              //Retourne la valeur de la cellule id.
    void modifie(int id, char x); //Modifie la valeur de la cellule id.
    /// Méthodes d'affichage
    // Initialise les caractères utilisés pour l'affichage.
    // Si motif contient n caractères alors
    // motif[i] est affiché pour représenter une case de valeur i entre 0 et n-2.
    // Toute autre valeur provoque l'affichage du caractère motif[n-1].
    void setAff(const char *motifs);
    void affiche(); // Affiche le labyrinthe.

    bool connexe();                //Vérifie si toutes les cellules de valeur 0 sont connectées.
    void genLaby(int nb);          //Produit un labyrinthe aléatoire connexe avec nb cases blanches.
    int distMin(int id1, int id2); //Retourne la distance minimal entre les cases id1 et id2.

    //CONTRIBUTION PERSONNELLE
    void afficheJeu(); // Affiche le labyrinthe du jeu(même fonction qu'affiche mais les robots ont des couleurs)
};

void Labyrinthe::push(int x)
{
    Pile[Sommet++] = x;
}
int Labyrinthe::pop()
{
    return Pile[--Sommet];
}
Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
    this->NB_LIGNES = nLignes;
    this->NB_COLONNES = nColonnes;
    setAff(" X.");
    Grille = new char[NB_LIGNES * NB_COLONNES];
    Pile = new int[NB_LIGNES * NB_COLONNES];
}
Labyrinthe::Labyrinthe(char data[])
{
    this->NB_LIGNES = data[0];
    this->NB_COLONNES = data[1];
    setAff(" X.");
    Grille = new char[NB_LIGNES * NB_COLONNES];
    Pile = new int[NB_LIGNES * NB_COLONNES];
    for (int i = 0; i + 2 < NB_LIGNES * NB_COLONNES; i++)
    {
        Grille[i] = data[i + 2];
    }
}
Labyrinthe::~Labyrinthe()
{
    delete[] Grille;
    delete[] Pile;
    delete[] Motifs;
}
int Labyrinthe::getID(int ligne, int colonne)
{
    return ligne * NB_COLONNES + colonne;
}
int Labyrinthe::getLigne(int id)
{
    return id / NB_COLONNES;
}
int Labyrinthe::getCol(int id)
{
    return id % NB_COLONNES;
}
void Labyrinthe::modifie(int ligne, int colonne, char x)
{
    Grille[getID(ligne, colonne)] = x;
}
char Labyrinthe::lit(int ligne, int colonne)
{
    return Grille[getID(ligne, colonne)];
}
int Labyrinthe::getNbLignes()
{
    return NB_LIGNES;
}
int Labyrinthe::getNbColonnes()
{
    return NB_COLONNES;
}
int Labyrinthe::lit(int id)
{
    return Grille[id];
}
void Labyrinthe::modifie(int id, char x)
{
    Grille[id] = x;
}
void Labyrinthe::setAff(const char *motifs)
{
    if (Motifs != NULL)
    {
        delete[] Motifs;
    }

    this->NB_MOTIFS = strlen(motifs);
    Motifs = new char[NB_MOTIFS];

    strcpy(Motifs, motifs);
}
void Labyrinthe::affiche()
{
    for (int l = 0; l < NB_COLONNES + 2; l++)
        printf("%c", Motifs[NB_MOTIFS - 1]); //BORD HAUT (on doit aller avant la premiere colonne jusqu'à une fois aprés la derniére c'est pour ça le l<NB_COLONNES+2)

    printf("\n");
    for (int m = 0; m < NB_LIGNES; m++)
    {
        printf("%c", Motifs[NB_MOTIFS - 1]); //On commence le bord a gauche
        for (int l = 0; l < NB_COLONNES; l++)
        {
            
            printf("%c", Motifs[lit(getID(m, l))]);
        }

        printf("%c\n", Motifs[NB_MOTIFS - 1]); //on termine a droite
    }
    for (int l = 0; l < NB_COLONNES + 2; l++)
        printf("%c", Motifs[NB_MOTIFS - 1]); //BORD BAS
    printf("\n");
}

bool Labyrinthe::connexe()
{
    int nbcasesb = 0, id = 0, nbcasesm = 0;
    int ligne, colonne;

    for (int m = 0; m < NB_LIGNES; m++)
    {
        for (int l = 0; l < NB_COLONNES; l++)
        {
            if (!(lit(m, l)))
            {
                nbcasesb++;
                id = getID(m, l);
            }
        }
    }
    modifie(getLigne(id), getCol(id), 2);
    if (!nbcasesb)
    {
        printf("Erreur Pas de cases blanches");
        exit(0);
    }
    push(id);
    while (Sommet)
    {
        id = pop();
        ligne = getLigne(id);
        colonne = getCol(id);

        for (int m = -1; m < 2; m = m + 2) // on compare verticalement
        {
            if (ligne + m >= 0 && ligne + m < NB_LIGNES && !(lit(ligne + m, colonne))) //lit(ligne+m,colonne)
            {
                modifie(ligne + m, colonne, 2);
                push(getID(ligne + m, colonne));
            }
        }

        for (int l = -1; l < 2; l = l + 2) //on compare horizontalement
        {
            if (colonne + l >= 0 && colonne + l < NB_COLONNES && !(lit(ligne, colonne + l)))
            {
                modifie(ligne, colonne + l, 2);
                push(getID(ligne, colonne + l));
            }
        }
    }
    for (int m = 0; m < NB_LIGNES; m++)
    {
        for (int l = 0; l < NB_COLONNES; l++)
        {
            if (lit(m, l) == 2)
            {
                modifie(m, l, 0);
                nbcasesm++;
            }
        }
    }
    if (nbcasesm == nbcasesb)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Labyrinthe::genLaby(int nb)
{ 
    int id = 0, IDlast, IDAvantModif, limite = 0;
    int K = 0;                                      //nbr cases vides
    IDlast = getID(NB_LIGNES - 1, NB_COLONNES - 1); // derniére case

    if (nb > (NB_LIGNES * NB_COLONNES) || nb <= 0)
    {
        if (nb > (NB_LIGNES * NB_COLONNES))
            printf("\nPas possible d'avoir plus de cases blanches que le nombre de cases totale\n");
        else if (nb <= 0)
            printf("\nPas possible d'avoir un nombre négatif ou égal à 0\n");
        exit(0);
    }
    nb = nb - 2;                     //j'enléve 2 du nombre voulu(première et derniére)
    K = NB_COLONNES * NB_LIGNES - 2; //j'enléve 2 du nombre totale de cases blanches(première et derniére)

    while (nb != K && !(limite > (NB_COLONNES * NB_LIGNES)))
    {

        while (id == 0 || id == IDlast)
            id = rand() % (NB_COLONNES * NB_LIGNES - 1); //je refais tant que j'ai une id de la premiere ou de la derniere case

        IDAvantModif = lit(getLigne(id), getCol(id)); //je prends la valeure de la case si elle était blanche(0) ou noire(1)

        modifie(getLigne(id), getCol(id), 1);

        if (connexe() && !IDAvantModif) //je test en ayant mit le case en noir si c'est toujours connexe et la case d'avant était bien blanche
        {
            K--; //car si je mets noir sur noir ça ne sert a rien
            limite = 0;
        }
        else if (!IDAvantModif)
        {
            modifie(getLigne(id), getCol(id), 0);

        } //si elle était blanche et je l'ai noircie mais elle était critique je reviens en arriére(Backtrack)

        else
            limite++; //si je rentre dans la boucle et je fais rien je limite++

        id = 0;
    }
    
}
int Labyrinthe::distMin(int id1, int id2)
{
    if (id1 == id2)
        return 0;

    int D[NB_LIGNES * NB_COLONNES] = {0};
    int P[NB_LIGNES * NB_COLONNES] = {0};
    int Comp = 0, nbcasesb = 0, min = NB_LIGNES * NB_COLONNES;
    int idtemp;
    int l, c;
    for (int i = 0; i < NB_LIGNES * NB_COLONNES; i++) //1 et 2
    {
        if (!Grille[i])
        {
            D[i] = NB_LIGNES * NB_COLONNES;
            nbcasesb++;
            P[i] = 0;
        }
        else
        {
            D[i] = -1;
            P[i] = -1;
        }
    }

    D[id1] = 0; //3

    while (nbcasesb != Comp) //4
    {                        //4.1
        for (int i = 0; i < (NB_LIGNES * NB_COLONNES); i++)
        {
            if (D[i] != -1 && D[i] < min && P[i] == 0)
            {
                min = D[i];
                idtemp = i;
            }
        }
        P[idtemp] = 1; //4.2

        Comp++; //4.2
        l = getLigne(idtemp);
        c = getCol(idtemp);
        //4.3
        if (l - 1 >= 0 && D[getID(l - 1, c)] > (D[idtemp] + 1) && P[getID(l - 1, c)] == 0)
            D[getID(l - 1, c)] = D[idtemp] + 1;
        if (l + 1 < NB_LIGNES && D[getID(l + 1, c)] > (D[idtemp] + 1) && P[getID(l + 1, c)] == 0)
            D[getID(l + 1, c)] = D[idtemp] + 1;
        if (c - 1 >= 0 && D[getID(l, c - 1)] > (D[idtemp] + 1) && P[getID(l, c - 1)] == 0)
            D[getID(l, c - 1)] = D[idtemp] + 1;
        if (c + 1 < NB_COLONNES && D[getID(l, c + 1)] > (D[idtemp] + 1) && P[getID(l, c + 1)] == 0)
            D[getID(l, c + 1)] = D[idtemp] + 1;
        min = NB_LIGNES * NB_COLONNES;
    }

    return D[id2];
}
void Labyrinthe::afficheJeu()
{
    for (int l = 0; l < NB_COLONNES + 2; l++)
        printf("%c", Motifs[NB_MOTIFS - 1]); //BORD HAUT (on doit aller avant la premiere colonne jusqu'à une fois aprés la derniére c'est pour ça le l<NB_COLONNES+2)

    printf("\n");
    for (int m = 0; m < NB_LIGNES; m++)
    {
        printf("%c", Motifs[NB_MOTIFS - 1]); //On commence le bord a gauche
        for (int l = 0; l < NB_COLONNES; l++)
        {

            if (lit(m, l) == 1 || lit(m, l) == 0)
                cout << Motifs[lit(getID(m, l))];
            else if (lit(m, l) == 2)
                cout << RED << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 3)
                cout << RED << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 4)
                cout << RED << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 5)
                cout << RED << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 6)
                cout << GREEN << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 7)
                cout << GREEN << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 8)
                cout << GREEN << Motifs[lit(getID(m, l))] << RESET;
            else if (lit(m, l) == 9)
                cout << CYAN << Motifs[lit(getID(m, l))] << RESET;
        }

        printf("%c\n", Motifs[NB_MOTIFS - 1]); //on termine a droite
    }
    for (int l = 0; l < NB_COLONNES + 2; l++)
        printf("%c", Motifs[NB_MOTIFS - 1]); //BORD BAS
    printf("\n");
}

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
    //Robots poursuivants
    int idRobotA;
    int idRobotB;
    int idRobotC;
    int idRobotD;
    //Robots poursuivis
    int idRobotE;
    int idRobotF;
    int idRobotG;
    //Robot du joueur
    int idRobotH;

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
    int getIdRobotC() { return idRobotC; }
    int getIdRobotD() { return idRobotD; }
    int getIdRobotE() { return idRobotE; }
    int getIdRobotF() { return idRobotF; }
    int getIdRobotG() { return idRobotG; }
    int getIdRobotH() { return idRobotH; }

    void setIdRobotA(int id) { idRobotA = id; }
    void setIdRobotB(int id) { idRobotB = id; }
    void setIdRobotC(int id) { idRobotC = id; }
    void setIdRobotD(int id) { idRobotD = id; }
    void setIdRobotE(int id) { idRobotE = id; }
    void setIdRobotF(int id) { idRobotF = id; }
    void setIdRobotG(int id) { idRobotG = id; }
    void setIdRobotH(int id) { idRobotH = id; }

    // Renvoi true si la case est prise par un autre robot, Renvoi false sinon
    bool casePriseAmi(int ligne, int colonne);
    bool casePriseEnnemy(int ligne, int colonne);

    // Produit un identifiant aléatoire de case vide (PAS un mur)/
    int caseRandom();
    int caseRandomjeu();

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

    void visualisationJeu();

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
    int monJeu(int timeout, bool silent, bool random);
    //Deplace le robot du joueur
    void deplacerRobotJoueur(int idRobot);
    //Deplace un robot ami afin de maximiser sa distance avec le robot ennemy le plus proche (entre A B C D) en utilisant idRobotEnnemyPlusProche
    void deplacerRobotAmi(int idRobot, int idRobot2);
    //Retourne true si les 4 robots E F G H ont perdus
    bool lesRobotsmorts();
    //Deplace un robot vers un des robots E F G H le plus proche en utilisant la methode idRobotAmiPlusProche
    void deplacerRobotEnnemy(int idRobot, int idRobot2);

    //Retourne l'id du robot le plus proche entre E F G H et idRobot
    int idRobotAmiPlusProche(int idRobot);
    //Retourne l'id robot le plus proche entre A B C D et idRobot
    int idRobotEnnemyPlusProche(int idRobot);
};

// Constructeur fourni par O. Bailleux. Peut être complété si nécessaire.
Laby::Laby(int nLignes, int nColonnes, double density) : Labyrinthe(nLignes, nColonnes)
{
    setAff(" XABCDEFGH.");
    idRobotA = getID(0, 0);
    idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
    genLaby((int)(density * getNbColonnes() * getNbLignes()));
    // Ajouter les initialisations supplémentaire nécessaires, si applicable
}

// Constructeur fourni gracieusement par O. Bailleux. Peut être complété si nécessaire.
Laby::Laby(char *descr) : Labyrinthe(descr)
{
    setAff(" XABCDEFGH.");
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
bool Laby::deplaceRobotA(int algo) //direct prédateur
{
    int nbcol = getNbColonnes();
    int nblig = getNbLignes();
    int colA = getCol(getIdRobotA());
    int ligA = getLigne(getIdRobotA());
    int IDs[4] = {0};
    int comp = 0;
    int idtemp;

    int distmin = -1;
    int dist;

    if (getIdRobotA() == getIdRobotB())
        return false;

    if (algo == 1) //au hasard parmis les min
    {
        if (colA - 1 >= 0 && !lit(getID(ligA, colA - 1))) //si case vide
        {
            setIdRobotA(getID(ligA, colA - 1)); //je déplace A vers la case voisine

            dist = distMin(getIdRobotA(), getIdRobotB()); // je calcule ma distance min

            distmin = dist; // j'initialise distmin

            IDs[comp++] = getIdRobotA(); //je mets l'id de cette case dans mon tableau
        }
        if (colA + 1 < nbcol && !lit(getID(ligA, colA + 1)))
        {
            setIdRobotA(getID(ligA, colA + 1));

            dist = distMin(getIdRobotA(), getIdRobotB());

            if (dist < distmin || distmin == -1) //le distmin==0 sert si aucun if n'a été lancé
            {
                distmin = dist;
                comp = 0;
                IDs[comp++] = getIdRobotA(); //distance minimal donc je mets dans mon tableau mon nouvel id à la place de l'id d'avant
            }
            else if (dist == distmin)
                IDs[comp++] = getIdRobotA(); //sinon si la distance minimal est égale à celle d'avant je rajoute dans mon tableau cet id à celui d'avant
        }
        if (ligA - 1 >= 0 && !lit(getID(ligA - 1, colA)))
        {
            setIdRobotA(getID(ligA - 1, colA));

            dist = distMin(getIdRobotA(), getIdRobotB());

            if (dist < distmin || distmin == -1)
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

            if (dist < distmin || distmin == -1)
            {
                distmin = dist;
                comp = 0;
                IDs[comp++] = getIdRobotA();
            }
            else if (dist == distmin)
                IDs[comp++] = getIdRobotA();
        }

        setIdRobotA(IDs[rand() % comp]); //je prends une id au hasard parmi ceux qui ont la même distance entre A et B.
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
    }
    return true;
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
    int distmax;

    if (getIdRobotA() == getIdRobotB())
        return false;

    if (algo == 1) //random proie
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
        { //je prends toujours la distance minimal la plus grande entre les 5 cases potentiels possible (case B et ses 4 voisines)
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
///////////////////////////////////////
/////CONTRIBUTION PERSONNELLE//////////
///////////////////////////////////////
//Renvoie true si y'a un robot poursuivi dans la case getID(ligne,colonne) false dans le cas contraire
bool Laby::casePriseAmi(int ligne, int colonne)
{
    int id = getID(ligne, colonne);
    if (id == getIdRobotE() || id == getIdRobotF() || id == getIdRobotG() || id == getIdRobotH())
        return true;
    return false;
}
//Renvoie true si y'a un robot poursuivant dans la case getID(ligne,colonne) false dans le cas contraire
bool Laby::casePriseEnnemy(int ligne, int colonne)
{
    int id = getID(ligne, colonne);
    if (id == getIdRobotA() || id == getIdRobotB() || id == getIdRobotC() || id == getIdRobotD())
        return true;
    return false;
}

//Methode pour gérer l'affichage pour le labyrinthe et les 8 robots
void Laby::visualisationJeu()
{
    // Les robots sont placés dans la grille avant l'affichage

    modifie(getIdRobotA(), 2);

    if (getIdRobotB() != -1)
        modifie(getIdRobotB(), 3);

    if (getIdRobotC() != -1)
        modifie(getIdRobotC(), 4);
    if (getIdRobotD() != -1)
        modifie(getIdRobotD(), 5);
    if (getIdRobotE() != -1)
        modifie(getIdRobotE(), 6);
    if (getIdRobotF() != -1)
        modifie(getIdRobotF(), 7);
    if (getIdRobotG() != -1)
        modifie(getIdRobotG(), 8);
    if (getIdRobotH() != -1)
        modifie(getIdRobotH(), 9);

    system("clear");
    afficheJeu();

    // Les robots sont retirés de la grille pour ne pas perturber la recherche de chemins
    // optimaux par la méthode distMin.
    modifie(getIdRobotA(), 0);
    modifie(getIdRobotB(), 0);
    modifie(getIdRobotC(), 0);
    modifie(getIdRobotD(), 0);
    modifie(getIdRobotE(), 0);
    modifie(getIdRobotF(), 0);
    modifie(getIdRobotG(), 0);
    modifie(getIdRobotH(), 0);
}
//Renvoie une case random VIDE et NON prise par un autre robot
int Laby::caseRandomjeu()
{
    int caserd = rand() % (getNbLignes() * getNbColonnes());
    while (lit(caserd) == 1 || caserd == getIdRobotA() || caserd == getIdRobotB() || caserd == getIdRobotC() || caserd == getIdRobotD() || caserd == getIdRobotE() || caserd == getIdRobotF() || caserd == getIdRobotG() || caserd == getIdRobotH())
    {
        caserd = rand() % (getNbLignes() * getNbColonnes());
    }
    return caserd;
}
//Renvoie true si tous les robots poursuivis ont été attrapés, false dans le cas contraire
bool Laby::lesRobotsmorts()
{
    if (getIdRobotE() == -1 && getIdRobotF() == -1 && getIdRobotG() == -1 && getIdRobotH() == -1)
        return true;
    return false;
}
//Méthode qui gére le jeu
int Laby::monJeu(int timeout, bool silent, bool random)
{
    int nbEtapes = 0;
    if (random)
    { // Course avec positions initiales des robots aléatoire
        idRobotB = caseRandomjeu();
        idRobotA = caseRandomjeu();
        idRobotC = caseRandomjeu();
        idRobotD = caseRandomjeu();
        idRobotE = caseRandomjeu();
        idRobotF = caseRandomjeu();
        idRobotG = caseRandomjeu();
        idRobotH = caseRandomjeu();
    }
    else
    { // Course avec départ dans les coins opposés.
        idRobotA = getID(0, 0);
        idRobotH = getID(getNbLignes() - 1, getNbColonnes() - 1);
        idRobotC = caseRandomjeu();
        idRobotD = caseRandomjeu();
        idRobotE = caseRandomjeu();
        idRobotB = caseRandomjeu();
        idRobotF = caseRandomjeu();
        idRobotG = caseRandomjeu();
    }
    while (nbEtapes < timeout && !lesRobotsmorts())
    {

        if (!silent)
        { // Délai et affichage seulement si on est pas en mode silencieux
            synchro(0.1);
            visualisationJeu();
        }
        printf("UP:'z' DOWN:'s' RIGHT:'q' LEFT:'d'\n");
        printf("Il vous reste %d Déplacement(s), Votre Déplacement : \n", timeout - nbEtapes);
        deplacerRobotEnnemy(getIdRobotA(), idRobotAmiPlusProche(getIdRobotA()));
        if (!lesRobotsmorts())
            deplacerRobotEnnemy(getIdRobotB(), idRobotAmiPlusProche(getIdRobotB()));
        if (!lesRobotsmorts())
            deplacerRobotEnnemy(getIdRobotC(), idRobotAmiPlusProche(getIdRobotC()));
        if (!lesRobotsmorts())
            deplacerRobotEnnemy(getIdRobotD(), idRobotAmiPlusProche(getIdRobotD()));

        if (getIdRobotE() != -1)
            deplacerRobotAmi(getIdRobotE(), idRobotEnnemyPlusProche(getIdRobotE()));
        if (getIdRobotF() != -1)
            deplacerRobotAmi(getIdRobotF(), idRobotEnnemyPlusProche(getIdRobotF()));
        if (getIdRobotG() != -1)
            deplacerRobotAmi(getIdRobotG(), idRobotEnnemyPlusProche(getIdRobotG()));
        if (getIdRobotH() != -1)
            deplacerRobotJoueur(getIdRobotH());

        nbEtapes++;
    }
    if (!silent)
    { // Délai et affichage seulement si on est pas en mode silencieux
        synchro(0.1);
        visualisationJeu();
    }
    return nbEtapes;
}
//Déplace un robot poursuivi vers une case permettant de maximiser la distance avec le robot idRobot2
void Laby::deplacerRobotAmi(int idRobot, int idRobot2)
{
    int colR = getCol(idRobot);
    int ligR = getLigne(idRobot);
    int nblig = getNbLignes();
    int nbcol = getNbColonnes();
    int distmax = distMin(idRobot2, idRobot);
    int idtemp = idRobot;

    if (colR - 1 >= 0 && !lit(getID(ligR, colR - 1)) && distmax < distMin(getID(ligR, colR - 1), idRobot2) && !casePriseAmi(ligR, colR - 1))
    { //je prends toujours la distance minimal la plus grande entre les 5 cases potentiels possible (case B et ses 4 voisines)
        idtemp = getID(ligR, colR - 1);

        distmax = distMin(idtemp, idRobot2);
    }
    if (colR + 1 < nbcol && !lit(getID(ligR, colR + 1)) && distmax < distMin(getID(ligR, colR + 1), idRobot2) && !casePriseAmi(ligR, colR + 1))
    {
        idtemp = getID(ligR, colR + 1);
        distmax = distMin(idtemp, idRobot2);
    }
    if (ligR - 1 >= 0 && !lit(getID(ligR - 1, colR)) && distmax < distMin(getID(ligR - 1, colR), idRobot2) && !casePriseAmi(ligR - 1, colR))
    {
        idtemp = getID(ligR - 1, colR);
        distmax = distMin(idtemp, idRobot2);
    }
    if (ligR + 1 < nblig && !lit(getID(ligR + 1, colR)) && distmax < distMin(getID(ligR + 1, colR), idRobot2) && !casePriseAmi(ligR + 1, colR))
    {
        idtemp = getID(ligR + 1, colR);
        distmax = distMin(idtemp, idRobot2);
    }

    if (idRobot == getIdRobotE())
        setIdRobotE(idtemp);
    else if (idRobot == getIdRobotF())
        setIdRobotF(idtemp);
    else if (idRobot == getIdRobotG())
        setIdRobotG(idtemp);
}
//Déplace un robot poursuivant vers une case permettant de minimiser la distance avec le robot idRobot2
void Laby::deplacerRobotEnnemy(int idRobot, int idRobot2)
{
    int nbcol = getNbColonnes();
    int nblig = getNbLignes();
    int col = getCol(idRobot);
    int lig = getLigne(idRobot);
    int idbeforemodif = getID(lig, col);
    int IDs[4] = {0};
    int comp = 0;

    int distmin = nblig * nbcol;
    int dist;

    if (col - 1 >= 0 && !lit(getID(lig, col - 1)) && !casePriseEnnemy(lig, col - 1)) //si case vide
    {

        idRobot = getID(lig, col - 1);
        dist = distMin(idRobot, idRobot2); // je calcule ma distance min

        if (dist < distmin) //distance minimal donc je mets dans mon tableau mon nouvel id à la place de l'id d'avant
        {
            distmin = dist;
            comp = 0;
            IDs[comp++] = idRobot;
        }
        else if (dist == distmin)
            IDs[comp++] = idRobot; //sinon si la distance minimal est égale à celle d'avant je rajoute dans mon tableau cet id à celui d'avant
    }
    if (col + 1 < nbcol && !lit(getID(lig, col + 1)) && !casePriseEnnemy(lig, col + 1))
    {
        idRobot = getID(lig, col + 1);
        dist = distMin(idRobot, idRobot2);

        if (dist < distmin)
        {
            distmin = dist;
            comp = 0;
            IDs[comp++] = idRobot; //distance minimal donc je mets dans mon tableau mon nouvel id à la place de l'id d'avant
        }
        else if (dist == distmin)
            IDs[comp++] = idRobot; //sinon si la distance minimal est égale à celle d'avant je rajoute dans mon tableau cet id à celui d'avant
    }
    if (lig - 1 >= 0 && !lit(getID(lig - 1, col)) && !casePriseEnnemy(lig - 1, col))
    {
        idRobot = getID(lig - 1, col);
        dist = distMin(idRobot, idRobot2);

        if (dist < distmin)
        {
            distmin = dist;
            comp = 0;
            IDs[comp++] = idRobot;
        }
        else if (dist == distmin)
            IDs[comp++] = idRobot;
    }
    if (lig + 1 < nblig && !lit(getID(lig + 1, col)) && !casePriseEnnemy(lig + 1, col))
    {
        idRobot = getID(lig + 1, col);
        dist = distMin(idRobot, idRobot2);

        if (dist < distmin)
        {
            distmin = dist;
            comp = 0;
            IDs[comp++] = idRobot;
        }
        else if (dist == distmin)
            IDs[comp++] = idRobot;
    }

    if (comp == 0)
    {
        if (getIdRobotA() == idbeforemodif)
            setIdRobotA(idbeforemodif);
        else if (getIdRobotB() == idbeforemodif)
            setIdRobotB(idbeforemodif);
        else if (getIdRobotC() == idbeforemodif)
            setIdRobotC(idbeforemodif);
        else if (getIdRobotD() == idbeforemodif)
            setIdRobotD(idbeforemodif);
    }

    else
    {
        if (getIdRobotA() == idbeforemodif)
            setIdRobotA(IDs[rand() % comp]);
        else if (getIdRobotB() == idbeforemodif)
            setIdRobotB(IDs[rand() % comp]);
        else if (getIdRobotC() == idbeforemodif)
            setIdRobotC(IDs[rand() % comp]);
        else if (getIdRobotD() == idbeforemodif)
            setIdRobotD(IDs[rand() % comp]);
    } //je prends une id au hasard parmi ceux qui ont la même distance entre le robot poursuivant et le robot poursuivi le plus proche.
    if ((getIdRobotA() == getIdRobotE()) || (getIdRobotB() == getIdRobotE()) || (getIdRobotC() == getIdRobotE()) || (getIdRobotD() == getIdRobotE()))
        setIdRobotE(-1);
    else if ((getIdRobotA() == getIdRobotF()) || (getIdRobotB() == getIdRobotF()) || (getIdRobotC() == getIdRobotF()) || (getIdRobotD() == getIdRobotF()))
        setIdRobotF(-1);
    else if ((getIdRobotA() == getIdRobotG()) || (getIdRobotB() == getIdRobotG()) || (getIdRobotC() == getIdRobotG()) || (getIdRobotD() == getIdRobotG()))
        setIdRobotG(-1);
    else if ((getIdRobotA() == getIdRobotH()) || (getIdRobotB() == getIdRobotH()) || (getIdRobotC() == getIdRobotH()) || (getIdRobotD() == getIdRobotH()))
        setIdRobotH(-1);
}
//Renvoie l'id du robot poursuivant(entre A B C D) le plus proche avec l'idRobot
int Laby::idRobotEnnemyPlusProche(int idRobot)
{
    int nblig = getNbLignes();
    int nbcol = getNbColonnes();
    int distmin[4] = {nblig * nbcol, nblig * nbcol, nblig * nbcol, nblig * nbcol};
    int IDs[4] = {0};

    distmin[0] = distMin(idRobot, getIdRobotA());

    distmin[1] = distMin(idRobot, getIdRobotB());

    distmin[2] = distMin(idRobot, getIdRobotC());

    distmin[3] = distMin(idRobot, getIdRobotD());

    int min = distmin[0];
    int i = 0;
    while (i < 4)
    {
        if (min > distmin[i])
        {
            min = distmin[i];
        }
        i++;
    }
    i = 0;
    if (min == distmin[0])
        IDs[i++] = getIdRobotA();
    if (min == distmin[1])
        IDs[i++] = getIdRobotB();
    if (min == distmin[2])
        IDs[i++] = getIdRobotC();
    if (min == distmin[3])
        IDs[i++] = getIdRobotD();

    return IDs[rand() % i];
}
//Renvoie l'id du robot poursuivi (entre E F G H)le plus proche avec idRobot
int Laby::idRobotAmiPlusProche(int idRobot)
{
    int nblig = getNbLignes();
    int nbcol = getNbColonnes();
    int distmin[4] = {nblig * nbcol, nblig * nbcol, nblig * nbcol, nblig * nbcol};
    int IDs[4] = {0};

    if (getIdRobotE() != -1)
        distmin[0] = distMin(idRobot, getIdRobotE());
    if (getIdRobotF() != -1)
        distmin[1] = distMin(idRobot, getIdRobotF());
    if (getIdRobotG() != -1)
        distmin[2] = distMin(idRobot, getIdRobotG());
    if (getIdRobotH() != -1)
        distmin[3] = distMin(idRobot, getIdRobotH());

    int min = distmin[0];
    int i = 0;
    while (i < 4)
    {
        if (min > distmin[i])
        {
            min = distmin[i];
        }
        i++;
    }
    i = 0;
    if (getIdRobotE() != -1 && min == distmin[0])
        IDs[i++] = getIdRobotE();
    if (getIdRobotF() != -1 && min == distmin[1])
        IDs[i++] = getIdRobotF();
    if (getIdRobotG() != -1 && min == distmin[2])
        IDs[i++] = getIdRobotG();
    if (getIdRobotH() != -1 && min == distmin[3])
        IDs[i++] = getIdRobotH();
    //printf("salut %d %d\n",idRobot,min);
    return IDs[rand() % i];
}
//Méthode pour déplacer le robot H par l'utilisateur (C'est un robot poursuivi)
void Laby::deplacerRobotJoueur(int idRobot)
{
    string dep;
    cin >> dep;
    int ligH = getLigne(getIdRobotH());
    int colH = getCol(getIdRobotH());

    if (dep[0] == 'z' && ligH - 1 >= 0 && !lit(ligH - 1, colH) && !casePriseAmi(ligH - 1, colH))
    {
        setIdRobotH(getID(ligH - 1, colH));
    }
    else if (dep[0] == 's' && ligH + 1 < getNbLignes() && !lit(ligH + 1, colH) && !casePriseAmi(ligH + 1, colH))
    {
        setIdRobotH(getID(ligH + 1, colH));
    }
    else if (dep[0] == 'q' && colH - 1 >= 0 && !lit(ligH, colH - 1) && !casePriseAmi(ligH, colH - 1))
    {
        setIdRobotH(getID(ligH, colH - 1));
    }
    else if (dep[0] == 'd' && colH + 1 < getNbColonnes() && !lit(ligH, colH + 1) && !casePriseAmi(ligH, colH + 1))
    {
        setIdRobotH(getID(ligH, colH + 1));
    }

    if (getIdRobotA() == getIdRobotH())
        setIdRobotH(-1);
    else if (getIdRobotB() == getIdRobotH())
        setIdRobotH(-1);
    else if (getIdRobotC() == getIdRobotH())
        setIdRobotH(-1);
    else if (getIdRobotD() == getIdRobotH())
        setIdRobotH(-1);
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

    Laby laby(40, 70, 0.9);

    int duree = laby.course(dureeMax, false, true, 1, 2);

    if (duree > dureeMax)
    {
        cout << "Succes apres " << dureeMax << " etapes" << endl;
    }
    else
    {
        cout << "Echec apres " << duree << " etapes" << endl;
    }
}

void testEval()
{
    Laby laby(descripteur2);

    int score = laby.evalue(100, 100, 1, 2);

    cout << "Mediane : " << score << endl;
}
void Jeu(int lig, int col, double density, int dureem)
{
    int dureeMax = dureem;
    string c;
    Laby laby(lig, col, density);
    printf("Début du jeu de Poursuite, Vous jouerez le robot H et vous serez poursuivis par 4 autres robots : Vous avez %d Déplacement(s)\nVous Avez 3 Robots Alliés et 4 Ennemis\nAppuyez sur une touche pour commencer\n", dureeMax);
    while (cin >> c && c[0] == 0)
        ;

    int duree = laby.monJeu(dureeMax, false, true);

    if (duree >= dureeMax)
    {
        cout << "Succes apres " << dureeMax << " etapes" << endl;
    }
    else
    {
        cout << "Echec apres " << duree << " etapes" << endl;
    }
}
void testJeu()
{
    int dureeMax;
    int ligne, colonne;
    double density;
    cout << "Donnez le nombre de ligne de votre labyrinthe: ";
    cin >> ligne;
    cout << endl;
    cout << "Donnez le nombre de colonne de votre labyrinthe: ";
    cin >> colonne;
    cout << endl;
    cout << "Donnez la densitée de cases blanches de votre labyrinthe entre 0 et 1 (0 = Un labyrinthe Rempli de mur, 1 = Un labyrinthe sans mur)(Il faut un labyrinthe avec au moins 8 cases vides pour les robots): ";
    cin >> density;
    cout << endl;
    cout << "Donnez le nombre de déplacement autorisés avant que la partie se finisse (par une défaite si les 4 robots rouges gagnent ou une victoire dans l'autre cas): ";
    cin >> dureeMax;
    cout << endl;
    Jeu(ligne, colonne, density, dureeMax);
}
void testdistmin()
{
    Laby L(10, 10, 0.9);
    int A = L.caseRandom();
    int B = L.caseRandom();
    L.affiche();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = L.caseRandom();
    B = L.caseRandom();
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = 0;
    B = L.getNbColonnes() * L.getNbLignes() - 1;
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
    A = 0;
    B = 0;
    printf("Dist entre %d et %d = %d\n", A, B, L.distMin(A, B));
}

int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    

    //testdistmin();
    

    testJeu();
    return 0;
}
