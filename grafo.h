#ifndef GRAFO_H
#define GRAFO_H


#include <iostream>
#include "lista.h"
#include "arista.h"

class Arista;

using namespace std;

class Grafo
{
public:
    bool dirigido;
    lista<Nodo*>* nodos;
    Grafo(bool isDirigido)
    {
        nodos = new lista<Nodo*>;
        dirigido = isDirigido;
    }
    bool estaNodo(Nodo* val)
    {
        bool founded = false;
        if(val == NULL)
            return founded;
        for(int i = 0; i < nodos->size(); i++)
        {
            if(nodos->get(i) == val)
                founded = true;
        }
        return founded;
    }
    int estaNodo(string name)
    {
        for(int i = 0; i < nodos->size(); i++)
        {
            if(nodos->get(i)->name == name)
                return i;
        }
        return -1;
    }
    void agregarNodo(Nodo* nuevo)
    {
        if(estaNodo(nuevo))
            return;
        nodos->push_back(nuevo);
    }
    Nodo* obtenerNodo(string name)
    {
        for(int i = 0; i < nodos->size(); i++)
        {
            if(nodos->get(i)->name == name)
                return nodos->get(i);
        }
        return NULL;
    }
    void agregarArista(Arista* nuevo)
    {
        if(estaNodo(nuevo->origen) && estaNodo(nuevo->destino) && !estaArista(nuevo->origen,nuevo->destino))
        {
            Nodo* origin = obtenerNodo(nuevo->origen->name);
            Nodo* dest = obtenerNodo(nuevo->destino->name);
            if(dirigido)
            {
                origin->aristas->push_back(nuevo);
            }
            else
            {
                origin->aristas->push_back(nuevo);
                dest->aristas->push_back(new Arista(dest,origin,nuevo->peso));    
            }
        }
    }
    void agregarArista(Nodo* origen,Nodo* destino,int peso)
    {
        Arista* nuevo = new Arista(origen,destino,peso);
        agregarArista(nuevo);
    }
    void agregarArista(string origen,string destino,int peso)
    {
        Nodo* origin = obtenerNodo(origen);
        Nodo* dest = obtenerNodo(destino);
        agregarArista(origin,dest,peso);
    }
    lista<Arista*>* hijosDe(Nodo* val)
    {
        lista<Arista*>* miLista = new lista<Arista*>;
        if(estaNodo(val) == true)
        {
            return val->aristas->clonar();
            
        }
        return miLista;
    }
     void eliminarNodo(Nodo* eliminar)
     {
         if(estaNodo(eliminar))
         {
             lista<Arista*>* conexiones = hijosDe(eliminar);
            for(int i = 0; i < nodos->size(); i++)
            {
                Nodo* actual = nodos->get(i);
                for(int m = 0; m < actual->aristas->size(); m++)
                {
                    Arista* current = actual->aristas->get(m);
                    if(current->origen == eliminar || current->destino == eliminar)
                    {
                        eliminarArista(current);
                    }
                }
                
            }
            
             nodos->eliminar(nodos->buscar(eliminar));    
         }
     }
    void printAll()
    {
        for(int i = 0; i < nodos->size(); i++)
        {
            Nodo* nodo = nodos->get(i);
            cout<<"\tAristas de "<<nodo->name<<endl;
            lista<Arista*>* hijosNodo = hijosDe(nodo);
            for(int m = 0; m < hijosNodo->size(); m++)
            {
                cout<<"\t\t"<<nodo->name<<"---->"<<hijosNodo->get(m)->destino->name<<endl;
            }
            
        }
        
    }
    void eliminarArista(Nodo* ori, Nodo* des)
    {
        if(estaNodo(ori) && estaNodo(des))
        {
            ori->aristas->remove(obtenerArista(ori,des));
        }
        
    }
    void eliminarArista(Arista* aris)
    {
        Nodo* ori = aris->origen;
        Nodo* des = aris->destino;
        eliminarArista(ori,des);
        
    }
    bool estaArista(Nodo* ori, Nodo* des)
    {
        if(dirigido)
        {
            if(obtenerArista(ori,des)!= NULL)
                return true;
        }
        else
        {
            if(obtenerArista(ori,des)!= NULL && obtenerArista(des,ori)!= NULL)
                return true;
        }
        return false;
    }
    Grafo* unir(Grafo* graf)
    {
        Grafo* nuevo = new Grafo(graf->dirigido);
        for(int i = 0; i < graf->nodos->size(); i++)
        {
            Nodo* act = graf->nodos->get(i);
            Nodo* nuev = new Nodo(act->name);
            nuev->aristas = act->aristas->clonar();
            nuevo->agregarNodo(nuev);
        }
        for(int i = 0; i < this->nodos->size(); i++)
        {
            Nodo* act = this->nodos->get(i);
            Nodo* nuev = new Nodo(act->name);
            nuev->aristas = act->aristas->clonar();
            nuevo->agregarNodo(nuev);
        }
        return nuevo;
    }
    Arista* obtenerArista(Nodo* ori, Nodo* des)
    {
        if(estaNodo(ori) && estaNodo(des))
        {
            lista<Arista*>* aristasHijos = hijosDe(ori);
            for(int i = 0; i < aristasHijos->size(); i++)
            {
                Arista* current = aristasHijos->get(i);
                if(current->destino == des && current->origen == ori)
                    return current;
            }
            
        }
        return NULL;
    }
    
};

#endif
