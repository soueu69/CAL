#include "graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main() {
    cout<<"........................................................................................."<<endl;
    cout<<"LOADING GRAPH..."<<endl;
    cout<<"........................................................................................."<<endl;
    Graph graph;
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
        int int_2 = stoi(info[2]);
        int int_3 = stoi(info[3]);
        Node *objeto = new Node(int_1, info[4], info[1], int_2, int_3);
        //nodes.push_back(objeto);
        graph.add_nodes(objeto);
    }
    infile.close();

    /*
    cout << "---------MENU---------" << endl;
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->getinfo();
        cout << endl;
    }
     */
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

    //vector<Edge *> edges;
    ///READ NODE FILE
    string textline2;
    ifstream infile2;
    infile2.open("../edges.txt");
    //calProj\CAL
    while (getline(infile2, textline2)) {
        //cout << textline2 << endl;
        vector<string> linha;
        string word = "";

        for (auto x : textline2) {
            if (x == ' ') {
                //cout << word << endl;
                linha.push_back(word);
                word = "";
            } else {
                word = word + x;
            }
        }
        //cout << word << endl;
        linha.push_back(word);
        //cout<<linha.size()<<endl;
        int id1 = stoi(linha[0]);
        int node1 = stoi(linha[1]);
        int node2 = stoi(linha[2]);

        cout<< "THIS EDGE-> "<<"NODE 1: "<<  node1 << "   NODE 2: "<< node2<<endl;


        Edge *objeto = new Edge(node1, node2, id1, linha[3]);

        //cout<<objeto->get_name()<<"--------"<<objeto->get_1ID()<<"---------"<< objeto->get_2ID()<<endl;
        /*
        cout<<"...................."<<endl;
        cout<<objeto->get_1ID()<<endl;
        cout<< objeto->get_2ID()<<endl;
        cout<<"------------------"<<endl;
         */



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

    ////////////////////////////////////////////////////////////////////////////////////////////////

    for (int x = 0; x < graph.get_size(); x++) {
        cout<<"----------------------"<<endl;
        cout<<"MAIN NODE: "<<graph.get_node(x)->get_name()<<endl;
        cout<<"NUMBER OF OUTGOING EDGES: " <<graph.get_node(x)->outgoing_edges_size()<<endl;
        for(int a=0;a<graph.get_node(x)->outgoing_edges_size();a++){
            cout<<"EDGE: "<<graph.get_node(x)->get_edge(a)->get_name()<<endl;
            cout<<"EDGE CONECTED NODE1 :"<<graph.get_node(x)->get_edge(a)->get_node1()->get_ID()<<endl;
            cout<<"EDGE CONECTED NODE2 :"<<graph.get_node(x)->get_edge(a)->get_node2()->get_ID()<<endl;
        }

        //just checking if everything is good ...

    }
    cout<<endl;
    cout<<"....................................................................................................."<<endl;
    cout<<"Loading finished!"<< " EZ PZ "<< " ... CATS>CAL-> IS SHIT!! %""";







}


