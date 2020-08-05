#ifndef MTMEX4_0_GCALC_H
#define MTMEX4_0_GCALC_H

#include <iostream>
#include <map>
#include "graph.h"

class Gcalc {

private:
    std::map<std::string, Graph> graphs;

public:

    void remove(const std::string& graph_name);
    void reset();
    int handleCommand(const std::string& command);
    bool checkSpecialCommand(const std::string& command,
            const std::string& token);
    static std::string removeSpacesFromSides(const std::string& command);
    Graph returnGraphFromExpression(const std::string& command);
    Graph getGraph(const std::string& graph_name);
    friend std::ostream& operator<<(std::ostream &os, const Gcalc& gcalc);

};


#endif //MTMEX4_0_GCALC_H
