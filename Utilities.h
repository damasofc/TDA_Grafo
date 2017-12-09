#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include "grafo.h"

class Utility
{
public:
    static Nodo* nodoDistMinima(Nodo* origen,int visitados[],lista<Nodo*>* vertices)
    {
        lista<Arista*>* aristasHijas = origen->aristas;
        int distanciaMin = 40000;
        Nodo* regreso = origen;
        Nodo* ori;
        Nodo* destino;
        for(int i = 0; i < aristasHijas->size(); i++)
        {
            Arista* current = aristasHijas->get(i);
            ori = current->origen;
            destino = current->destino;
            int posOri = vertices->buscar(ori);
            int posDest = vertices->buscar(destino);
            if((visitados[posDest] == 0) && (current->peso < distanciaMin))
            {
                distanciaMin = current->peso;
                regreso = destino;
            }
        }
        return regreso;
    }
    static Grafo* dijkstra(Grafo* graf,Nodo* origen)
    {
        Grafo* nuevoGrafo = new Grafo(graf->dirigido);
        if(graf->hijosDe(origen)->size() <= 0)
            return nuevoGrafo;
        //inicializacion
        lista<Nodo*>* vertices = graf->nodos->clonar();
        int posOrigen = vertices->buscar(origen);
        int visitado[vertices->size()];
        int pesos[vertices->size()];
        for(int i = 0; i < vertices->size(); i++)
        {
            pesos[i] = 1000;
            visitado[i] = 0;
        }
        //1 significa true 
        //0 significa false
        visitado[posOrigen] = 1;
        pesos[posOrigen] = 0;
        //fin inicializacion
        Nodo* actual = origen;
        bool continuar = true;
        while(continuar)
        {

            visitado[vertices->buscar(actual)] = 1;

            for(int m = 0; m < graf->hijosDe(actual)->size(); m++)
            {
                Arista* act = graf->hijosDe(actual)->get(m);
                Nodo* ady = act->destino;
                int w = act->peso;
                //REALAJAR
                int posActual = vertices->buscar(actual);
                int posAdy = vertices->buscar(ady);
                if((pesos[posActual] + w) < (pesos[posAdy]))
                {
                    pesos[posAdy] = pesos[posActual] + w;

                }

                //FIN RELAJAR
            }

            //COMPROBAR QUE ESTEN VISITADOS
            int cont = 0;
            for(int r = 0; r < vertices->size(); r++)
            {
                if(visitado[r] == 1)
                {
                    cont++;
                }

            }
            if(cont >= vertices->size())
            {
                continuar = false;
            }
            else
            {
                actual = nodoDistMinima(actual,visitado,vertices);
            }
            //FIN COMPROBAR QUE ESTEN VISITADOS
        }
        //return nuevoGrafo;
        //final regresar todo en forma de grafo
        int posN = 0;
        for(int i = 0; i < vertices->size(); i++)
        {
            Nodo* current = vertices->get(i);
            Nodo* nuevo = new Nodo(current->name);
            nuevoGrafo->agregarNodo(nuevo);
            if(nuevo->name == origen->name)
                posN = i;
        }
        Nodo* introd = nuevoGrafo->nodos->get(posN);
        cout<<"\t\tDIJKSTRA:"<<endl;
        for(int s = 0; s < nuevoGrafo->nodos->size(); s++)
        {
            if(introd == nuevoGrafo->nodos->get(s))
                continue;
            introd->aristas->push_back(new Arista(introd,nuevoGrafo->nodos->get(s),pesos[s]));
            cout<<"\t\t\tEL camino desde: "<<introd->name<<" hasta: "<<nuevoGrafo->nodos->get(s)->name
                <<" es de peso: "<<pesos[s]<<endl;
        }
        return nuevoGrafo;
    }

    static void DFS(Grafo* graf,Nodo* origin, int visitados[])
    {
        visitados[graf->nodos->buscar(origin)] = 1;
        for(int i = 0; i < graf->hijosDe(origin)->size(); i++)
        {
            Arista* actual = graf->hijosDe(origin)->get(i);
            if(visitados[graf->nodos->buscar(actual->destino)] == 0)
            {
                cout<<"\t\t\t"<<actual->destino->name<<"---Padre: "<<origin->name<<endl;
                DFS(graf,actual->destino,visitados);
            }
        }

    }
    static void BFS(Grafo* graf,Nodo* origin)
    {
        lista<Nodo*>* vertices = graf->nodos->clonar();
        lista<Nodo*> niveles[10];
        int visitados[vertices->size()];
        for(int i = 0; i < 10; i++)
        {
            niveles[i] = lista<Nodo*>();
        }

        for(int i = 0; i < vertices->size(); i++)
        {
            visitados[i] = 0;
        }
        Nodo* actual = origin;
        bool continuar = true;
        int level = 0;
        niveles[level].push_back(actual);
        while(continuar)
        {
            int posBuscar = -1;
            level++;
            visitados[vertices->buscar(actual)] = 1;
            for(int m = 0; m < graf->hijosDe(actual)->size(); m++)
            {
                Arista* act = graf->hijosDe(actual)->get(m);
                Nodo* ady = act->destino;
                if(visitados[vertices->buscar(ady)] == 0)
                {
                    visitados[vertices->buscar(ady)] = 1;
                    niveles[level].push_back(ady);
                    posBuscar = vertices->buscar(ady);
                }
            }
            //COMPROBAR QUE ESTEN VISITADOS
            int cont = 0;
            for(int r = 0; r < vertices->size(); r++)
            {
                if(visitados[r] == 1)
                {
                    cont++;
                }

            }
            if(cont >= vertices->size())
            {
                continuar = false;
            }
            else
            {
                actual = vertices->get(posBuscar);
            }
            //FIN COMPROBAR QUE ESTEN VISITADOS
        }

        //Imprimir valores
        cout << "\t\tBFS NIVELES:"<<endl;
        for(int i = 0; i < 10; i++)
        {
            lista<Nodo*> nodos = niveles[i];
            if(nodos.size() <= 0)
                continue;
            cout<<"\t\t\tNivel "<<i<<endl;
            for(int j = 0; j < nodos.size(); j++)
            {
                Nodo* actual = nodos.get(j);
                cout<<"\t\t\t\t"<<actual->name<<endl;
            }

        }
    
    }

    static bool existeCamino(Nodo* desde,Nodo* hasta)
    {
        lista<Arista*>* aristas = desde->aristas;
        for(int i = 0; i < aristas->size(); i++)
        {
            Arista* current = aristas->get(i);
            if(current->origen == desde && current->destino == hasta)
                return true;
        }
        return false;

    }
    static Grafo* floydWarshall(Grafo* graf)
    {
        Grafo* nuevoGrafo = new Grafo(graf->dirigido);
        lista<Nodo*>* vertices = graf->nodos->clonar();
        //inicializacion
        int pesos[vertices->size()][vertices->size()];
        for(int i = 0; i < vertices->size(); i++)
        {
            Nodo* actualI = vertices->get(i);
            for(int j = 0; j < vertices->size(); j++)
            {
                Nodo* actualJ = vertices->get(j);
                Arista* agg = graf->obtenerArista(actualI,actualJ);
                if(agg!=NULL)
                {
                    pesos[i][j] = agg->peso; 
                }
                else
                {
                    pesos[i][j] = 10000;
                }
            }

        }
        //Warshall
        for(int i = 0; i < vertices->size(); i++)
        {
            Nodo* pivote = vertices->get(i);
            for(int j = 0; j < vertices->size(); j++)
            {
                Nodo* desde = vertices->get(j);
                for(int k = 0; k < vertices->size(); k++)
                {
                    Nodo* hasta = vertices->get(k);
                    if(existeCamino(desde,pivote) && existeCamino(pivote,hasta))
                    {
                        //FLOYD
                        if(pesos[j][i] + pesos[i][k] < pesos[j][k])
                        {
                            pesos[j][k] = pesos[j][i] + pesos[i][k];
                        }
                    }
                }

            }
        }
        //devolver todo como un Grafo
        nuevoGrafo->nodos = new lista<Nodo*>();
        for(int i = 0; i < vertices->size(); i++)
        {
            Nodo* current = vertices->get(i);
            Nodo* nuevo = new Nodo(current->name);
            nuevo->aristas = new lista<Arista*>();
            nuevoGrafo->agregarNodo(nuevo);
        }

        cout<<"\t\tFloyd-Warshall"<<endl;
        for(int i = 0; i < vertices->size(); i++)
        {
            Nodo* desde = nuevoGrafo->nodos->get(i);
            for(int j = 0; j < vertices->size(); j++)
            {
                Nodo* hasta = nuevoGrafo->nodos->get(j);
                if(i == j)
                    continue;
                if(pesos[i][j] == 10000)
                    continue;
                nuevoGrafo->agregarArista(new Arista(desde,hasta,pesos[i][j]));
                cout<<"\t\t\tEL camino desde: "<<desde->name<<" hasta: "<<hasta->name
                <<" es de peso: "<<pesos[j][i]<<endl;

            }

        }

        return nuevoGrafo;
    }
    static lista<Arista*>* sortMenorMayor(Grafo* graf)
    {
        lista<Arista*>* aristas = new lista<Arista*>();
        for(int i = 0; i < graf->nodos->size() ; i++)
        {
            Nodo* actual = graf->nodos->get(i);
            for(int m = 0; m < actual->aristas->size(); m++)
            {
                Arista* current = actual->aristas->get(m);
                if(aristas->buscar(current) == -1)
                {
                    //determinar en que posicion de la listas de aristas se colocara
                    if(aristas->size() == 0)
                    {
                        aristas->push_front(current);
                    }
                    else
                    {
                        bool insertado = false;
                        for(int s = 0; s < aristas->size(); s++)
                        {
                            Arista* temp = aristas->get(s);
                            if(current == temp)
                                continue;
                            if(current->peso <= temp->peso)
                            {
                                aristas->insertar(current,s);
                                insertado = true;
                                break;
                            }
                        }
                        if(!insertado)
                            aristas->push_back(current);
                        
                    }
                }
            }
            
        }
        return aristas;
        
    }
    static bool estaNodo(Nodo* nodo,Grafo* graf)
    {
        lista<Arista*>* aristas = new lista<Arista*>();
        for(int i = 0; i < graf->nodos->size(); i++)
        {
            Nodo* act = graf->nodos->get(i);
            for(int a = 0; a < act->aristas->size(); a++)
            {
                Arista* current = act->aristas->get(a);
                aristas->push_back(current);
            }
            
        }
        
        //comprueba si esta el nodo en este grafo
        for(int i = 0; i < aristas->size(); i++)
        {
            Arista* actual = aristas->get(i);
            if(actual->origen == nodo || actual->destino == nodo)
                return true;
        }
        return false;
    }
    static Grafo* kruskal(Grafo* graf)
    {
        Grafo* nuevo = new Grafo(graf->dirigido);
        lista<Nodo*>* vertices = graf->nodos->clonar();
        lista<Grafo*>* arboles = new lista<Grafo*>();
        lista<Arista*>* aristasRegreso = new lista<Arista*>();
        for(int i = 0; i < vertices->size(); i++)
        {
            arboles->push_back(new Grafo(graf->dirigido));
            arboles->get(i)->agregarNodo(vertices->get(i));
        }
        lista<Arista*>* temp = sortMenorMayor(graf);
        for(int i = 0; i < temp->size(); i++)
        {
            Arista* actual = temp->get(i);
            int posOrigen = vertices->buscar(actual->origen);
            int posDes = vertices->buscar(actual->destino);
            //chequiar que no se produzca un ciclo
            if(!estaNodo(actual->origen,arboles->get(posOrigen)) || !estaNodo(actual->destino,arboles->get(posDes)))
            {
                aristasRegreso->push_back(actual);
                arboles->get(posOrigen)->agregarArista(actual);
                arboles->get(posDes)->agregarArista(actual);

            }

            //comprobar que ya esten todos conectados
            int cont = 0 ;
            for(int a = 0; a < vertices->size(); a++)
            {
                
            }
            //if(cont>=vertices->size())
            //{
            //    
            //}
            
            
            
        }
        

        //imprimir
        cout<<"\t\tKRUSKAL"<<endl;
        for(int i = 0; i < aristasRegreso->size(); i++)
        {
            Arista* actual = aristasRegreso->get(i);
            cout<<"\t\t\tEL camino desde: "<<actual->origen->name<<" hasta: "<<actual->destino->name
                <<" es de peso: "<<actual->peso<<endl;
        }
        return nuevo;
    }

};

#endif 
