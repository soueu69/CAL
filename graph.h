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
    int IDaux;   //auxiliary for updating graph
    int menuID=599;  // menu aux
  

    bool available =true;  //for checking if it can be used
    string importance;
    string name;
    vector<Edge*> outgoing_edges;
    double double_x;
    double double_y;


    double dist;   //auxiliary
    Vertex * previous; //auxiliary
public:

    Vertex(string imp,double xx,double yy,string nam){
        importance=imp;
        double_x=xx;
        double_y=yy;
        name=nam;
    }
    void set_IDaux(int x){
        IDaux=x;
    }
    int get_IDaux(){
        return IDaux;
    }

    bool get_availablility(){
        return available;
    }

    void set_availablility(bool flag){
        available=flag;
    }

    void set_menuID(int k){
        menuID=k;
    }

    int get_menuID(){
        return  menuID;
    }

    string get_importance(){
        return importance;
    }
    /*
    void set_visited(bool dis){
        visited=dis;
    }


    bool get_visited(){
            return visited;
    };
     */
    Vertex * get_previous(){
        return previous;
    }

    void set_previous(Vertex * obj){
        previous=obj;
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

    vector<Vertex*> dijkstraShortestPath(Vertex * source,Vertex * destiny);
};

vector<Vertex*> Graph::dijkstraShortestPath(Vertex * source,Vertex * destiny) {
    vector<Vertex*> visited;
    vector<Vertex*> lista;             // criar lista com todos os nodes
    for(auto vertices : vertexes){     // percorrer todos os nodes e atualizar valores
        vertices->set_dist(INT_MAX);
        lista.push_back(vertices);   // colocamos todos os nodes neste vetor
    }
    source->set_dist(0);


    while(!lista.empty()){
        auto node = lista[0];
        int index=0;
        for(int i=1; i<lista.size();i++){
            if((node->get_dist()>lista[i]->get_dist())){
                node=lista[i];
                index=i;                                   // escolhemos o node com menor distancia de todos os nossos nodes(o node source comeca a 0 logo é escolhido)
            }
        }
        //node->set_visited(true);
        visited.push_back(node);                            // colocamos o node com menor distancia no vetor de visitados
        lista.erase(lista.begin()+index);                 // retira da lista o node com menor distancia percorrida e passo a trabalhar com este node

        for(auto outgoing_edges : node->get_outgoing_edges()){            // todas as edges que saiem do node que escolhemos por ter menor distancia
            double total_percorrido =  node->get_dist() + outgoing_edges->get_lenght();  // distancia para cada um dos nodes é a distancia do node anterior e somo o amanho da edge
            if(total_percorrido<outgoing_edges->get_destiny_vertex()->get_dist()){
                outgoing_edges->get_destiny_vertex()->set_dist(total_percorrido);
                outgoing_edges->get_destiny_vertex()->set_previous(node);

            }
        }
    }

    ///return path;
    auto atual = destiny;                   // node destino final
    vector<Vertex*> path;
    while(atual!=source){
        path.push_back(atual);              //path comeca com o destino pretendido
        for(auto node :visited){
            if(atual==node){                    //procuramos o desntino no vetor de node visitados
                atual=atual->get_previous();      //quando é encontrado o node atual, subsitutimos pelo anterior pretendido
            }
        }
    }
    path.push_back(source);
    return path;
}

#endif //PROJETO_CAL_GRAPH_H
