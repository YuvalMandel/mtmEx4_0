#include "graph.h"
#include <algorithm>
using std::endl;

using std::ostream;
using std::set;
using std::string;
using std::pair;

bool Graph::checkVertexPossible(const string& vertexName){

    for (unsigned int i = 0; i < vertexName.length(); ++i) {
        if(!(isalnum(vertexName[i]) || vertexName[i] == '[' ||
           vertexName[i] == ']' || vertexName[i] == ';')){
            return false;
        }
    }

    int bracketsNum = 0;

    for (unsigned int i = 0; i < vertexName.length(); ++i) {
        if(vertexName[i] == '['){
            bracketsNum++;
        }else if(vertexName[i] == ']'){
            bracketsNum--;
            if(bracketsNum < 0){
                return false;
            }
        }else if(vertexName[i] == ';'){
            if(bracketsNum == 0){
                return false;
            }
        }
    }

    if(bracketsNum != 0){
        return false;
    }

    std::set<string>::const_iterator search = this -> vertexes.find(vertexName);
    if (search != this -> vertexes.end()) {
        return false;
    }

    return true;

}

void Graph::addVertexToGraph(const string& v){

    if(this -> checkVertexPossible(v)){
        this -> vertexes.insert(v);
    }else{
        throw std::invalid_argument( "Bad vertex" );
    }

}

bool Graph::checkEdgePossible(const pair<string, string>& e){

    if(e.first == e.second){
        return false;
    }

    bool resultFirst = false;
    bool resultSecond = false;

    for(const string& v : this -> vertexes){

        if(v == e.first){
            resultFirst = true;
        }

        if(v == e.second){
            resultSecond = true;
        }

    }

    std::set<pair<string, string>>::const_iterator search = this -> edges.find(e);
    if (search != this -> edges.end()) {
        return false;
    }

    return resultFirst && resultSecond;

}

void Graph::addEdgeToGraph(const pair<string, string>& e){

    if(this -> checkEdgePossible(e)){
        this -> edges.insert(e);
    }else{
        throw std::invalid_argument("Bad edge");
    }
}

ostream& operator<<(ostream &os, const pair<string, string> &e){

    return os << e.first << " " << e.second;

}

Graph operator+(const Graph& g1, const Graph& g2){

    Graph g;

    std::set_union(g1.vertexes.begin(), g1.vertexes.end(),
                   g2.vertexes.begin(), g2.vertexes.end(),
                   std::inserter(g.vertexes, g.vertexes.begin()));

    std::set_union(g1.edges.begin(), g1.edges.end(),
                   g2.edges.begin(), g2.edges.end(),
                   std::inserter(g.edges, g.edges.begin()));

    return g;

}

Graph operator-(const Graph& g1, const Graph& g2){

    Graph g = g1;

    for(const string& v : g2.vertexes){
        g.vertexes.erase(v);
    }

    for(const pair<string, string>& e : g2.edges){
        g.edges.erase(e);
    }

    for(const pair<string, string>& e : g.edges){
        if(!g.checkEdgePossible(e)){
            g.edges.erase(e);
        }
    }

    return g;

}

Graph operator^(const Graph& g1, const Graph& g2){

    Graph g;

    std::set_intersection(g1.vertexes.begin(), g1.vertexes.end(),
                          g2.vertexes.begin(), g2.vertexes.end(),
                          std::inserter(g.vertexes, g.vertexes.begin()));

    std::set_intersection(g1.edges.begin(), g1.edges.end(),
                          g2.edges.begin(), g2.edges.end(),
                          std::inserter(g.edges, g.edges.begin()));

    return g;

}

Graph operator*(const Graph& g1, const Graph& g2){

    Graph g;

    for(const string& v1 : g1.vertexes){
        for(const string& v2 : g2.vertexes){
            string new_v = "[" + v1 + ";" + v2 + "]";
            g.vertexes.insert(new_v);
        }
    }

    for(const pair<string, string>& e1 : g1.edges){
        for(const pair<string, string>& e2 : g2.edges){
            string v_first = "[" + e1.first + ";" + e2.first + "]";
            string v_left = "[" + e1.second + ";" + e2.second + "]";
            pair<string, string> new_e(v_first,v_left);
            g.edges.insert(new_e);
        }
    }

    return g;

}

Graph operator!(const Graph& g){

    Graph new_g;

    new_g.vertexes = g.vertexes;

    for(const string& v1 : new_g.vertexes){
        for(const string& v2 : new_g.vertexes){
            if(v1 != v2) {
                pair<string, string> new_e(v1, v2);
                new_g.edges.insert(new_e);
            }
        }
    }

    for(const pair<string, string>& e : g.edges){
        new_g.edges.erase(e);
    }

    return new_g;

}

ostream& operator<<(ostream &os, const Graph &g){

    for(const string& v : g.vertexes){

        os << v << endl;

    }

    os << "$" << endl;

    for(const pair<string, string>& e : g.edges){

        os << e << endl;

    }

    return os;

}

void Graph::saveGraphToFile(const std::string& fileName){

    std::ofstream outfile(fileName, std::ios_base::binary);

    // First we will write the number of vertexes.
    int num_of_vertexes = this -> vertexes.size();
    outfile.write((char*)&num_of_vertexes, sizeof(int));

    // Now we will write the number of edges.
    int num_of_edges = this -> edges.size();
    outfile.write((char*)&num_of_edges, sizeof(int));

    // Now each vertex.
    for(const string& v : this -> vertexes){

        int vertex_size = v.size();
        outfile.write((char*)&vertex_size, sizeof(int));

        for(char c : v){
            outfile.write(&c, sizeof(char));
        }
    }

    // And each Edge.
    for(const pair<string, string>& e : this -> edges){

        int vertex_size = e.first.size();
        outfile.write((char*)&vertex_size, sizeof(int));

        for(char c : e.first){
            outfile.write(&c, sizeof(char));
        }

        vertex_size = e.second.size();
        outfile.write((char*)&vertex_size, sizeof(int));

        for(char c : e.second){
            outfile.write(&c, sizeof(char));
        }

    }

    outfile.close();

}

Graph loadGraphFromFile(const std::string& fileName){

    std::ifstream infile(fileName, std::ios_base::binary);

    if(!infile.is_open()){
        throw std::invalid_argument("Can't open file");
    }

    // Might need to add try and catch // TODO

    Graph g;

    // Read number of vertexes.
    int num_of_vertexes;
    infile.read((char*)&num_of_vertexes, sizeof(int));

    // Read number of edges.
    int num_of_edges;
    infile.read((char*)&num_of_edges, sizeof(int));

    // Read each vertex.
    for(int i = 0; i < num_of_vertexes; ++i) {

        // We will read the firs 4 bytes (int) to know how much chars to read.
        int vertex_size;
        infile.read((char*)&vertex_size, sizeof(int));

        string v;
        char c;

        for(int j = 0; j < vertex_size; ++j){
            infile.read((char*)&c, sizeof(char));
            v += c;
        }

        g.addVertexToGraph(v);

    }

    // Read each edge.
    for(int i = 0; i < num_of_edges; ++i) {

        int vertex_size;
        string v;
        char c;
        pair<string, string> e;

        // First Vertex

        // We will read the first 4 bytes (int) to know how much chars to read.
        infile.read((char*)&vertex_size, sizeof(int));

        for(int j = 0; j < vertex_size; ++j){
            infile.read((char*)&c, sizeof(char));
            v += c;
        }

        e.first = v;

        // Second vertex
        v = "";

        // We will read the first 4 bytes (int) to know how much chars to read.
        infile.read((char*)&vertex_size, sizeof(int));

        for(int j = 0; j < vertex_size; ++j){
            infile.read((char*)&c, sizeof(char));
            v += c;
        }

        e.second = v;

        g.addEdgeToGraph(e);

    }

    infile.close();

    return g;

}

Graph* create(){
    Graph* g = new Graph;
    return g;
}

void destroy(Graph* g){
    delete g;
}

Graph* addVertex(Graph* g, char* v){
    try {
        std::string string_v(v);
        g -> addVertexToGraph(string_v);
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return g;
}

Graph* addEdge(Graph* g, char* v1, char* v2){

    std::string string_v1(v1);
    std::string string_v2(v2);

    pair<string, string> e;
    e.first = string_v1;
    e.second = string_v2;

    try {
        g->addEdgeToGraph(e);
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return g;
}

void disp(Graph* g){
    std::cout << *g;
}

Graph* graphUnion(Graph* graph_in1, Graph* graph_in2,
                                Graph* graph_out){
    *graph_out = *graph_in1 + *graph_in2;
    return graph_out;
}

Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2,
                                       Graph* graph_out){
    *graph_out = *graph_in1 ^ *graph_in2;
    return graph_out;
}

Graph* graphDifference(Graph* graph_in1, Graph* graph_in2,
                                     Graph* graph_out){
    *graph_out = *graph_in1 - *graph_in2;
    return graph_out;
}

Graph* graphProduct(Graph* graph_in1, Graph* graph_in2,
                                  Graph* graph_out){
    *graph_out = *graph_in1 * *graph_in2;
    return graph_out;
}

Graph* graphComplement(Graph* graph_in1, Graph* graph_out){
    *graph_out = !(*graph_in1);
    return graph_out;
}
