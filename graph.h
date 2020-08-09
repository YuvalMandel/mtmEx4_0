#ifndef MTMEX4_0_GRAPH_H
#define MTMEX4_0_GRAPH_H

#include <iostream>
#include <set>
#include <fstream>

#define Vertex std::string
#define Edge std::pair<Vertex, Vertex>

class Graph {
private:

    std::set<Vertex> vertexes;
    std::set<Edge> edges;


public:

    Graph() = default;
    ~Graph() = default;
    Graph& operator=(const Graph&) = default;

    bool checkEdgePossible(const Edge& e);
    bool checkVertexPossible(const Vertex& e);
    void addVertexToGraph(const Vertex& v);
    void addEdgeToGraph(const Edge& e);

    void saveGraphToFile(const std::string& fileName);

    friend Graph loadGraphFromFile(const std::string& fileName);

    friend Graph operator+(const Graph& g1, const Graph& g2);
    friend Graph operator-(const Graph& g1, const Graph& g2);
    friend Graph operator^(const Graph& g1, const Graph& g2);
    friend Graph operator*(const Graph& g1, const Graph& g2);
    friend Graph operator!(const Graph& g);
    friend std::ostream& operator<<(std::ostream &os, const Graph &g);

};

Graph loadGraphFromFile(const std::string& fileName);

extern "C" Graph* graphCreate(){
    Graph* g = new Graph;
    return g;
}

extern "C" void graphDestroy(Graph* g){
    delete g;
}

extern "C" Graph* graphAddVertex(Graph* g, char* v){
    try {
        std::string string_v(v);
        g -> addVertexToGraph(string_v);
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return g;
}

extern "C" Graph* graphAddEdge(Graph* g, char* v1, char* v2){

    std::string string_v1(v1);
    std::string string_v2(v2);

    Edge e;
    e.first = string_v1;
    e.second = string_v2;

    try {
        g->addEdgeToGraph(e);
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return g;
}

extern "C" void graphDisp(Graph* g){
    std::cout << *g;
}

extern "C" Graph* graphUnionInt(Graph* graph_in1, Graph* graph_in2,
                 Graph* graph_out){
    *graph_out = *graph_in1 + *graph_in2;
    return graph_out;
}

extern "C" Graph* graphIntersectionInt(Graph* graph_in1, Graph* graph_in2,
                                Graph* graph_out){
    *graph_out = *graph_in1 ^ *graph_in2;
    return graph_out;
}

extern "C" Graph* graphDifferenceInt(Graph* graph_in1, Graph* graph_in2,
                                       Graph* graph_out){
    *graph_out = *graph_in1 - *graph_in2;
    return graph_out;
}

extern "C" Graph* graphProductInt(Graph* graph_in1, Graph* graph_in2,
                                     Graph* graph_out){
    *graph_out = *graph_in1 * *graph_in2;
    return graph_out;
}

extern "C" Graph* graphComplementInt(Graph* graph_in1, Graph* graph_out){
    *graph_out = !(*graph_in1);
    return graph_out;
}

#endif //MTMEX4_0_GRAPH_H
