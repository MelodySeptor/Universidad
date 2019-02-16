#include "node.h"

// Constructor por defecto
template<typename Jugador>

Node<Jugador>::Node()
{
    //data = NULL;
    data.nom[15];
    data.punts=0;
    next = NULL;
}

// Constructor por parámetro
template<typename Jugador>
Node<Jugador>::Node(Jugador data_)
{
    data.nom = data_.nom;
    data.punts = data.punts;
    next = NULL;
}

// Eliminar todos los Nodos
template<typename Jugador>
void Node<Jugador>::delete_all()
{
    if (next)
        next->delete_all();
    delete this;
}

// Imprimir un Nodo
template<typename Jugador>
void Node<Jugador>::print()
{
    cout << data.nom << "-> "<<data.punts<<endl;
}

template<typename Jugador>
Node<Jugador>::~Node() {}
