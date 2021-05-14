#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
using namespace std;

class Edge {
private:
    pair< int, int> unify;  //nodes
    string name;
    int ID_street;
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

};

class Node {
private:
    vector<Edge*> outgoing_edges;
    int ID;
    string name;
    string importance;
    int x;
    int y;
public:
    Node(int id, string name1, string importance1, int x1,int y1) {
        ID = id;
        name = name1;
        importance = importance1;
        x = x1;
        y = y1;
    };


    int get_ID(){
        return this->ID;
    }

    string get_name(){
        return this->name;
    }

    string get_importance(){
        return this->importance;
    }

    int get_x(){
        return this->x;
    }

    int get_y(){
        return this->y;
    }

    void add_edge(Edge* objeto){
        outgoing_edges.push_back(objeto);
    }

};

class Graph{
    private:
        vector<Node*> nodes;
    public:
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

#endif /* GRAPH_H_ */
