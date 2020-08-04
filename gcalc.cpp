#include "gcalc.h"
#include <iterator>
using std::endl;
using std::string;
using std::map;

void Gcalc::remove(const std::string& graph_name){

    std::map<std::string, Graph>::iterator it;
    it = this -> graphs.find(graph_name);
    this -> graphs.erase(it);

}

void Gcalc::reset(){

    this -> graphs.clear();

}

Graph Gcalc::getGraph(const std::string& graph_name){

    return this -> graphs[graph_name];

}

std::ostream& operator<<(std::ostream &os, const Gcalc& gcalc){

//    map<string, Graph>::iterator it = gcalc.graphs.begin();

    for(auto it = gcalc.graphs.begin(); it != gcalc.graphs.end(); ++it) {
        os << (it -> second) << endl;
    }

    return os;

}

bool handleCommand(string command){

    return false;

}

void prompt(){

    bool exit = false;
    string command;

    while(!exit){

        std::cout << "Gcalc> ";
        std::cin >> command;

        exit = handleCommand(command);

        exit = true;

    };

}

int main(int argc, char *argv[]){

    // prompt
    if(argc == 1){

        prompt();

    } else if (argc == 3){



    }else{

        std::cout << "Error: Bad amount of args" << endl;

    }

}