#ifndef NODO_H
#define NODO_H

#include "lista.h"
#include "arista.h"

class Arista;
 

using namespace std;
class Nodo
{
public:
    lista<Arista*>* aristas;
    string name;
    Nodo(string nombre)
    {
        aristas = new lista<Arista*>;
        this->name = nombre;
    }
    bool operator==(Nodo* nodo)
    {
        if(this->name == nodo->name)
            return true;
        return false;
    }
};

#endif
