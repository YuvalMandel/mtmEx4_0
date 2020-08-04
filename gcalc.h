#ifndef MTMEX4_0_GCALC_H
#define MTMEX4_0_GCALC_H

#include <map>
#include "graph.h"
using namespace std;

class GCalc {

private:
    map<string, Graph> graphs;

public:
    friend osstream print(string graphName);
    void delete(string graphName);
    osstream who();

};


#endif //MTMEX4_0_GCALC_H
