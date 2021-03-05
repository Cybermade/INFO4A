#include "Labyrinthe.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <math.h>
using namespace std;
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
    NB_LIGNES = nLignes;
    NB_COLONNES = nColonnes;
    Sommet = 0;

    Grille = new char[NB_LIGNES * NB_COLONNES];
    Pile = new int[NB_LIGNES * NB_COLONNES];

    for (int i = 0; i < NB_LIGNES * NB_COLONNES; i++)
        Grille[i] = 0;
    
}
Labyrinthe::Labyrinthe(char data[])
{
    NB_LIGNES = data[0];
    NB_COLONNES = data[1];
    Sommet = 0;

    Grille = new char[NB_LIGNES * NB_COLONNES];
    Pile = new int[NB_LIGNES * NB_COLONNES];

    for (int i = 0; i < (NB_LIGNES * NB_COLONNES); i++)
        Grille[i] = data[i + 2];
    Poursuite(0,99);
}
int Labyrinthe::getLongueur()
{
    return NB_LIGNES;
}
int Labyrinthe::getLargeur()
{
    return NB_COLONNES;
}
void Labyrinthe::affiche()
{

    for (int l = 0; l < NB_COLONNES + 2; l++)
    {
        putchar(AFF_BORD);
        putchar(' '); //BORD HAUT (on doit aller avant la premiere colonne jusqu'à une fois aprés la derniére c'est pour ça le l<NB_COLONNES+2)
    }
    printf("\n");
    for (int m = 0; m < NB_LIGNES; m++)
    {
        putchar(AFF_BORD);
        putchar(' '); //On commence le bord a gauche
        for (int l = 0; l < NB_COLONNES; l++)
        {
            if (lit(m, l)==1)
                 putchar(AFF_MUR); 
            else if(lit(m, l)==2)
                putchar(AFF_ROBOT_A); 
            else if(lit(m, l)==3)
                 putchar(AFF_ROBOT_B);
            else
                putchar(AFF_VIDE);
            putchar(' ');
        }

        printf("%c\n", AFF_BORD); //on termine a droite
    }
    for (int l = 0; l < NB_COLONNES + 2; l++)
    {
        putchar(AFF_BORD);
        putchar(' '); //BORD BAS
    }
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
char Labyrinthe::lit(int ligne, int colonne)
{
    return Grille[getID(ligne, colonne)];
}
void Labyrinthe::modifie(int ligne, int colonne, char x)
{
    Grille[getID(ligne, colonne)] = x;
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
        puts("Erreur Pas de cases blanches");
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
void Labyrinthe::push(int x)
{
    Pile[Sommet++] = x;
}
int Labyrinthe::pop()
{
    return Pile[--Sommet];
}
void Labyrinthe::genLaby(int k)
{
    int temp = 0, IDlast, IDAvantModif, temp3 = 0;
    int K = 0;
    IDlast = getID(NB_LIGNES - 1, NB_COLONNES - 1); // derniére case
    printf("Want %d\n", k);
    if (k > (NB_LIGNES * NB_COLONNES))
    {
        puts("\nPas possible d'avoir plus de cases blanches que le nombre de cases totale\n");
        exit(0);
    }
    k = k - 2;                       //j'enléve 2 du nombre voulu(première et derniére)
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

        temp = 0;
    }
    printf("Have %d\n", K + 2);
}
int Labyrinthe::distMin(int id1, int id2) //djikstra (l'algo que j'ai trouvé sur wikipedia avec quelques changements)
{   
    int D[NB_LIGNES * NB_COLONNES] = {0};//Distance
    int utilise[NB_LIGNES * NB_COLONNES] = {0};//Pile de l'algo de djisktra qui commence par un 0 et se termine quand on a tous les sommets(cases blanches ici)
    int Comp = 0, nbcasesb = 0, min = NB_LIGNES * NB_COLONNES;
    int idtemp;
    int l, c;
    
    
    for (int i = 0; i < NB_LIGNES * NB_COLONNES; i++)
    {
        if (!Grille[i])
        {
            D[i] = NB_LIGNES * NB_COLONNES;
            nbcasesb++;
            utilise[i] = 0;
        }
        else if(Grille[i]==1)
        {
            D[i] = -1;
            utilise[i] = -1;
        }
    }

    D[id1] = 0;

    while (nbcasesb != Comp)// tant qu'il y'a pas tous les sommets dans P
    {
        for (int i = 0; i < (NB_LIGNES * NB_COLONNES); i++)// je choisis un Sommet hors P avec la plus petite distance et je prends sa dist et son id
        { //hors de P veut dire utilise[i]==0
            if (D[i] != -1 && D[i] < min && !utilise[i])
            {
                min = D[i];
                idtemp = i;
            }
        }
        utilise[idtemp] = 1; //je le mets dans P 
        
        Comp++;// je rajoute 1 au compteur des cases blanches
        l = getLigne(idtemp);
        c = getCol(idtemp);
        //4 if comme suit 
        //  x        1       x
        //  3     idtemp     4 
        //  x        2       x
        // logique un sommet peut avoir au MAX 4 voisins
        if (l - 1 >= 0 && (D[getID(l - 1, c)] > (D[idtemp] + 1)) && !utilise[getID(l - 1, c)] )
            
            D[getID(l - 1, c)] = D[idtemp] + 1; 

        if (l + 1 < NB_LIGNES && (D[getID(l + 1, c)] > (D[idtemp] + 1)) && !utilise[getID(l + 1, c)] )
          
            D[getID(l + 1, c)] = D[idtemp] + 1; 

        if (c - 1 >= 0 && (D[getID(l, c - 1)] > (D[idtemp] + 1) )&& !utilise[getID(l, c - 1)])
          
            D[getID(l, c - 1)] = D[idtemp] + 1; 

        if (c + 1 < NB_COLONNES && (D[getID(l, c + 1)] > (D[idtemp] + 1)) && !utilise[getID(l, c + 1)])
           
            D[getID(l, c + 1)] = D[idtemp] + 1; 

        min = NB_LIGNES * NB_COLONNES;
    }
    

    return D[id2];
}
int Labyrinthe::AlgoRobotA(int idA,int idB)
{   
    int l=getLigne(idA);
    int c=getCol(idA);
    int distM=distMin(idA,idB);
    
    
    
    
    
    if(l-1>=0  && (lit(l-1,c)==0||lit(l-1,c)==3) && distM>distMin(getID (l-1,c) ,idB ))
        idA=getID (l-1,c);
    if(l+1<NB_LIGNES  && (lit(l+1,c)==0||lit(l+1,c)==3) && distM>distMin(getID (l+1,c) ,idB ))
        idA=getID (l+1,c);
    if(c-1>=0  && (lit(l,c-1)==0||lit(l,c-1)==3) && distM>distMin(getID (l,c-1) ,idB ))
        idA=getID (l,c-1);
    if(c+1<NB_COLONNES  && (lit(l,c+1)==0||lit(l,c+1)==3) && distM>distMin(getID (l,c+1) ,idB ))
        idA=getID (l,c+1);
    
    return idA;
    
        

}
int Labyrinthe::AlgoRobotB(int idA,int idB)
{  /* 
    int l=getLigne(idB);
    int c=getCol(idB);
    int templ;
    int tempc;
    int distM=distMin(idA,idB);*/
    int id=0;
    
    /*
    int i=rand()%3;
    while(!i)
    {   templ=(rand()%2)*(int)pow(-1,rand()%2);
        if(templ==0)
            tempc=(rand()%2)*(int)pow(-1,rand()%2);
        if(l+templ<NB_LIGNES && l+templ>=0 && c+tempc<NB_COLONNES && c+tempc>=0 && lit(l + templ,c + tempc)==0)
            {idB=getID(l+templ,c+tempc);
            i++;
            }
        printf("id %d",idB);
        if(i)
            return idB;
        
        tempc=0;
        templ=0;
        
    }
    */
    int comp=0;
    while(comp<NB_LIGNES*NB_COLONNES)
    {    if(lit(getLigne(comp),getCol(comp) )==0 && comp!=idA && comp!=idB )
        id=comp;
        comp=NB_LIGNES*NB_COLONNES;
    }

    
    
    for(int j=0;j<NB_LIGNES*NB_COLONNES;j++)
    {   
        if(lit(getLigne(j),getCol(j) )==0 && distMin(j,idB)<=distMin(j,idA) && distMin(idB,idA)<=distMin(j,idB))
        {      
            id=j;
            
        }
    }
            

    
    return AlgoRobotA(idB,id);
   


}
void Labyrinthe::Poursuite(int idA,int idB)
{   
    int idtempA=idA;
    int idtempB=idB;
    int i=0;
    puts("DEBUT POURSUITE A TO B");
    Sleep(1000);
    system("cls");
    while(idA!=idtempB && i<1000)
   {

    modifie(getLigne(idA),getCol(idA),2);
    modifie(getLigne(idB),getCol(idB),3);
    
    affiche();

    modifie(getLigne(idA),getCol(idA),0); 
    modifie(getLigne(idB),getCol(idB),0); 
     
    
    idtempA=idA;
    idtempB=idB; 

    idA=AlgoRobotA(idtempA,idtempB);
    
    idB=AlgoRobotB(idtempA,idtempB);
    

    
    modifie(getLigne(idtempA),getCol(idtempA),0);
    modifie(getLigne(idtempB),getCol(idtempB),0);
    
    Sleep(1000);
    system("cls");
   
    
    
    i++;
   }
    modifie(getLigne(idtempA),getCol(idtempA),0);
    
    modifie(getLigne(idA),getCol(idA),2);
    
    affiche();
    cout<<endl<<"END AFTER "<<i<<" TOURS";
    puts("\nCOURSE POURSUITE END\n");

    
}
Labyrinthe::~Labyrinthe()
{
    delete[] Grille;
    delete[] Pile;
    cout << endl << "Delete completed";
}
