%module graph
%{
#include "graph.h"
%}
class Graph {
public:
	Graph create();
	void destroy(Graph& g);
	Graph& addVertex(Graph& g, Vertex v);
	Graph& addEdge(Graph& g, const Vertex& v1, const Vertex& v2);
	void disp(const Graph& g);
	Graph& graphUnion(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
	Graph& graphIntersection(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
	Graph& graphDifference(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
	Graph& graphProduct(const Graph& graph_in1, const Graph& graph_in2, Graph& graph_out);
	Graph& graphComplement(const Graph& graph_in1, Graph& graph_out);
};