#include "list.h"

using namespace std;

// Constructor
template<typename Jugador>
List<Jugador>::List()
{
    m_num_nodes = 0;
    m_primer = NULL;
}

// Afegeix un node al final de la llista
template<typename Jugador>
void List<Jugador>::afageixNode(Jugador infoNou)
{
     Node<Jugador> *new_node = new Node<Jugador>;
    strcpy(new_node->info.nom,infoNou.nom);
    new_node->info.punts = infoNou.punts;

    Node<Jugador> *temp = m_primer;

    if (!m_primer) {
        m_primer = new_node;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    m_num_nodes++;
}

// Eliminar la llista sencera
template<typename Jugador>
void List<Jugador>::esborraLlista()
{
    m_primer->deleteAll();
    m_primer = 0;
}

// Mostra la llista
template<typename Jugador>
void List<Jugador>::mostraLlista()
{
    Node<Jugador> *temp = m_primer;
    if (!m_primer) {
        cout << "No hi ha cap resultat " << endl;
    } else {
        while (temp) {
            temp->mostrar();
            if (!temp->next) cout << " ";
                temp = temp->next;
        }
  }
  cout << endl << endl;
}

// Ordena la llista de manera ascendent
template<typename Jugador>
void List<Jugador>::ordenaLlista()
{
    Jugador temp_data;
    Node<Jugador> *aux_node = m_primer;
    Node<Jugador> *temp = aux_node;

    while (aux_node) {
        temp = aux_node;

        while (temp->next) {
            temp = temp->next;

            if (aux_node->info.punts > temp->info.punts) {
                temp_data.punts = aux_node->info.punts;
                strcpy(temp_data.nom,aux_node->info.nom);

                aux_node->info = temp->info;
                temp->info = temp_data;
            }
        }

        aux_node = aux_node->next;
    }
}

// Inverteix la llista
template<typename Jugador>
void List<Jugador>::invertirLlista()
{
    Node<Jugador> *prev = NULL;
    Node<Jugador> *next = NULL;
    Node<Jugador> *temp = m_primer;

    while (temp) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    m_primer = prev;
}

//Carga una lista desde un arxiu
template<typename Jugador>
void List<Jugador>::cargarArxiu(string file)
{
    ifstream fileO;
    Jugador line;
    fileO.open(file);
    int i =0;
    if(fileO.is_open())
    {
        while(!fileO.eof())
        {
        fileO>> line.nom;
        fileO>> line.punts;
        afageixNode(line);
        i++;
        }

        eliminaPos(i);
    }
}


// Guarda la llista al arxiu
template<typename Jugador>
void List<Jugador>::guardarArxiu(string file)
{
    Node<Jugador> *temp = m_primer;
    ofstream out;
    out.open(file.c_str());

    if (!out.is_open()) {
        cout << "No se puede guardar el archivo " << endl;
    } else {
        while (temp!=NULL) {
            out << temp->info.nom<<endl;
            out << temp->info.punts<<endl;
            temp = temp->next;
        }
    }
    out.close();
}

// Elimina un node la la posicio pos
template<typename Jugador>
void List<Jugador>::eliminaPos(int pos)
{
    Node<Jugador> *temp = m_primer;
    Node<Jugador> *temp1 = temp->next;

    if (pos < 1 || pos > m_num_nodes) {
    } else if (pos == 1) {
        m_primer = temp->next;
    } else {
        for (int i = 2; i <= pos; i++) {
            if (i == pos) {
                Node<Jugador> *aux_node = temp1;
                temp->next = temp1->next;
                delete aux_node;
                m_num_nodes--;
            }
            temp = temp->next;
            temp1 = temp1->next;
        }
    }
}

//Mira si la llista es buida
template<typename Jugador>
bool List<Jugador>::esBuida()
{
    if(m_primer==NULL)
    {
        return true;
    }
    else
        return false;
}

//Destrucrtor
template<typename Jugador>
List<Jugador>::~List() {}
