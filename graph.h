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
    int menuID;  // menu aux

    Vertex *prev;  //auxiliary
    double dist;   //auxiliary
public:

    Vertex(string imp,double xx,double yy,string nam){
        importance=imp;
        double_x=xx;
        double_y=yy;
        name=nam;
    }
    int set_menuID(int k){
        menuID=k;
    }

    int get_menuID(){
        return  menuID;
    }

    string get_importance(){
        return importance;
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
    vector<Vertex*> lista;            // criar lista com todos os nodes
    for(auto vertices : vertexes){     // percorrer todos os nodes e atualizar valores
        vertices->set_dist(INT_MAX);
        vertices->set_prev(NULL);
        lista.push_back(vertices);   // colocamos todos os nodes neste vetor
    }
    source->set_dist(0);

    while(!lista.empty()){                              // enquanto houver nodes na lista
        auto node = lista[0];                           // node é o node inicial
        int index=0;
        for(int i=1; i<lista.size();i++){                // percorrer todos os outros nodes da lista
            if(node->get_dist()>lista[i]->get_dist()){   // se algum desses nodes tiver uma distancia menor é escolhida
                node=lista[i];
                index=i;
            }
        }
        lista.erase(lista.begin()+index);                 // retira da lista o node com menor distancia percorrida e passo a trabalhar com este node

        for(auto outgoing_edges : node->get_outgoing_edges()){                           // todas as edges que saiem do node que escolhemos por ter menor distancia
            double total_percorrido =  node->get_dist() + outgoing_edges->get_lenght();  // distancia para cada um dos nodes é a distancia do node anterior e somo o amanho da edge
            if(total_percorrido<outgoing_edges->get_destiny_vertex()->get_dist()){
                outgoing_edges->get_destiny_vertex()->set_dist(total_percorrido);
                outgoing_edges->get_destiny_vertex()->set_prev(node);
            }
        }
    }
}

#endif //PROJETO_CAL_GRAPH_H
