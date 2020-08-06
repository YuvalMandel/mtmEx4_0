#ifndef MTMEX4_0_GCALC_H
#define MTMEX4_0_GCALC_H

#include <iostream>
#include <exception>
#include <map>
#include "graph.h"

class Gcalc {

private:
    std::map<std::string, Graph> graphs;

public:

    void remove(const std::string& graph_name);
    void reset();
    int handleCommand(std::ostream &os, const std::string& command);
    bool checkSpecialCommand(const std::string& command,
            const std::string& token);
    static std::string removeSpacesFromSides(const std::string& command);
    static int returnEqualsSignLocation(const std::string& command);
    Graph returnGraphFromExpression(const std::string& exp);
    static bool checkValidGraphName(const std::string& command);
    Graph creatGraphFromString(const std::string& exp);
    void addGraph(const std::string& graph_name,const Graph& graph);
    Edge createEdgeFromString(const std::string& str);
    Graph calcTwoExpressions(const std::string& leftSide,
                             const std::string& rightSide,
                             const char& symbol);
    std::string returnGraphName(const std::string& graphName);
    friend std::ostream& operator<<(std::ostream &os, const Gcalc& gcalc);

    class BadEdge: public std::exception{};
    class noGraph: public std::exception{};

};


#endif //MTMEX4_0_GCALC_H
