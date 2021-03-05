#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

int NB_COLONNES = 30; //longueur
int NB_LIGNES = 20;   //largeur
char AFF_VIDE = '-'; //Caractère représentant les cases vides pour l’affichage
char AFF_MUR = 'X';  //Caractère représentant les murs pour l’affichage
char AFF_BORD = '0'; //Caractère représentant les bords pour l’affichage
char *Grille = NULL;
int *Pile=NULL;
int Sommet = 0;

int getID(int, int);
int getLigne(int);
int getCol(int);
void modifie(int, int, char);
char lit(int, int);
void affiche();
int pop();
void push(int);
int connexe();
void GenLaby(int);


void push(int x)
{
    Pile[Sommet++] = x;
}
int pop()
{
    return Pile[--Sommet];
}

int connexe()
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
    modifie( getLigne(id), getCol(id), 2) ;
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
            if (ligne + m >= 0 && ligne + m < NB_LIGNES && !(lit(ligne+m,colonne)))//lit(ligne+m,colonne)
            {
                modifie(ligne+m,colonne,2);
                push(getID(ligne + m, colonne));
            }
        }

        for (int l = -1; l < 2; l = l + 2) //on compare horizontalement
        {
            if (colonne + l >= 0 && colonne + l < NB_COLONNES && !(lit(ligne, colonne + l)))
            {
                modifie(ligne , colonne + l , 2);
                push(getID(ligne, colonne + l));
            }
        }
    }
    for (int m = 0; m < NB_LIGNES; m++)
    {
        for (int l = 0; l <  NB_COLONNES; l++)
        {
            if (lit(m,l) == 2)
            {   
                modifie(m,l,0);
                nbcasesm++;
            }
        }
    }
    if (nbcasesm == nbcasesb)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void GenLaby(int k) //backtrack simple
{
    int temp=0, IDlast, IDAvantModif, temp3 = 0;
    int K = 0;
    IDlast = getID(NB_LIGNES - 1, NB_COLONNES - 1); // derniére case

    if (k > (NB_LIGNES * NB_COLONNES))
    {
        printf("\nPas possible d'avoir plus de cases blanches que le nombre de cases totale\n");
        exit(0);
    }
    k = k - 2;     //j'enléve 2 du nombre voulu(première et derniére)
    K = NB_COLONNES * NB_LIGNES - 2; //j'enléve 2 du nombre totale de cases blanches(première et derniére)

    while (k != K && !(temp3 > (NB_COLONNES * NB_LIGNES)))
    {
        

        while (temp == 0 || temp == IDlast)
            temp = rand() % (NB_COLONNES * NB_LIGNES - 1); //je refais tant que j'ai une id de la premiere ou de la derniere case

        IDAvantModif = lit(getLigne(temp), getCol(temp)); //je prends la valeure de la case si elle était blanche(0) ou noire(1)

        modifie(getLigne(temp), getCol(temp), 1);

        if (connexe() && !IDAvantModif) //je test en ayant mit le case en noir si c'est toujours connexe et la case d'avant était bien blanche
        {
            K--; //car si je mets noir sur noir ça ne sert a rien
            temp3 = 0;
        }
        else if (!IDAvantModif)
        {
            modifie(getLigne(temp), getCol(temp), 0);

        } //si elle était blanche et je l'ai noircie mais elle était critique je reviens en arriére(Backtrack)

        else
            temp3++; //si je rentre dans la boucle et je fais rien je temp3++

        temp=0;       
            
    }
    printf("Have %d\n", K+2);
}

int getID(int ligne, int colonne)
{
    return ligne * NB_COLONNES + colonne;
}
int getLigne(int id)
{
    return id / NB_COLONNES;
}
int getCol(int id)
{
    return id % NB_COLONNES;
}
void modifie(int ligne, int colonne, char x)
{
    Grille[getID(ligne, colonne)] = x;
}
char lit(int ligne, int colonne)
{
    return Grille[getID(ligne, colonne)];
}
void affiche()
{
    for (int l = 0; l < NB_COLONNES + 2; l++)
        printf("%c ", AFF_BORD); //BORD HAUT (on doit aller avant la premiere colonne jusqu'à une fois aprés la derniére c'est pour ça le l<NB_COLONNES+2)
    
    printf("\n");
    for (int m = 0; m < NB_LIGNES; m++)
    {   printf("%c ", AFF_BORD);   //On commence le bord a gauche
        for (int l = 0; l < NB_COLONNES; l++)
        {
            if (lit(m, l))
                printf("%c ", AFF_MUR);
            else
                printf("%c ", AFF_VIDE);
        }
        
        printf("%c\n", AFF_BORD); //on termine a droite
    }
    for (int l = 0; l < NB_COLONNES + 2; l++)
        printf("%c ", AFF_BORD); //BORD BAS
}
int main()
{
    Grille = (char *)calloc(NB_LIGNES * NB_COLONNES, sizeof(char));
    Pile=(int *)calloc(NB_LIGNES * NB_COLONNES, sizeof(int));
    srand(time(NULL));
    int k=350;

    affiche();
    printf("\n");
    printf("Want %d\n", k);
    GenLaby(k);

    affiche();

    /*if (connexe())
        printf("\nC'est un Labyrinthe");
    else
        printf("\nnon");*/

    free(Grille);
    free(Pile);
    return 0;
}
