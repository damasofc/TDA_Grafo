#include <iostream>

#include "Utilities.h"


int main()
{
    Grafo* grafo = new Grafo(false);
    //Agregando Nodos
    grafo->agregarNodo(new Nodo("a"));
    grafo->agregarNodo(new Nodo("b"));
    grafo->agregarNodo(new Nodo("c"));
    grafo->agregarNodo(new Nodo("d"));
    //Agregando Aristas

    grafo->agregarArista("a","b",2);
    grafo->agregarArista("a","c",22);
    grafo->agregarArista("c","d",1);
    grafo->agregarArista("b","d",23);

    grafo->printAll();

    //Utility::BFS(grafo,grafo->obtenerNodo("b"));
    //Utility::dijkstra(grafo,grafo->obtenerNodo("d"));
    //int visitado[grafo->nodos->size()];
    //for(int i = 0; i < grafo->nodos->size(); i++)
    //{
    //    visitado[i] = 0;
    //}
    //cout<<"\t\tDFS:"<<endl;
    //Utility::DFS(grafo,grafo->obtenerNodo("c"),visitado);
    //Utility::floydWarshall(grafo);

    Utility::kruskal(grafo);
    


    return 0;
}