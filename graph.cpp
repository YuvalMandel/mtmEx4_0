#include "graph.h"
#include <algorithm>
#include <set>
using std::endl;

using std::ostream;
using std::set;
using std::string;
using std::pair;

bool Graph::checkVertexPossible(const Vertex& vertexName){

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

    return true;

}

void Graph::addVertexToGraph(const Vertex& v){

    if(this -> checkVertexPossible(v)){
        this -> vertexes.insert(v);
    }else{
        throw BadVertex();
    }

}

bool Graph::checkEdgePossible(const Edge& e){

    if(e.first == e.second){
        return false;
    }

    bool resultFirst = false;
    bool resultSecond = false;

    for(const Vertex& v : this -> vertexes){

        if(v == e.first){
            resultFirst = true;
        }

        if(v == e.second){
            resultSecond = true;
        }

    }

    return resultFirst && resultSecond;

}

void Graph::addEdgeToGraph(const Edge& e){

    if(this -> checkEdgePossible(e)){
        this -> edges.insert(e);
    }else{
        throw BadEdge();
    }
}

ostream& operator<<(ostream &os, const Edge &e){

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

    for(const Vertex& v : g2.vertexes){
        g.vertexes.erase(v);
    }

    for(const Edge& e : g2.edges){
        g.edges.erase(e);
    }

    for(const Edge& e : g.edges){
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

    for(const Vertex& v1 : g1.vertexes){
        for(const Vertex& v2 : g2.vertexes){
            Vertex new_v = "[" + v1 + ";" + v2 + "]";
            g.vertexes.insert(new_v);
        }
    }

    for(const Edge& e1 : g1.edges){
        for(const Edge& e2 : g2.edges){
            Vertex v_first = "[" + e1.first + ";" + e2.first + "]";
            Vertex v_left = "[" + e1.second + ";" + e2.second + "]";
            Edge new_e(v_first,v_left);
            g.edges.insert(new_e);
        }
    }

    return g;

}

Graph operator!(const Graph& g){

    Graph new_g;

    new_g.vertexes = g.vertexes;

    for(const Vertex& v1 : new_g.vertexes){
        for(const Vertex& v2 : new_g.vertexes){
            if(v1 != v2) {
                Edge new_e(v1, v2);
                new_g.edges.insert(new_e);
            }
        }
    }

    for(const Edge& e : g.edges){
        new_g.edges.erase(e);
    }

    return new_g;

}

ostream& operator<<(ostream &os, const Graph &g){

    for(const Vertex& v : g.vertexes){

        os << v << endl;

    }

    os << "$" << endl;

    for(const Edge& e : g.edges){

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
    for(const Vertex& v : this -> vertexes){

        int vertex_size = v.size();
        outfile.write((char*)&vertex_size, sizeof(int));

        for(char c : v){
            outfile.write(&c, sizeof(char));
        }
    }

    // And each Edge.
    for(const Edge& e : this -> edges){

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
        throw Graph::CantReadFile();
    }

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

        Vertex v;
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
        Vertex v;
        char c;
        Edge e;

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

    return g;

}

Graph create(){
    Graph g;
    return g;
}

void destroy(Graph& g){
    g.~Graph();
}

Graph addVertex(Graph& g, const Vertex& v){
    g.addVertexToGraph(v);
    return g;
}

Graph addEdge(Graph& g, const Vertex& v1, const Vertex& v2){
    Edge e;
    e.first = v1;
    e.second = v2;
    g.addEdgeToGraph(e);
    return g;
}

void disp(const Graph& g){
    std::cout << g;
}

Graph graphUnion(const Graph& graph_in1, const Graph& graph_in2,
                  Graph& graph_out){
    graph_out = graph_in1 + graph_in2;
    return graph_out;
}

Graph graphIntersection(const Graph& graph_in1, const Graph& graph_in2,
                         Graph& graph_out){
    graph_out = graph_in1 ^ graph_in2;
    return graph_out;
}

Graph graphDifference(const Graph& graph_in1, const Graph& graph_in2,
                                Graph& graph_out){
    graph_out = graph_in1 - graph_in2;
    return graph_out;
}

Graph graphProduct(const Graph& graph_in1, const Graph& graph_in2,
                              Graph& graph_out){
    graph_out = graph_in1 * graph_in2;
    return graph_out;
}

Graph graphComplement(const Graph& graph_in1, Graph& graph_out){
    graph_out = !graph_in1;
    return graph_out;
}



//string Graph::convertVertexesToString(){
//
//    string current;
//
//    for(const Vertex& v : this -> vertexes){
//        current += std::to_string(v.size());
//        current += v;
//    }
//
//    return current;
//
//}
//
//string Graph::convertEdgesToString(){
//
//    string current;
//
//    for(const Edge& e : this -> edges){
//        current += e.first + e.second;
//    }
//
//    return current;
//
//}
//
//int Graph::graphVertexesNum(){
//    return this -> vertexes.size();
//}
//
//int Graph::graphEdgesNum(){
//    return this -> edges.size();
//}

//    unsigned int mum_of_vertexes = this -> vertexes.size();
//    unsigned int mum_of_edges = this -> edges.size();
//
//    unsigned int sum_size = 4+4; //for num of vertexes and num
//
//    for(const Vertex& v : this -> vertexes){
//        vertex_size = v.size();
//    }
//
//    os << "$" << endl;
//
//    for(const Edge& e : g.edges){
//
//        os << e << endl;
//
//    }
//
//    return os;

//int main(){
//
//    Graph g1;
//    Graph g2;
//    Vertex v1 = "v1";
//    Vertex v2 = "v2";
//    Vertex v3 = "v3";
//    Vertex v4 = "v4";
//    Edge e12(v1,v2);
//    Edge e34(v3,v4);
//    g1.addVertexToGraph(v1);
//    g1.addVertexToGraph(v2);
//    g1.addVertexToGraph(v3);
//    g2.addVertexToGraph(v3);
//    g2.addVertexToGraph(v4);
//    g1.addEdgeToGraph(e12);
//    g2.addEdgeToGraph(e34);
//    Graph g3 = g1 + g2;
//    Graph g4 = !g1;
//    std::cout << g1 << endl;
////    std::cout << g2 << endl;
////    std::cout << g3 << endl;
//    std::cout << g4 << endl;
//
//    return 0;
//
//}
