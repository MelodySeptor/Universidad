#include "node.h"

// Constructor
template<typename Jugador>

Node<Jugador>::Node()
{
    info.nom[15];
    info.punts=0;
    next = NULL;
}

// Eliminar un node
template<typename Jugador>
void Node<Jugador>::deleteAll()
{
    if (next)
        next->deleteAll();
    delete this;
}

// Mostrar un node
template<typename Jugador>
void Node<Jugador>::mostrar()
{
    cout << info.nom <<" --> "<<info.punts<<endl;
}

//Destructor
template<typename Jugador>
Node<Jugador>::~Node() {}
