//
// Created by diogo on 18/05/2021.
//

#ifndef PROJETO_CAL_GRAPH_H
#define PROJETO_CAL_GRAPH_H


#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <string>
#include <iterator>
#include <set>
using namespace std;

class Graph;
class Vertex;
class Edge;

class Vertex{
private:
    string importance;
    string name;
    vector<Edge*> outgoing_edges;
    double double_x;
    double double_y;

    Vertex *prev;  //auxiliary
    double dist;   //auxiliary
public:
    Vertex(string imp,double xx,double yy,string nam){
        importance=imp;
        double_x=xx;
        double_y=yy;
        name=nam;
    }
    void set_prev(Vertex * dis){
        prev=dis;
    }
    void set_dist(double distance){
        dist=distance;
    }

    string get_name(){
        return name;
    }
    double get_x(){
        return double_x;
    }
    double  get_y(){
        return double_y;
    }
    void add_edge(Edge * obj){
        outgoing_edges.push_back(obj);
    }
    vector<Edge*> get_outgoing_edges(){
        return outgoing_edges;
    }

    double get_dist(){
        return dist;
    }
};
class Edge{
private:
    double length;
    Vertex * destination_vertex;
public:
    Edge(Vertex * dest,double len){
        destination_vertex=dest;
        length=len;
    }
    double get_lenght(){
        return length;
    }

    Vertex * get_destiny_vertex(){
        return destination_vertex;
    }

};

class Graph{
private:
    vector<Vertex*> vertexes;
public:

    void fill_vector(Vertex * objeto){
        this->vertexes.push_back(objeto);
    }
    vector<Vertex*> get_vertexes(){
        return vertexes;
    }

    Vertex* get_vertex(int i){
        return vertexes[i];
    }

    void dijkstraShortestPath(Vertex * source);
};

void Graph::dijkstraShortestPath(Vertex * source) {
    vector<Vertex*> lista;

    for(auto x : get_vertexes()){   // percorre todos os vertices do grafo
        x->set_dist(INT_MAX);
        x->set_prev(NULL);
        lista.push_back(x);         // coloca na auxiliar todos os nodes percorridos
    }

    source->set_dist(0);    // dist do node inicial fica 0
    auto current = lista[0];
    while(!lista.empty()){
        int index=0;
        for(int a=1;a <lista.size();a++){
            if(lista[a]->get_dist()<current->get_dist()){
                index = a;
                current = lista[a];   // o node retirado da lista , o que tinha o dist menor
            }
        }
        lista.erase(lista.begin() + index);
    }
    for(int i =0 ; i<current->get_outgoing_edges().size();i++){
        double soma = current->get_dist() + current->get_outgoing_edges()[i]->get_lenght();
        if(soma<current->get_outgoing_edges()[i]->get_destiny_vertex()->get_dist()){
            current->get_outgoing_edges()[i]->get_destiny_vertex()->set_dist(soma);
            current->get_outgoing_edges()[i]->get_destiny_vertex()->set_prev(current);
        }
    }
}


#endif //PROJETO_CAL_GRAPH_H
