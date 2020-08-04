#ifndef MTMEX4_0_GRAPH_H
#define MTMEX4_0_GRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <string>

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

    bool checkEdgePossible(const Edge& e);
    void addVertex(const Vertex& v);
    void addEdge(const Edge& e);
    friend Graph operator+(const Graph& g1, const Graph& g2);
    friend Graph operator-(const Graph& g1, const Graph& g2);
    friend Graph operator^(const Graph& g1, const Graph& g2);
    friend Graph operator*(const Graph& g1, const Graph& g2);
    friend Graph operator!(const Graph& g);
    friend std::ostream& operator<<(std::ostream &os, const Graph &g);

};


#endif //MTMEX4_0_GRAPH_H
