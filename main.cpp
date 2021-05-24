#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"
#include <cmath>

void read_nodes(Graph * graph){
    int counter=0;
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
        Vertex *objeto= new Vertex(info[0],doublex,doubley,info[3],counter);
        graph->fill_vector(objeto);
        counter+=1;
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
                        graph->fill_edges(objeto);
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


void get_path(Graph *graph, vector<Vertex*> hospitals){
    //When function is called put all the possible storage centers in tis vector
    vector<Vertex*> storage;

    for(auto x : graph->get_vertexes()){
        if(x->get_importance()=="Storage"){
            storage.push_back(x);
        }
    }

    int choice;
    cout<<".................................................................";
    cout<<endl<<"Which algorithm do you want to use? "<<endl;
    cout<<"[0]DIJKSTRA  ALGORITHM"<<endl;
    cout<<"[1]FLOYDWARSHAL ALGORITHM"<<endl;
    cout<<"Choose ID: ";
    cin>>choice;
    while(true){
        if(choice<0 or choice>2){
            cout<<"Error, invalid entry.\n";
            cin.clear();
            cin.ignore();
            cout<<"Insert number again:";
            cin>>choice;                     // number is the number os hospital that need vacines
        }
        if(choice>=0 or choice<=2){
            break;
        }
    }

    switch(choice){
        case 0 : {
            if(hospitals.size()==1){

                auto armazem = storage[0];  //colocamos o primeiro armazem nesta variavel
                auto vetor=graph->dijkstraShortestPath(hospitals[0],storage[0]);

                for(int i =0 ;i<storage.size();i++){
                    graph->dijkstraShortestPath(hospitals[0],storage[i]);
                    if(storage[i]->get_dist()<armazem->get_dist()){
                        armazem=storage[i];
                        vetor=graph->dijkstraShortestPath(hospitals[0],storage[i]);
                    }
                }
                cout<<".........................................DISPLAYING FULL ROUTE.................................................";
                cout<<"----------------------------------------------------------------------------------------------------------------------";
                cout<<"This path is calculated using 'Dijkstra algorithm'" <<endl;
                cout<<"Path distance: "<<armazem->get_dist()<<endl;
                cout<<endl<<"Ideal Path: ";
                for(auto each : vetor){
                    if(each==armazem){
                        cout<<each->get_name();
                        continue;
                    }
                    cout<<" -> "<<each->get_name();
                }

                cout<<endl<<endl<<"ARRIVED AT YOUR DESTINATION!";
                cout<<endl<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
            }
            if(hospitals.size()>1){
                cout<<"CALCULATE IDEAL PATH FOR MORE THAN 2 HOSPITALS USING JUST 1 STORAGE CENTER IN ONE RIDE"<<endl;
                cout<<endl;

                //cout<<hospitals.size()<<endl;
                vector<string>nomes_hospitais;
                vector<string>nomes_armazens;
                vector<double>distancias;

                for(auto h : hospitals){
                    for(int i =0 ; i<storage.size();i++){
                        graph->dijkstraShortestPath(h,storage[i]);
                        //cout<<"A DISTANCIA DO HOSPITAL "<< h->get_name()<< " ate o armazem "<<storage[i]->get_name() <<" e "<< storage[i]->get_dist()<<endl;
                        nomes_hospitais.push_back(h->get_name());
                        nomes_armazens.push_back(storage[i]->get_name());
                        distancias.push_back(storage[i]->get_dist());
                    }
                }
                double min_dist=100000000000000;
                int index;
                for(int i=0;i<distancias.size(); i++){
                    double x=distancias[i];
                    if(x<min_dist){
                        min_dist=x;
                        index=i;
                    }
                }
                Vertex * source1;
                Vertex * dest;
                for(auto x: graph->get_vertexes()){
                    if(x->get_name()==nomes_hospitais[index]){
                        source1 =x;    // primeiro hospital do percurso
                    }
                    if(x->get_name()==nomes_armazens[index]){
                        dest=x;        // armazem a usar
                    }
                }

                cout<<"................................................DISPLAYING FULL ROUTE................................................";
                cout<<endl<<"------------------------------------------------------------------------------------------------------------------------";
                cout<<"This path is calculated using 'Dijkstra algorithm'" <<endl;
                cout<<"Path distance: "<<dest->get_dist()<<endl;
                auto vetor1= graph->dijkstraShortestPath(source1,dest);
                for(auto each : vetor1){
                    if(each->get_importance()=="Storage"){
                        cout<<each->get_name();
                        continue;
                    }
                    cout<<" -> "<<each->get_name();
                }
                cout<<endl<<endl<<"ARRIVED AT FIRST DESTINATION!"<<endl<<"CALCULATING NEW PATH...";
                cout<<endl<<"------------------------------------------------------------------------------------------------------------------------";
                auto last_visited=vetor1[vetor1.size()-1]; // qual o primeiro hospital que me desloco
                for(int i=0;i<hospitals.size();i++){
                    if(hospitals[i]==last_visited){
                        hospitals.erase(hospitals.begin()+i);  // retira do vetor hospitais o hospital visitado
                    }
                }
                while(true){
                    int distancia=1000000000;
                    int index;
                    for(int i=0;i<hospitals.size();i++){  // percorre todos os hospitais que faltam ir
                        auto vetor1= graph->dijkstraShortestPath(last_visited,hospitals[i]);
                        if(hospitals[i]->get_dist()<distancia){
                            index=i;
                        }
                    }
                    auto show_user= graph->dijkstraShortestPath(hospitals[index] ,last_visited);
                    cout<<"This path is calculated using 'Dijkstra algorithm'" <<endl;
                    cout<<"Path distance: "<<last_visited->get_dist()<<endl;
                    for(auto each : show_user){
                        if(each->get_importance()=="Storage"){
                            cout<<each->get_name();
                            continue;
                        }
                        cout<<" -> "<<each->get_name();
                    }
                    last_visited=show_user[show_user.size()-1];
                    if(hospitals.size()>1){
                        cout<<endl<<endl<<"ARRIVED AT NEW DESTINATION!"<<endl<<"CALCULATING NEW PATH...";
                    }
                    if(hospitals.size()==1){
                        cout<<endl<<endl<<"ARRIVED AT LAST DESTINATION!";
                    }
                    cout<<endl<<"------------------------------------------------------------------------------------------------------------------------";
                    hospitals.erase(hospitals.begin()+index);
                    if(hospitals.empty()){
                        break;
                    }
                }
            }
            break;
        }
        case 1 :{
            cout<<endl;
            if(hospitals.size()==1){

                graph->floydWarshall(2,8);
                int distancia=1000000;
                int id_armazem_escolhido;
                for(auto armazens : storage){
                    if(graph->get_distances(armazens->get_ID(),hospitals[0]->get_ID())<distancia){
                        distancia=graph->get_distances(armazens->get_ID(),hospitals[0]->get_ID());
                        id_armazem_escolhido=armazens->get_ID();
                    }
                }
                auto caminho = graph->floydWarshall(id_armazem_escolhido,hospitals[0]->get_ID());

                cout<<".................................................DISPLAYING FULL ROUTE................................................."<<endl;
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"This path is calculated using 'Floyd Warshall algorithm'" <<endl;
                cout<<"Path distance: "<<distancia<<endl;
                for(auto x : caminho){
                    if(x->get_ID()==hospitals[0]->get_ID()){
                        cout<<x->get_name();
                        continue;
                    }
                    cout<<x->get_name()<<"->";
                }
                cout<<endl;
                cout<<endl<<"ARRIVED AT YOUR DESTINATION!";
                cout<<endl<<"------------------------------------------------------------------------------------------------------------------------"<<endl;


            }
            if(hospitals.size()>1){
                    graph->floydWarshall(4,8);
                    int distancia=1000000;
                    int id_armazem_escolhido;
                    int id_hospital_escolhido;
                    for(auto hospitais : hospitals){
                        for(auto armazens : storage){
                            if(graph->get_distances(armazens->get_ID(),hospitais->get_ID())<distancia){
                                distancia=graph->get_distances(armazens->get_ID(),hospitais->get_ID());
                                id_armazem_escolhido=armazens->get_ID();
                                id_hospital_escolhido=hospitais->get_ID();
                            }
                        }
                    }
            auto path = graph->floydWarshall(id_armazem_escolhido,id_hospital_escolhido);
            cout<<".................................................DISPLAYING FULL ROUTE................................................."<<endl;
            cout<<"------------------------------------------------------------------------------------------------------------------------";
            cout<<"This path is calculated using 'Floyd Warshall algorithm'" <<endl<<"Path distance: "<<distancia<<endl<<endl;
            for(auto x : path){
                if(x->get_ID()==hospitals[0]->get_ID()){
                    cout<<x->get_name();
                    continue;
                }
                cout<<x->get_name()<<"->";
            }
            cout<<endl;
            cout<<endl<<"ARRIVED AT YOUR DESTINATION! CALCULATING NEXT PATH...";
            cout<<endl<<"------------------------------------------------------------------------------------------------------------------------";

            int eliminar;
            for(int i=0;i < hospitals.size();i++){
                if(hospitals[i]->get_ID()==id_hospital_escolhido){
                    eliminar=i;
                }
            }
            hospitals.erase(hospitals.begin()+eliminar);
            while(true) {
                if (hospitals.size() == 0) {
                    break;
                }

                int distancia2 = 10000000;
                int chosen_next_hospital;
                for (auto hospitals_are_left : hospitals) {
                    if (graph->get_distances(id_hospital_escolhido, hospitals_are_left->get_ID()) < distancia2) {
                        distancia2 = graph->get_distances(id_hospital_escolhido, hospitals_are_left->get_ID());
                        chosen_next_hospital = hospitals_are_left->get_ID();
                    }
                }
                auto path2 = graph->floydWarshall(id_hospital_escolhido, chosen_next_hospital);
                cout<<"This path is calculated using 'Floyd Warshall algorithm'" <<endl;
                cout<<"Path distance: "<<distancia2<<endl<<endl;
                for (auto x : path2) {
                    if (x->get_ID() == hospitals[0]->get_ID()) {
                        cout << x->get_name();
                        continue;
                    }
                    cout << x->get_name() << "->";
                }
                cout << endl;
                if(hospitals.size()==1){
                    cout<<endl<<"ARRIVED AT YOUR DESTINATION!";
                }
                if(hospitals.size()>1){
                    cout<<endl<<"ARRIVED AT YOUR DESTINATION! CALCULATING NEXT PATH...";
                }
                cout << endl<< "------------------------------------------------------------------------------------------------------------------------";

                id_hospital_escolhido = chosen_next_hospital;
                int eliminar2;
                for (int i = 0; i < hospitals.size(); i++) {
                    if (hospitals[i]->get_ID() == id_hospital_escolhido) {
                        eliminar2 = i;
                    }
                }
                hospitals.erase(hospitals.begin() + eliminar2);
            }
            }
        }
    }
}

void choose_destinations(Graph *graph){
    vector<Vertex*> required_hospitals;                 // all the chosen destination places by the user
    cout<<endl<<"Possible destinations :"<<endl;
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
        cin>>number;                     // number is the number os hospital that need vacines
         }
    if(number>=0 or number<=counter){
            break;
        }
    }
    int counter2=0;
    while(counter2<number) {        // asks for hospital destination counter number of times
        int choose;                 //choose ID
        cout << "CHOOSE YOUR DESTINATION[ID]:" << endl;
        cin >> choose;
        for (auto nodes: graph->get_vertexes()) {
            if (nodes->get_menuID() == choose) {
                required_hospitals.push_back(nodes);
            }
        }
        counter2+=1;
    }
    get_path(graph,required_hospitals);
}

void update_graph(Graph *graph){
    cout<<"[0]Set road as unavailable"<<endl;
    cout<<"[1]Set road as available"<<endl;
    int choice;
    cout<<"Choose ID:";
    cin>>choice;

    if(choice==0){
        for(int i=0;i<graph->get_edges().size();i++){
            graph->get_edge(i)->set_aux_id(i);
            cout<<"["<<i<<"]"<<graph->get_edge(i)->get_name()<<"Availability: "<<graph->get_edge(i)->get_available()<<endl;
        }

        int chosing;
        cout<<"Choose ID: ";
        cin>>chosing;
        while(true){
            if(chosing<0 or chosing>graph->get_edges().size()){
                cout<<"Error, invalid entry.\n";
                cin.clear();
                cin.ignore();
                cout<<"Insert number again:";
                cin>>chosing;
            }
            if(chosing>=0 or chosing<=graph->get_edges().size()){
                break;
            }
        }

        for(auto edge : graph->get_edges()){
            if(edge->get_aux_id()==chosing and edge->get_available()){
                edge->set_available(false);
            }
        }
    }
    if(choice==1){
        for(int i=0;i<graph->get_edges().size();i++){
            graph->get_edge(i)->set_aux_id(i);
            cout<<"["<<i<<"]"<<graph->get_edge(i)->get_name()<<"Availability: "<<graph->get_edge(i)->get_available()<<endl;
        }

        int chosing;
        cout<<"Choose ID: ";
        cin>>chosing;
        while(true){
            if(chosing<0 or chosing>graph->get_edges().size()){
                cout<<"Error, invalid entry.\n";
                cin.clear();
                cin.ignore();
                cout<<"Insert number again:";
                cin>>chosing;
            }
            if(chosing>=0 or chosing<=graph->get_edges().size()){
                break;
            }
        }

        for(auto edge : graph->get_edges()){
            if(edge->get_aux_id()==chosing and !edge->get_available()){
                edge->set_available(true);
            }
        }
    }
}


bool menu(Graph *graph){
    cout<<".................MENU................."<<endl;
    cout<<"[0]SET PATH"<<endl;
    cout<<"[1]UPDATE GRAPH"<<endl;
    cout<<"[2]EXIT "<<endl;
    cout<<"......................................"<<endl;
    int choice;
    cout<<"Choose ID: ";
    cin>>choice;
    switch(choice){
        case 0:{
            choose_destinations(graph);
            return true;
        }
        case 1:{
            update_graph(graph);
            return true;
        }
        case 2:{
            return false;

        }
    }
        return false;
}


int main() {
    Graph graph;
    read_nodes(&graph);
    read_edges(&graph);

    while(true){
        auto x = menu(&graph);
        if(!x){
            break;
        }
    }
    auto x=graph.floydWarshall(0,2);
    for(auto y :x){
        cout<<y->get_name()<<endl;
    }
}
