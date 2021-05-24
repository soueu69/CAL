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
#include <algorithm>
using namespace std;

class Graph;
class Vertex;
class Edge;

class Vertex{
private:
    int IDaux;   //auxiliary for updating graph
    int menuID=599;  // menu aux

    string importance;
    string name;
    vector<Edge*> outgoing_edges;
    double double_x;
    double double_y;


    double dist;   //auxiliary
    Vertex * previous; //auxiliary

    int ID; //used for Floyd Marshall
public:

    Vertex(string imp,double xx,double yy,string nam,int c){
        importance=imp;
        double_x=xx;
        double_y=yy;
        name=nam;
        ID=c;
    }


    int get_ID(){
        return ID;
    }
    void set_IDaux(int x){
        IDaux=x;
    }
    int get_IDaux(){
        return IDaux;
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
    int aux_id;
    string name;

    double length;
    Vertex * destination_vertex;
    bool available = true;
public:
    Edge(Vertex * dest,double len){
        destination_vertex=dest;
        length=len;
        name = " Estrada da "+dest->get_name();
    }
    void set_aux_id(int y){
        aux_id=y;
    }

    int get_aux_id(){
        return  aux_id;
    }

    bool get_available(){
        return available;
    }

    string get_name(){
        return name;
    }

    void set_available(bool x){
        available=x;
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
    vector<Vertex*> vertexes; //main vertex set

    vector<Edge*> aux_edges;  //auxiliary
    int array_name[22][22]; //aux da keeps all distances between points after floyd is called

public:

    int get_distances(int first,int second){
        return array_name[first][second];
    }

    void insert_distances(int first,int second,int result){
        array_name[first][second]=result;
    }


    Edge* get_edge(int x){
        return aux_edges[x];
    }

    vector<Edge*> get_edges(){
        return aux_edges;
    }

    void fill_edges(Edge* objeto){
        aux_edges.push_back(objeto);
    }


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
    vector<Vertex*> floydWarshall(int id_inicial,int id_final);

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

        visited.push_back(node);                            // colocamos o node com menor distancia no vetor de visitados
        lista.erase(lista.begin()+index);                 // retira da lista o node com menor distancia percorrida e passo a trabalhar com este node

        for(auto outgoing_edges : node->get_outgoing_edges()){            // todas as edges que saiem do node que escolhemos por ter menor distancia
            if(outgoing_edges->get_available()){                           // condicao que proibe edge indisponivel de ser usada para determinar um caminho
                double total_percorrido =  node->get_dist() + outgoing_edges->get_lenght();  // distancia para cada um dos nodes é a distancia do node anterior e somo o amanho da edge
                if(total_percorrido<outgoing_edges->get_destiny_vertex()->get_dist()){
                    outgoing_edges->get_destiny_vertex()->set_dist(total_percorrido);
                    outgoing_edges->get_destiny_vertex()->set_previous(node);
                }
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


vector<Vertex*> Graph::floydWarshall(int id_inicial, int id_final) {
        int dist[22][22]; //matrix that stores distances
        int path[22][22]; // stores index path
        for(int i=0; i<22 ; i++){
            for(int a2=0; a2<23 ; a2++){
                if(i==a2){
                    //insert_distances(i,a2,0);
                    dist[i][a2]=0;
                    path[i][a2]=a2;
                    continue;
                }
                //insert_distances(i,a2,50000000);
                dist[i][a2]=50000000;   //inicializa a matrix
                path[i][a2]=0;          // iniciliza a matriz path a 0
            }
        }

        for(auto x : vertexes){
            auto begin = x->get_ID();
            for( auto edge : x->get_outgoing_edges()){
                auto desteny = edge->get_destiny_vertex()->get_ID();
                auto distance = edge->get_lenght();
                dist[begin][desteny]=distance;  // coloca em cada posicao que temos taamhos da edges o valor na matrx
                //insert_distances(begin,desteny,distance);
                path[begin][desteny]=edge->get_destiny_vertex()->get_ID(); // coloca em cada posicao  o id do node destino
            }
        }

        for(int k = 0; k<22 ;k++){
            for(int i = 0; i<22 ;i++){
                for(int j = 0; j<22 ;j++){
                    if(dist[i][j]>dist[i][k]+dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];    // algortimo que prenche a matrix com todas as didtancias entre pontos
                        path[i][j]=path[i][k];
                    }
                }
            }
        }

    for(int i=0;i<22;i++){
        for(int i2=0;i2<22;i2++){
            insert_distances(i,i2,dist[i][i2]);
        }
    }


    vector<Vertex*> percurso;
    for(auto x :vertexes){
        if(id_final==x->get_ID()){
            percurso.push_back(x);
        }
    }

    while(true){
        auto nova_posicao=path[id_final][id_inicial];
        for(auto x :vertexes){
            if(x->get_ID()==nova_posicao){
                percurso.push_back(x);
            }
        }
        id_final=nova_posicao;
        if(id_final==id_inicial){
            break;
        }
    }
    reverse(percurso.begin(),percurso.end());
    return percurso;
}

#endif //PROJETO_CAL_GRAPH_H
