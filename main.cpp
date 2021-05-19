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

Vertex *search_destinations(string dest,Graph * graph){
    Vertex * objeto= new Vertex("nada",1,1,"Teste");
    objeto->set_dist(INT_MAX);
    for(auto x : graph->get_vertexes()){
        if(x->get_importance()==dest){
            cout<<"Name: "<<x->get_name()<<"   DISTANCE:"<<x->get_dist()<<endl;
            if(x->get_dist()==objeto->get_dist()){
                objeto=x;
            }
            if(x->get_dist()<objeto->get_dist()){
                objeto=x;
            }
        }
    }
    return objeto;
}

void choose_route(Graph *graph){
    cout<<"Possible destinations :"<<endl;
    int counter=0;
    for(auto vertexes : graph->get_vertexes()){
        if(vertexes->get_importance()=="Application"){  // searches for the application centers (places we need a better route to)
            vertexes->set_menuID(counter);
            cout<<"["<<counter<<"]"<<vertexes->get_name()<<endl;
            counter+=1;
        }
    }
    int number;
    cout<<endl<<"How many hospital require vaccines:(max 4):";
    cin>>number;   //number of places that require vacines

    while(true){
    if(number<0 or number>counter){
        cout<<"Error, invalid entry.\n";
        cin.clear();
        cin.ignore();
        cout<<"Insert number again:";
        cin>>number;
         }
    if(number>=0 or number<=counter){
            break;
        }
    }
    int contador_escolhidos=0; // counter of the number of choosen places
    vector<Vertex *> choosen_places;
    while(contador_escolhidos<number){
        int choose;  //choose ID
        cout<<"CHOOSE YOUR DESTINY[ID]:"<<endl;
        cin>>choose;
        Vertex *dis;   // the choosen hospital
        for(auto nodes: graph->get_vertexes()){
            if(nodes->get_menuID()==choose){
                dis = nodes;
                choosen_places.push_back(dis);
            }
        }
        contador_escolhidos+=1;
    }

    for(auto pick : choosen_places){
        cout<<pick->get_name()<<endl;
        graph->dijkstraShortestPath(pick);
        auto objeto_final=search_destinations("Storage",graph);
        cout<<objeto_final->get_name()<<endl;    // choosen storage center  for dis hospital
        cout<<".............................."<<endl;

    }
}

int main() {
    Graph graph;
    read_nodes(&graph);
    read_edges(&graph);
    //check_graph_creation(&graph);
    choose_route(&graph);
}
