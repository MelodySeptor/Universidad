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

        void add_end(Jugador data_);
        void del_all();
        void print();
        void sortt();
        void invert();

    private:
        Node<Jugador> *m_head;
        int m_num_nodes;
};

#endif // LIST_H
