%module graph
%include "std_string.i"
%{
#include "graph.h"
%}
class Graph {};

Graph create();
void destroy(Graph& g);
Graph addVertex(Graph& g, const std::string& v);
Graph addEdge(Graph& g, const std::string& v1, const std::string& v2);
void disp(const Graph& g);
Graph graphUnion(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
Graph graphIntersection(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
Graph graphDifference(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
Graph graphProduct(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
Graph graphComplement(const Graph& graph_in1, Graph& graph_out);