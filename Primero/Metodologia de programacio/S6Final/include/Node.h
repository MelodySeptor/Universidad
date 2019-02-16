#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

struct Jugador
{
    int punts =0;
    char nom[15] = "----------";
};

template <class Jugador>

class Node
{
    public:
        Node();
        ~Node();

        //Asi no creo el get y set
        Node *next;
        Jugador info;

        void deleteAll();
        void mostrar();
};

#endif // NODE_H
