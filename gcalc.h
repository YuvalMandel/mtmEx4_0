#ifndef MTMEX4_0_GCALC_H
#define MTMEX4_0_GCALC_H

#include <iostream>
#include <exception>
#include <map>
#include "graph.h"

class Gcalc {

private:

    std::map<std::string, Graph> graphs;
    Graph calcTwoExpressions(const std::string& leftSide,
                             const std::string& rightSide,
                             const char& symbol);
    std::string removeSpacesAndBracketsFromSides(const std::string& graphName);
    bool checkReservedWord(const std::string& word);
    std::pair<std::string, std::string> createEdgeFromString(const std::string&
    str);
    Graph createGraphFromString(const std::string& exp);
    bool checkValidGraphName(const std::string& command);
    static std::string removeSpacesFromSides(const std::string& command);
    static int returnEqualsSignLocation(const std::string& command);
    Graph returnGraphFromExpression(const std::string& exp);
    bool checkSpecialCommand(const std::string& command,
                             const std::string& token);
    void addGraph(const std::string& graph_name,const Graph& graph);
    void save(const std::string& command);
    Graph load(const std::string& exp);
    void remove(const std::string& graphName);
    void reset();
    friend std::ostream& operator<<(std::ostream &os, const Gcalc& gcalc);


public:

    int handleCommand(std::ostream &os, const std::string& command);

};


#endif //MTMEX4_0_GCALC_H
