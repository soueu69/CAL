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
    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

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
    int dist[get_vertexes().size()];  // array dist

    //set all distances as infinite instead of source with 0
    for(int x=0; x != get_vertexes().size(); x++){
        if(get_vertexes()[x]->get_name() == source->get_name()) dist[x] = 0;
        else dist[x] = INT_MAX;
    }

    //go through all vertices
    for(int i=0; i != get_vertexes().size() -1; i++){
        int min = INT_MAX;
        int min_index;
        //pick the vertex with the minimum distance that hasnt been visited
        for(int j=0; j != get_vertexes().size(); j++){
            if(!get_vertexes()[j]->visited && dist[j] <= min){
                min = dist[j];
                min_index = j;
            }
        }
        //set vertex as visited
        get_vertexes()[min_index]->visited = true;

        //update the values of the adjacent vertices
        for(int x=0; x != get_vertexes()[min_index]->get_outgoing_edges().size(); x++){
            for(int y=0; y != get_vertexes().size(); y++){
                if(get_vertexes()[y]->get_name()== get_vertexes()[min_index]->get_outgoing_edges()[x]->get_destiny_vertex()->get_name() &&
                        get_vertexes()[min_index]->get_outgoing_edges()[x]->get_lenght() + dist[min_index] < dist[y])
                    dist[y] = get_vertexes()[min_index]->get_outgoing_edges()[x]->get_lenght() + dist[min_index];
            }
        }
    }

    for(int i=0; i != get_vertexes().size(); i++){
        cout << dist[i] << "      " << get_vertexes()[i]->get_name()<< endl;
    }
}


#endif //PROJETO_CAL_GRAPH_H
