#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"
#include <cmath>

void read_nodes(Graph * graph){
    string textline;
    ifstream infile;
    infile.open("../nodes.txt");
    while (getline(infile, textline)) {
        vector<string> info;
        string word = "";
        for (auto x : textline) {
            if (x == ' ') {
                info.push_back(word);
                word = "";
            } else {
                word = word + x;
            }
        }
        info.push_back(word);
        if (info.size() == 6) {
            info.erase(info.begin() + 5);
        }
        double doublex = stod(info[1]);   // coordanate x
        double doubley = stod(info[2]);   //coordenate y
        Vertex *objeto= new Vertex(info[0],doublex,doubley,info[3]);
        graph->fill_vector(objeto);
    }
    infile.close();
}

void read_edges(Graph * graph){
    string textline2;
    ifstream infile2;
    infile2.open("../edges.txt");
    while (getline(infile2, textline2)) {
        vector<string> linha;
        string word = "";
        for (auto x : textline2) {
            if (x == ' ') {
                linha.push_back(word);
                word = "";
            } else {
                word = word + x;
            }
        }
        linha.push_back(word);
        for(int i=0; i<graph->get_vertexes().size();i++){
            if(graph->get_vertex(i)->get_name()==linha[0]){
                for(int i2=0; i2<graph->get_vertexes().size();i2++){
                    if(graph->get_vertex(i2)->get_name()==linha[1]){
                        double le;
                        double first= (graph->get_vertex(i)->get_x()-graph->get_vertex(i2)->get_x())*(graph->get_vertex(i)->get_x()-graph->get_vertex(i2)->get_x());
                        double second = (graph->get_vertex(i)->get_y()-graph->get_vertex(i2)->get_y())*(graph->get_vertex(i)->get_y()-graph->get_vertex(i2)->get_y());
                        le=sqrt(first+second)*10000;
                        Edge *objeto= new Edge(graph->get_vertex(i2),le);
                        graph->get_vertex(i)->add_edge(objeto);
                    }
                }
            }
        }
    }
    infile2.close();
}

void check_graph_creation(Graph * graph){
    cout<<"CHECKING GRAPH"<<endl;
    for(auto x :graph->get_vertexes()){
        cout<<"----------------------------------------------"<<endl;
        cout<<"CURRENT VERTEX: "<<x->get_name()<<endl<<"NUMBER OF EDGES GOING OUT:  "<<x->get_outgoing_edges().size()<<endl;
        for(auto y : x->get_outgoing_edges()){
            cout<<"EDGE SIZE: "<<y->get_lenght()<<endl;
            cout<<"DESTINY VERTEX: "<<y->get_destiny_vertex()->get_name()<<endl;
        }
    }
}

int main() {
    Graph graph;
    read_nodes(&graph);
    read_edges(&graph);
    //check_graph_creation(&graph);
    auto x = graph.get_vertex(3);  // o source sera o node 4
    graph.dijkstraShortestPath(x);
    for(auto ga : graph.get_vertexes()){
        cout<<ga->get_name()<<"  "<<ga->get_dist()/100000<<endl;
    }


}
