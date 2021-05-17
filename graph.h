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

    double distance;
    Node* prev;


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

    bool available = true;

    double distance_between_nodes;
public:
    friend class Graph;
    friend class Node;
    double getFlow() const;

    Edge(int node1, int node2,int ID,string name1) {
        this->unify.first = node1;
        this->unify.second = node2;
        this->ID_street = ID;
        this->name = name1;
    }


    void set_bool_false(){
        available=false;
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
        bool relax(Node *v, Node *w, Edge *e, double residual, double cost);
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
function Dijkstra(Graph, source):
2:	for each vertex v in Graph:	// Initialization
3:	dist[v] := infinity	// initial distance from source to vertex v is set to infinite
4:	previous[v] := undefined	// Previous node in optimal path from source
5:	dist[source] := 0	// Distance from source to source
6:	Q := the set of all nodes in Graph	// all nodes in the graph are unoptimized - thus are in Q
7:	while Q is not empty:	// main loop
8:	u := node in Q with smallest dist[ ]
9:	remove u from Q
10:	for each neighbor v of u:	// where v has not yet been removed from Q.
11:	alt := dist[u] + dist_between(u, v)
12:	if alt < dist[v]	// Relax (u,v)
13:	dist[v] := alt
14:	previous[v] := u
15:	return previous[ ]
 */


void Graph::dijkstraShortestPath(Node *origin){


}










#endif /* GRAPH_H_ */
