#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"


constexpr auto INF = std::numeric_limits<double>::max();
using namespace std;

class Node;
class Edge;
class Graph;

class Node {
private:
    int ID;
    string name;
    string importance;
    double x;
    double y;

    vector<Edge*> outgoing_edges;

    bool visited;   // for path finding
    Edge *path;     // for path finding
    double dist;    // for path finding
    int queueIndex = 0; // required by MutablePriorityQueue


public:

    Node(int id, string name1, string importance1, double x1,double y1) {
        ID = id;
        name = name1;
        importance = importance1;
        x = x1;
        y = y1;
    }
    int outgoing_edges_size(){
        return outgoing_edges.size();
    }

    Edge* get_edge(int x){
        return outgoing_edges[x];
    }


    int get_ID(){
        return this->ID;
    }

    string get_name(){
        return this->name;
    }

    string get_importance(){
        return this->importance;
    }

    double get_x(){
        return this->x;
    }

    double get_y(){
        return this->y;
    }

    void add_edge(Edge* objeto){
        outgoing_edges.push_back(objeto);
    }
    void set_dist(double x){
        dist=x;
}

    friend class Graph;
    friend class MutablePriorityQueue<Node>;
};

class Edge {
private:
    pair< int, int> unify;  //useless
    string name;
    int ID_street;

    Node *node1;
    Node *node2;


    double capacity;
    double cost;
    double flow;

    double distance_between_nodes;
public:
    Edge(int node1, int node2,int ID,string name1) {
        this->unify.first = node1;
        this->unify.second = node2;
        this->ID_street = ID;
        this->name = name1;
    }

    int get_1ID(){
        return unify.first;
    }

    int get_2ID(){
        return unify.second;
    }
    string get_name(){
        return name;
    }

    int get_streetID(){
        return ID_street;
    }

    Node *get_node1(){
        return node1;
    }

    Node *get_node2(){
        return node2;
    }

    void set_node1(Node *objet){
        node1 =  objet;
    }

    void set_node2(Node *objet){
        node2 =  objet;
    }

    double calculate_distance(){
        double x1=this->node1->get_x();
        double y1=this->node1->get_y();
        double x2=this->node2->get_x();
        double y2=this->node2->get_y();
        this->distance_between_nodes = sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)))*1000;
        return distance_between_nodes;
    }
};



class Graph{
    private:
        vector<Node*> nodes;
    public:
    void dijkstraShortestPath(Node *s);

        int get_size(){
            return nodes.size();
        }

        void add_nodes(Node * obj){
            nodes.push_back(obj);
        }

        Node* get_node(int i){
            return  nodes[i];
        }
};

/*
void Graph::dijkstraShortestPath(Node *s ) {   // s é o node inicial
    for(auto v : vertexSet)   // vetor de nodes do grafo
        v->dist = INF;        // dist do node é a distancia total ate este este node
    s->dist = 0;              // a distancia do node atual é 0
    MutablePriorityQueue<Vertex<T>> q;   //nova queue
    q.insert(s);        //inserir o node inicial na queue
    while( ! q.empty() ) {    //enquanto a queueu nao estivel vazia
        auto v = q.extractMin();     //coloca em v um node retirado da queue
        for (auto e : v->outgoing) {    //coloca em e todas as edges que saiem de v
            auto oldDist = e->dest->dist;  // coloca em old dist
            if (relax(v, e->dest, e, e->capacity - e->flow, e->cost)){
                if (oldDist==INF)
                    q.insert(e->dest);
                else
                    q.decreaseKey(e->dest);
            }
        }
        for (auto e : v->incoming) {
            auto oldDist = e->orig->dist;
            if (relax(v, e->orig, e, e->flow, -e->cost)) {
                if (oldDist == INF)
                    q.insert(e->orig);
                else
                    q.decreaseKey(e->orig);
            }
        }
    }
}
 */





#endif /* GRAPH_H_ */
