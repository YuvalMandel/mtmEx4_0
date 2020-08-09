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

Graph* create();
void destroy(Graph* g);
Graph* addVertex(Graph* g, char* v);
Graph* addEdge(Graph* g, char* v1, char* v2);
void disp(Graph* g);

Graph* graphUnion(Graph* graph_in1, Graph* graph_in2,
                  Graph* graph_out);
Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2,
                         Graph* graph_out);
Graph* graphDifference(Graph* graph_in1, Graph* graph_in2,
                       Graph* graph_out);
Graph* graphProduct(Graph* graph_in1, Graph* graph_in2,
                    Graph* graph_out);
Graph* graphComplement(Graph* graph_in1, Graph* graph_out);

#endif //MTMEX4_0_GRAPH_H
