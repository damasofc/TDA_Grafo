#ifndef ARISTA_H
#define ARISTA_H

#include <iostream>
#include "nodo.h"
#include <string>
#include <sstream>

using namespace std;

class Nodo;

class Arista
{
public:
    Nodo* origen;
    Nodo* destino;
    int peso;
    Arista(Nodo* origen, Nodo* destino,int peso)
    {
        this->origen = origen;
        this->destino = destino;
        this->peso = peso;
    }
    bool operator==(Arista* aris)
    {
        if((this->origen == aris->origen) && (this->destino == aris->destino) && (this->peso == aris->peso))
            return true;
        return false;
    }

};
#endif

