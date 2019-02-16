#ifndef LIST_H
#define LIST_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "node.h"
#include "node.cpp"

using namespace std;

template <class Jugador>

class List
{
    public:
        List();
        ~List();

        //Operacions basiques de la llista
        void afageixNode(Jugador infoNou);
        void esborraLlista();

        void mostraLlista();
        void ordenaLlista();
        bool esBuida();

        //Arxius
        void cargarArxiu(string file);
        void guardarArxiu(string file);

        //Necesari per el correcte funcionament
        void invertirLlista();
        void eliminaPos(int pos);

    private:
        Node<Jugador> *m_primer;
        int m_num_nodes;
};

#endif // LIST_H
