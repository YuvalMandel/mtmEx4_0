#include "gcalc.h"
#include <iterator>
#include <cctype>
#include <iostream>
using std::endl;
using std::string;
using std::map;
using std::exception;
using std::getline;

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

    if(gcalc.graphs.empty()){
        return os;
    }

    for(auto it = gcalc.graphs.begin(); it != gcalc.graphs.end(); ++it) {
        os << (it -> first) << endl;
    }

    return os;

}

string Gcalc::removeSpacesFromSides(const std::string& command){

    string current_string = command;

    while(current_string[0] == ' '){
        current_string.erase(0, 1);
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
                        token.length(),command.length() - token.length()));

        if(sub_command[0] == '(' && sub_command.back() == ')'){

            return true;

        }
    }

    return false;

}

Edge Gcalc::creatEdgeFromString(const std::string& str){

    Edge e;

    if(str[0] == '<' && str.back() == '>'){

        int location = str.find(',');

        string leftSide = str.substr(1,location-1);
        string rightSide = str.substr(location+1,str.length()-location-2);

        leftSide = this -> removeSpacesFromSides(leftSide);
        rightSide = this -> removeSpacesFromSides(rightSide);

        e.first = leftSide;
        e.second = rightSide;

    }else{
        throw BadEdge();
    }

    return e;

}

Graph Gcalc::creatGraphFromString(const std::string& exp){

    Graph g;
    int i = 1;
    string current;

    while(exp[i] != '|' && exp[i] != '}'){

        if(exp[i] != ','){
            current += exp[i];
        }else{

            current = this -> removeSpacesFromSides(current);

            if(!current.empty()){
                g.addVertex(current);
                current = "";
            }
        }

        ++i;

    }

    current = this -> removeSpacesFromSides(current);

    if(!current.empty()){
        g.addVertex(current);
        current = "";
    }

    if(exp[i] == '|'){

        i++;

        bool expecting_comma = false;

        while(exp[i] != '}'){

            if(!expecting_comma) {

                current += exp[i];

                if (exp[i] == ' ') { ;
                } else if (exp[i] == '>') {

                    current = this->removeSpacesFromSides(current);

                    if (!current.empty()) {
                        Edge e = this->creatEdgeFromString(current);
                        g.addEdge(e);
                        current = "";
                    }

                    expecting_comma = true;
                }
            }else{
                if(exp[i] == ' '){
                    ;
                }else if(exp[i] == ','){
                    expecting_comma = false;
                }else{
                    throw BadEdge();
                }
            }
            ++i;
        }
    }

    return g;

}

Graph Gcalc::calcTwoExpressions(const std::string& leftSide,
                         const std::string& rightSide, const char& symbol){

    Graph leftGraph = this -> returnGraphFromExpression(leftSide);
    Graph rightGraph = this -> returnGraphFromExpression(rightSide);

    if(symbol == '+'){
        return leftGraph + rightGraph;
    }

    switch (symbol) {
        case '+' : return leftGraph + rightGraph;
        case '-' : return leftGraph - rightGraph;
        case '*' : return leftGraph * rightGraph;
        case '^' : return leftGraph ^ rightGraph;
        default: return leftGraph + rightGraph;
    }

}

Graph Gcalc::returnGraphFromExpression(const std::string& exp){

    Graph g;

    string shaved_exp = this -> removeSpacesFromSides(exp);

    if(shaved_exp[0] == '(' && shaved_exp.back() == ')'){
        shaved_exp.erase(0,1);
        shaved_exp.pop_back();
        g = this -> returnGraphFromExpression(shaved_exp);
        return g;
    }

    int i = shaved_exp.length() - 1;

    int brackets_count = 0;

    while(i >= 0){

        if(exp[i] == ')'){
            brackets_count--;
        }
        if(exp[i] == '('){
            brackets_count++;
        }

        if((brackets_count == 0) &&
        (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '^')){

            string leftSide = exp.substr(0, i);
            string rightSide = exp.substr(i + 1, exp.length() - i - 1);

            return this -> calcTwoExpressions(leftSide, rightSide, exp[i]);

        }

        --i;

    }

    if(shaved_exp[0] == '!'){
        g = !this -> returnGraphFromExpression(shaved_exp.erase(0, 1));
        return g;
    }

    if(shaved_exp[0] == '{' && shaved_exp.back() == '}'){
        g = this -> creatGraphFromString(shaved_exp);
        return g;
    }

    std::map<string,Graph>::iterator it = this -> graphs.find(shaved_exp);
    if (it != this -> graphs.end()){
        return it -> second;
    }

    throw noGraph();

}

int Gcalc::returnEqualsSignLocation(const std::string& command){

    bool found = false;

    int location = command.find('=');

    if (location!=std::string::npos)
        found = true;

    int bad_location = command.substr(
            location+1,command.length() - location).find('=');

    if (bad_location!=std::string::npos || !found) {
        return -1;
    }

    return location;

}

bool Gcalc::checkValidGraphName(const string& command){

    if(!isalpha(command[0])){
        return false;
    }

    for (int i = 0; i < command.length(); ++i) {
        if(!isalnum(command[i])){
            return false;
        }
    }

    return true;

}

void Gcalc::addGraph(const std::string& graph_name,const Graph& graph){

    this -> graphs[graph_name] = graph;

}

string Gcalc::returnGraphName(const string& graphName){

    string shaved_name = this -> removeSpacesFromSides(graphName);

    if(shaved_name[0] == '(' && shaved_name.back() == ')'){
        shaved_name.erase(0,1);
        shaved_name.pop_back();
        return this -> returnGraphName(shaved_name);
    }

    return shaved_name;

}

int Gcalc::handleCommand(const string& command){

    // First, we will remove any spaces from the sides.
    string shaved_command = this -> removeSpacesFromSides(command);

    // We will check if the commands are either "who", "reset" or "quit".
    if(shaved_command == "who"){
        std::cout << *this;
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

        Graph g;

        try{
            g = this -> returnGraphFromExpression(expression_to_calc);
        }catch(noGraph& e){
            std::cout << "Error: No Graph Exists with this name" << endl;
            return 0;
        }

        std::cout << g;

        return 0;

    } else if(checkSpecialCommand(shaved_command, "delete")){

        expression_to_calc = shaved_command.substr(
                6, shaved_command.length() - 6);
        expression_to_calc = this ->returnGraphName(expression_to_calc);

        this -> graphs.erase(expression_to_calc);

        return 0;

    } else if(checkSpecialCommand(shaved_command, "save")){

        return 0;

    } else if(checkSpecialCommand(shaved_command, "load")){

        return 0;

    }

    // We will check if there is a single "="
    int equalsSignLocation = this -> returnEqualsSignLocation(shaved_command);

    if(equalsSignLocation != -1){

        // On the left side, we will check if it's valid graph name.
        string graph_name = this -> removeSpacesFromSides(
                shaved_command.substr(0, equalsSignLocation));

        if(!(this -> checkValidGraphName(graph_name))){
            std::cout << "Error: Invalid Graph name" << endl;
            return 0;
        }

        // On the right side, we will calc the expression to a graph.
        string graph_expression = this -> removeSpacesFromSides(
                shaved_command.substr(equalsSignLocation + 1,
                        shaved_command.length() -equalsSignLocation - 1));

        Graph graph;

        try {
            graph = this -> returnGraphFromExpression(graph_expression);
        } catch(noGraph& e){
            std::cout << "Error: No Graph Exists with this name" << endl;
            return 0;
        }

        this -> addGraph(graph_name, graph);
        return 0;

    }

    // If all of them are false, this is an illegal command.
    std::cout << "Error: Illegal command" << endl;
    return 0;

}

void prompt(){

    int exit = 0;
    string command;
    Gcalc gcalc;

    while(!exit){

        std::cout << "Gcalc>";
        getline(std::cin,command);

        exit = gcalc.handleCommand(command);

    };

}

int main(int argc, char *argv[]){

    // prompt
    if(argc == 1){

        prompt();

    } else if (argc == 3){

        std::cout << argv[1] << " " << argv[2] << endl;

    }else{

        std::cout << "Error: Bad amount of args" << endl;

    }

}