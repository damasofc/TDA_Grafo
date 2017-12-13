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
    grafo->agregarNodo(new Nodo("e"));
    grafo->agregarNodo(new Nodo("f"));
    //Agregando Aristas

    grafo->agregarArista("a","b",1);
    grafo->agregarArista("a","c",8);
    grafo->agregarArista("c","d",5);
    grafo->agregarArista("b","d",9);
    grafo->agregarArista("c","b",6);
    grafo->agregarArista("c","e",4);
    grafo->agregarArista("e","f",2);
    grafo->agregarArista("f","d",3);
    grafo->agregarArista("e","d",1);

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

    Utility::prim(grafo);

    Utility::kruskal(grafo);
    


    return 0;
}