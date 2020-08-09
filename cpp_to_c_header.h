#ifndef EX4_CPP_TO_C_HEADER_H
#define EX4_CPP_TO_C_HEADER_H

struct Graph;

Graph* graphCreate();
Graph* create(){
    return graphCreate();
}

void graphDestroy(Graph* g);
void destroy(Graph* g){
    graphDestroy(g);
}

Graph* graphAddVertex(Graph* g, char* v);
Graph* addVertex(Graph* g, char* v){return graphAddVertex(g,v);}

Graph* graphAddEdge(Graph* g, char* v1, char* v2);
Graph* addEdge(Graph* g, char* v1, char* v2){return graphAddEdge(g,v1,v2);}

void graphDisp(Graph* g);
void disp(Graph* g){graphDisp(g);}

Graph* graphUnionInt(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphUnion(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    graphUnionInt(graph_in1 , graph_in2, graph_out);
    return graph_out;
}

Graph* graphIntersectionInt(Graph* graph_in1, Graph* graph_in2, Graph*
graph_out);
Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    graphIntersectionInt(graph_in1 , graph_in2, graph_out);
    return graph_out;
}

Graph* graphDifferenceInt(Graph* graph_in1, Graph* graph_in2, Graph*
graph_out);
Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    graphDifferenceInt(graph_in1 , graph_in2, graph_out);
    return graph_out;
}

Graph* graphProductInt(Graph* graph_in1, Graph* graph_in2, Graph*
graph_out);
Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    graphProductInt(graph_in1 , graph_in2, graph_out);
    return graph_out;
}

Graph* graphComplementInt(Graph* graph_in1, Graph* graph_out);
Graph* graphComplement(Graph* graph_in1, Graph* graph_out){
    graphComplementInt(graph_in1 , graph_out);
    return graph_out;
}

#endif //EX4_CPP_TO_C_HEADER_H
