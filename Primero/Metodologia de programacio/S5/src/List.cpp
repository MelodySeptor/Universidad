#include "list.h"

using namespace std;

// Constructor por defecto
template<typename Jugador>
List<Jugador>::List()
{
    m_num_nodes = 0;
    m_head = NULL;
}

// Insertar al final
template<typename Jugador>
void List<Jugador>::add_end(Jugador data_)
{
     Node<Jugador> *new_node = new Node<Jugador>;
    strcpy(new_node->data.nom,data_.nom);
    new_node->data.punts = data_.punts;

    Node<Jugador> *temp = m_head;

    if (!m_head) {
        m_head = new_node;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    m_num_nodes++;
}

// Eliminar todos los nodos
template<typename Jugador>
void List<Jugador>::del_all()
{
    m_head->delete_all();
    m_head = 0;
}

// Imprimir la Lista
template<typename Jugador>
void List<Jugador>::print()
{
    Node<Jugador> *temp = m_head;
    if (!m_head) {
        cout << "No hi ha cap resultat " << endl;
    } else {
        while (temp) {
            temp->print();
            if (!temp->next) cout << " ";
                temp = temp->next;
        }
  }
  cout << endl << endl;
}

// Ordenar de manera ascendente
template<typename Jugador>
void List<Jugador>::sortt()
{
    Jugador temp_data;
    Node<Jugador> *aux_node = m_head;
    Node<Jugador> *temp = aux_node;

    while (aux_node) {
        temp = aux_node;

        while (temp->next) {
            temp = temp->next;

            if (aux_node->data.punts > temp->data.punts) {
                temp_data.punts = aux_node->data.punts;
                strcpy(temp_data.nom,aux_node->data.nom);

                aux_node->data = temp->data;
                temp->data = temp_data;
            }
        }

        aux_node = aux_node->next;
    }
}

// Invertir la lista
template<typename Jugador>
void List<Jugador>::invert()
{
    Node<Jugador> *prev = NULL;
    Node<Jugador> *next = NULL;
    Node<Jugador> *temp = m_head;

    while (temp) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    m_head = prev;
}

template<typename Jugador>
List<Jugador>::~List() {}
