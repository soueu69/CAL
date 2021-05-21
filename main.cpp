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
            cout<<".................................................DISPLAYING FULL ROUTE................................................."<<endl;
            cout<<"------------------------------------------------------------------------------------------------------------------------";
            cout<<"Closest storage to current hospital:  "<<armazem->get_dist()<<" "<<armazem->get_name()<<" to " <<hospitals[0]->get_name()<<endl;
            cout<<endl<<"Ideal Path: ";
            for(auto each : vetor){
                if(each==armazem){
                    cout<<each->get_name();
                    continue;
                }
                cout<<" -> "<<each->get_name();
            }
            cout<<endl<<endl<<"ARRIVED AT YOUR DESTINATION!";
            cout<<endl<<"------------------------------------------------------------------------------------------------------------------------"<<endl;



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

            cout<<".................................................DISPLAYING FULL ROUTE.................................................";
            cout<<endl<<"------------------------------------------------------------------------------------------------------------------------";
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

void menu(Graph *graph){
    cout<<"........MENU........"<<endl;
    cout<<"[0]SET PATH"<<endl;
    cout<<"[1]UPDATE GRAPH"<<endl;
    cout<<"[2]DISPLAY GRAPH "<<endl;
    int choice;
    cout<<"Choose ID: ";
    cin>>choice;
    switch(choice){
        case 0:{
            choose_destinations(graph);
            break;
        }
        case 1:{
            update_graph(graph);
            break;
        }
        case 2:{
            cout<<"CHECK GRAPH";
            break;
        }
    }
}


int main() {
    Graph graph;
    read_nodes(&graph);
    read_edges(&graph);
    menu(&graph);
}
