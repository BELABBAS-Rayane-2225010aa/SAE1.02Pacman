#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "Fichier_jeu/game.h"

using namespace std;
using namespace nsGraphics;
using namespace nsEvent;
using namespace nsShape;
using namespace chrono;

template <typename T>
void affichMat(const vector <vector<T>> & V)
{
    for (size_t i (0); i < V.size(); ++i)
    {
        for (const T & j : V[i])
            cout << j;
        cout << endl;
     }
}



int main()
{
    try
    {
        return ppal ();
    }
    catch (...)
    {
        cerr << "ca c'est mal passe quelque part" << endl;
        return 1;
    }
}
