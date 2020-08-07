#ifndef MTMEX4_0_GRAPH_H
#define MTMEX4_0_GRAPH_H

#include <iostream>
#include <set>
#include <fstream>

#define Vertex std::string
#define Edge std::pair<Vertex, Vertex>

//class Vertex: public std::string{
//
//    using std::string::string;
//
//};
//class Edge: public std::pair<Vertex, Vertex>{
//
//    using pair::pair;
//    friend std::ostream& operator<<(std::ostream &os, const Edge &e);
//
//};

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

    class BadVertex: public std::exception{};
    class BadEdge: public std::exception{};
    class CantReadFile: public std::exception{};

};

Graph loadGraphFromFile(const std::string& fileName);

Graph create();
void destroy(Graph& g);
Graph& addVertex(Graph& g, Vertex v);
Graph& addEdge(Graph& g, const Vertex& v1, const Vertex& v2);
void disp(const Graph& g);

Graph& graphUnion(const Graph& graph_in1, const Graph& graph_in2,
                  Graph& graph_out);
Graph& graphIntersection(const Graph& graph_in1, const Graph& graph_in2,
                         Graph& graph_out);
Graph& graphDifference(const Graph& graph_in1, const Graph& graph_in2,
                       Graph& graph_out);
Graph& graphProduct(const Graph& graph_in1, const Graph& graph_in2,
                    Graph& graph_out);
Graph& graphComplement(const Graph& graph_in1, Graph& graph_out);

#endif //MTMEX4_0_GRAPH_H
