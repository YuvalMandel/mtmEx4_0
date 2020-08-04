#include "graph.h"
#include <algorithm>
#include <set>
//using namespace Graph;
using std::endl;
//using std::set_union;

using std::ostream;
using std::set;
using std::string;
using std::pair;

void Graph::addVertex(const Vertex& v){

    this -> vertexes.insert(v);

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

void Graph::addEdge(const Edge& e){

    if(this -> checkEdgePossible(e)){
        this -> edges.insert(e);
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
//    g1.addVertex(v1);
//    g1.addVertex(v2);
//    g1.addVertex(v3);
//    g2.addVertex(v3);
//    g2.addVertex(v4);
//    g1.addEdge(e12);
//    g2.addEdge(e34);
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
