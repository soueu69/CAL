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

    bool available =true;  //for checking if it can be used
    string importance;
    string name;
    vector<Edge*> outgoing_edges;
    double double_x;
    double double_y;


    double dist;   //auxiliary
    Vertex * previous; //auxiliary

    double dist_Floyd;  //distance used in FLOYD
    int ID; //used for Floyd Marshall
public:

    Vertex(string imp,double xx,double yy,string nam,int c){
        importance=imp;
        double_x=xx;
        double_y=yy;
        name=nam;
        ID=c;
    }
    int get_dist_Floyd(){
        return dist_Floyd;
    }

    void set_dist_Floyd(double floy){
        dist_Floyd=floy;
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

    bool get_availablility(){
        return available;
    }

    void set_availablility(bool flag){
        available=flag;
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
public:
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
    vector<Vertex*>  floydWarshall(int id_inicial, int id_final);

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
        //node->set_visited(true);
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

vector<Vertex*>  Graph::floydWarshall(int id_inicial, int id_final) {
    int array[23][23];
    int path[23][23];
    for(int i=0;i<23;i++){
        for(int i2=0;i2<23;i2++){
            array[i][i2]=999;
            if(i==i2){
                array[i][i2]=0;
                path[i][i2]=i;
            }
        }
    }
    for(int i2=0; i2< vertexes.size();i2++){  //percorremos todos os nodes
        auto first_node=vertexes[i2]->get_ID();   // ID do primeiro node
        for(auto x : vertexes[i2]->get_outgoing_edges()){
            auto distancia = x->get_lenght();   // distania entre estes dois nodes
            auto second_node = x->get_destiny_vertex()->get_ID();  //ID do segundo node
            array[first_node][second_node]=distancia;
            path[first_node][second_node]=x->get_destiny_vertex()->get_ID();

        }
    }
    for(int k =0;k<23;k++){
        for(int i =0;i<23;i++){
            for(int j =0;j<23;j++){
                if(array[i][j]>array[i][k]+array[k][j]){
                    array[i][j]=array[i][k]+array[k][j];
                    path[i][j]=path[i][k];
                }
            }
        }
    }
    /*
    for(int i=0;i<23;i++){
        for(int i2=0;i2<23;i2++){
            cout<<" "<<array[i][i2]<<" ";
        }
        cout<<"!"<<endl;
    }
     */
    ///GET PATH

    vector<int> caminho;   //guarda caminho percorrido
    caminho.push_back(id_final);  //coloca a ultima
    while(true){
        int tamanho = caminho.size();
        if(caminho[tamanho-2]==caminho[tamanho-1]){
            break;
        }
        auto anterior = path[id_inicial][id_final];  //calcula o anterior ao final
        caminho.push_back(anterior);        // coloca no vetor o anterior
        id_final=anterior;                     //final passa a ser o anterior
    }
    caminho.pop_back();
    caminho.push_back(id_inicial);
    reverse(caminho.begin(),caminho.end());

    vector<Vertex*> sequencia;
    for(int i =0 ;i<caminho.size();i++){
        auto id = caminho[i];
        for(auto x :vertexes){
            if(x->get_ID()==id){
                sequencia.push_back(x);
            }
        }
    }
    return sequencia;
}

#endif //PROJETO_CAL_GRAPH_H
