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
        Node(Jugador data_);
        ~Node();

        Node *next;
        Jugador data;

        void delete_all();
        void print();
};

#endif // NODE_H
