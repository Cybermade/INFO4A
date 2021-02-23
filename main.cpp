#include <iostream>
#include "Labyrinthe.h"
#include <time.h>
using namespace std;
int main()
{   srand(time(0));
    cout<<"Debut Labyrinthe"<<endl;
    Labyrinthe L(10,50);
    L.affiche();
    
    cout<<endl;
    L.genLaby(300);



    L.affiche();
    
    
    
}