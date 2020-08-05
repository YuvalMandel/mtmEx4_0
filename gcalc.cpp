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

string Gcalc::removeSpacesFromSides(const std::string& command){

    string current_string = command;

    while(current_string[0] == ' '){
        current_string.erase(0);
    }

    while(current_string.back() == ' '){
        current_string.pop_back();
    }

    return current_string;

}

bool Gcalc::checkSpecialCommand(const std::string& command, const std::string&
token){

    if(command.substr(0,token.length()) == token){
        string sub_command = this -> removeSpacesFromSides(
                command.substr(
                        token.length() + 1,command.length() - token.length()));

        if(sub_command[0] == '(' && sub_command.back()){

            return true;

        }
    }

    return false;

}

Graph returnGraphFromExpression(const std::string& command){

    Graph g;

    return g;

}

int Gcalc::handleCommand(const string& command){

    // First, we will remove any spaces from the sides.
    string shaved_command = this -> removeSpacesFromSides(command);

    // We will check if the commands are either "who", "reset" or "quit".
    if(shaved_command == "who"){
        std::cout << this;
        return 0;
    } else if (shaved_command == "reset"){
        this -> reset();
        return 0;
    } else if (shaved_command == "quit"){
        return 1;
    }

    string expression_to_calc;

    // We will check if the command is "print", "save", "load" with  round
    // brackets. If it is, we will calc the expression inside the brackets,
    // and use the special function on them.
    if(checkSpecialCommand(shaved_command, "print")){

        expression_to_calc = shaved_command.substr(
                5, shaved_command.length() - 5);

        std::cout << this -> returnGraphFromExpression(expression_to_calc);

        return 0;

    } else if(checkSpecialCommand(shaved_command, "save")){

        return 0;

    } else if(checkSpecialCommand(shaved_command, "load")){

        return 0;

    }

    // We will check if there is a single "="

        // On the left side, we will check if it's valid graph name.

        // On the right side, we will calc the expression to a graph.

    // If all of them are false, this is an illegal command.

}

void prompt(){

    int exit = 0;
    string command;
    Gcalc gcalc;

    while(!exit){

        std::cout << "Gcalc> ";
        std::cin >> command;

        exit = gcalc.handleCommand(command);

        exit = 1;

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