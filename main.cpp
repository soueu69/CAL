#include "graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main() {

    Graph graph;
    //vector<Node *> nodes;
    ///READ NODE FILE
    string textline;
    ifstream infile;
    infile.open("C:\\Users\\diogo\\Desktop\\nodes.txt");
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

    vector<Edge *> edges;
    ///READ NODE FILE
    string textline2;
    ifstream infile2;
    infile2.open("C:\\Users\\diogo\\Desktop\\edges.txt");
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
        int id1= stoi(linha[0]);
        int node1= stoi(linha[1]);
        int node2= stoi(linha[2]);

        Edge *objeto = new Edge( node1,node2,id1, linha[3]);

        //cout<<objeto->get_name()<<"--------"<<objeto->get_1ID()<<"---------"<< objeto->get_2ID()<<endl;

        edges.push_back(objeto);

}
    infile2.close();

    ////////////////////////////////////////////////////////////////////////////////////////////////
 /*
    for(int i=0; i<edges.size();i++){
        edges[i]->getinfo();
        cout<<endl;
    }


    for(int i=0;i<edges.size();i++){
        edges[i]->get1ID();
        cout<<endl;
        edges[i]->get2D();
        cout<<endl;
        edges[i]->get_name();
        cout<<endl;
        edges[i]->get_streetID();
    }
     */


 for(int x =0; x<graph.get_size();x++){

     //cout<<graph.get_node(x)->get_ID()<<"--------";
     //cout<<graph.get_node(x)->get_name()<<"--------";
     //cout<<graph.get_node(x)->get_importance()<<endl;

 }

 for(int i=0; i<edges.size();i++){
     cout<<edges[i]->get_name()<<"--------"<<edges[i]->get_1ID()<<"---------"<< edges[i]->get_2ID()<<endl;

 }












}



