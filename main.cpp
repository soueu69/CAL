#include "graph.h"
#include "Vehicle.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
Graph graph;
vector<Vehicle*> vans;

void Select_Hospitals(){
    cout<<"Available vaccination centers:"<<endl;
    for(int a =0; a<graph.get_size();a++){
        if(graph.get_node(a)->get_importance()=="Application"){
            cout<<"["<<graph.get_node(a)->get_ID()<<"]-";
            cout<<graph.get_node(a)->get_name()<<endl;
        }
    }
    int number;
    cout<<"How many Hospitals require vacines?(1/2...)"<<endl;
    cin>>number;
    int count=0;
    while(count<number){
        int id_hospital;
        cout<<"Which hospital?"<<endl;
        cin>>id_hospital;
        int quantity;
        cout<<"How many vacines are required?"<<endl;
        cout<<"--MAX QUANTITY PER VAN IS : 50000--"<<endl;
        cin>>quantity;
        if(quantity<5000){
            for(int u=0;u<graph.get_size();u++){
                if(graph.get_node(u)->get_ID()==id_hospital){
                    graph.dijkstraShortestPath(graph.get_node(u));
                }
            }
            cout<<"HERE WE CHECK THE IDEAL PATH MADE BY dijkstraShortestPath "<<endl;
        }
        else{
            cout<<"NEED MORE THAN 1 VAN"<<endl;
        }
        count++;
    }
}



void menu(){
    int choose;
    cout<<"Select option:";
    cin>>choose;
    cout<<endl;
    switch(choose){
        case 0:{
            cout<<"[0]-Unavailable edge"<<endl<<"[1]-Remove Node"<<endl;
            int choose1;
            cout<<"Select Option:"<<endl;
            cin>>choose1;
            if(choose1==0){
                //display the graph
                //checkloading();
                cout<<"Which edge is not available(ID)?<<endl";
            }
            if(choose1==1){
                cout<<"Which node is not avaialable";
            }
            break;
        }

        case 1 : {
            Select_Hospitals();
            break;
        }
    }

}
void checkloading(){
    for (int x = 0; x < graph.get_size(); x++) {
        //cout<<"----------------------"<<endl;
        //cout<<"MAIN NODE: "<<graph.get_node(x)->get_name()<<endl;
        //cout<<"COORDINATES:"<<graph.get_node(x)->get_x()<<","<<graph.get_node(x)->get_y()<<endl;
        //cout<<"NUMBER OF OUTGOING EDGES: " <<graph.get_node(x)->outgoing_edges_size()<<endl;
        for(int a=0;a<graph.get_node(x)->outgoing_edges_size();a++){
            cout<<"EDGE: "<<graph.get_node(x)->get_edge(a)->get_streetID()<<" ";
            cout<<"EDGE: "<<graph.get_node(x)->get_edge(a)->get_name()<<" ";
            //cout<<"LENGHT: "<<graph.get_node(x)->get_edge(a)->calculate_distance()<<endl;
            cout<<"EDGE CONECTED NODE1 :"<<graph.get_node(x)->get_edge(a)->get_node1()->get_ID()<<" ",
            cout<<"EDGE CONECTED NODE2 :"<<graph.get_node(x)->get_edge(a)->get_node2()->get_ID()<<endl;

        }
        //just checking if everything is good ...

    }
}

void initialize(){
    cout<<endl;
    cout<<"....................................................................................................."<<endl;
    cout<<"Loading finished!"<<endl;
    cout<<endl;
    cout<<"VaccineRouter..."<<endl;
    cout<< "................."<< "MENU"<< "................."<<endl;
    cout<<"[0]-Change map setup"<<endl<<"[1]-Program route"<<endl;
}

void read_nodes(){
    cout<<"........................................................................................."<<endl;
    cout<<"LOADING GRAPH..."<<endl;
    cout<<"........................................................................................."<<endl;
    ///READ NODE FILE
    string textline;
    ifstream infile;
    infile.open("../nodes.txt");
    while (getline(infile, textline)) {
        vector<string> info;
        //cout << textline << endl;
        string word = "";
        for (auto x : textline) {
            if (x == ' ') {
                //cout << word << endl;
                info.push_back(word);
                word = "";
            } else {
                word = word + x;
            }
        }
        //cout << word << endl;
        info.push_back(word);
        if (info.size() == 6) {
            info.erase(info.begin() + 5);
        }
        int int_1 = stoi(info[0]);
        double int_2 = stod(info[2]);   // coordanate x
        double int_3 = stod(info[3]);   //coordenate y
        //cout<<int_2<<endl;
        //cout<<int_3<<endl;
        Node *objeto = new Node(int_1, info[4], info[1], int_2, int_3);
        //nodes.push_back(objeto);
        graph.add_nodes(objeto);
    }
    infile.close();
}

void read_edges(){
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
        int id1 = stoi(linha[0]);
        int node1 = stoi(linha[1]);
        int node2 = stoi(linha[2]);
        Edge *objeto = new Edge(node1, node2, id1, linha[3]);

        for (int i = 0; i < graph.get_size(); i++) {
            int value = graph.get_node(i)->get_ID();    //NODE ID
            if (value == objeto->get_1ID()) {            //if node ID is the same as the first edge ID
                objeto->set_node1(graph.get_node(i));
                graph.get_node(i)->add_edge(objeto);     // add this edge to the node
            }
            if (value == objeto->get_2ID()) {
                objeto->set_node2(graph.get_node(i));
                graph.get_node(i)->add_edge(objeto);
            }
        }
    }
    infile2.close();
}


int main() {
    for(int i=0; i<4;i++){
        Vehicle *objeto;
        objeto->set_id(i);
        vans.push_back(objeto);
    }
    read_nodes();
    read_edges();
    //checkloading();
    initialize();
    menu();

}


