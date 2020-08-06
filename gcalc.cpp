#include "gcalc.h"
#include <iterator>
#include <cctype>
#include <iostream>

using std::endl;
using std::string;
using std::map;
using std::exception;
using std::getline;

void Gcalc::remove(const std::string& graphName){

    std::map<std::string, Graph>::iterator it;
    it = this -> graphs.find(graphName);
    this -> graphs.erase(it);

}

void Gcalc::reset(){

    this -> graphs.clear();

}

std::ostream& operator<<(std::ostream &os, const Gcalc& gcalc){

    if(gcalc.graphs.empty()){
        return os;
    }

    for(map<string,Graph>::const_iterator it = gcalc.graphs.begin();
    it != gcalc.graphs.end(); ++it) {
        os << (it -> first) << endl;
    }

    return os;

}

string Gcalc::removeSpacesFromSides(const std::string& command){

    string current_string = command;

    while(current_string[0] == ' '){
        current_string.erase(0, 1);
    }

    while(current_string[current_string.length() - 1] == ' '){
        current_string.erase(current_string.size() - 1, 1);
    }

    return current_string;

}

bool Gcalc::checkReservedWord(const std::string& word){

    string shaved_word = this -> removeSpacesFromSides(word);

    if(shaved_word == "print" || shaved_word == "delete" ||
        shaved_word == "reset" || shaved_word == "who" ||
        shaved_word == "quit" || shaved_word == "saved" ||
        shaved_word == "load"){
        return true;
    }

    return false;

}

bool Gcalc::checkSpecialCommand(const std::string& command, const std::string&
token){

    if(command.substr(0,token.length()) == token){
        string sub_command = this -> removeSpacesFromSides(
                command.substr(
                        token.length(),command.length() - token.length()));

        if(sub_command[0] == '(' &&
            sub_command[sub_command.length() - 1] == ')'){

            return true;

        }
    }

    return false;

}

Edge Gcalc::createEdgeFromString(const std::string& str){

    Edge e;

    int location = str.find(',');

    if (location==std::string::npos)
        throw BadEdge();

    int bad_location = str.substr(location+1, str.size() - location - 1).find
            (',');

    if (!(bad_location==std::string::npos))
        throw BadEdge();

    if(str[0] == '<' && str[str.length() - 1] == '>'){

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

            if(this -> checkReservedWord(current)){
                throw BadVertex();
            }

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
                        Edge e = this->createEdgeFromString(current);
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

    if(shaved_exp[0] == '(' && shaved_exp[shaved_exp.length() - 1] == ')'){
        shaved_exp.erase(0,1);
        shaved_exp.erase(shaved_exp.size() - 1, 1);;
        g = this -> returnGraphFromExpression(shaved_exp);
        return g;
    }

    int i = int(shaved_exp.length()) - 1;

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

    std::cout << "shaved_exp before brackets: '" << shaved_exp << endl;
    std::cout << "shaved_exp[0]: '" << shaved_exp[0] << "'" << endl;
    std::cout << shaved_exp[shaved_exp.length() - 2] << endl;

    if(shaved_exp[0] == '{' && shaved_exp[shaved_exp.length() - 1] == '}'){
        std::cout << "got in side {} if"  << endl;
        g = this -> creatGraphFromString(shaved_exp);
        return g;
    }

    if(checkSpecialCommand(shaved_exp, "load")){

        shaved_exp = shaved_exp.substr(4, shaved_exp.length() - 4);

        return this -> load(shaved_exp);

    }

    map<string,Graph>::const_iterator it = this -> graphs.find(shaved_exp);
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

    if(this -> checkReservedWord(command)){
       return false;
    }

    return true;

}

void Gcalc::addGraph(const std::string& graph_name,const Graph& graph){

    this -> graphs[graph_name] = graph;

}

string Gcalc::returnGraphName(const string& graphName){

    string shaved_name = this -> removeSpacesFromSides(graphName);

    if(shaved_name[0] == '(' && shaved_name[shaved_name.size() - 1] == ')'){
        shaved_name.erase(0,1);
        shaved_name.erase(shaved_name.size() - 1, 1);;
        return this -> returnGraphName(shaved_name);
    }

    return shaved_name;

}

void Gcalc::save(const std::string& command){

    string shaved_command = this -> removeSpacesFromSides(command);
    if(shaved_command[0] == '(' &&
    shaved_command[shaved_command.length() - 1] == ')'){
        shaved_command.erase(0,1);
        shaved_command.erase(shaved_command.size() - 1, 1);;
    }

    int location = shaved_command.find(',');

    if (location==std::string::npos)
        throw BadSave();

    int bad_location = shaved_command.substr(
            location+1, shaved_command.size() - location - 1).find(',');

    if (!(bad_location==std::string::npos))
        throw BadSave();

    string graphName = this -> removeSpacesFromSides(
            shaved_command.substr(0,location));
    string fileName = this -> removeSpacesFromSides(
            shaved_command.substr(
                    location + 1, shaved_command.size() - location - 1));

    std::map<std::string, Graph>::iterator it;
    it = this -> graphs.find(graphName);
    it -> second.saveGraphToFile(fileName);

}

Graph Gcalc::load(const std::string& exp){

    string shaved_exp = this -> removeSpacesFromSides(exp);
    if(shaved_exp[0] == '(' && shaved_exp[shaved_exp.length() - 1] == ')'){
        shaved_exp.erase(0,1);
        shaved_exp.erase(shaved_exp.size() - 1, 1);;
        shaved_exp = this -> removeSpacesFromSides(shaved_exp);
    }

    return loadGraphFromFile(shaved_exp);

}

int Gcalc::handleCommand(std::ostream &os, const string& command){

    // First, we will remove any spaces from the sides.
    string shaved_command = this -> removeSpacesFromSides(command);

    // We will check if the commands are either "who", "reset" or "quit".
    if(shaved_command == "who"){
        os << *this;
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
            os << "Error: No Graph Exists with this name" << endl;
            return 0;
        }

        os << g;

        return 0;

    } else if(checkSpecialCommand(shaved_command, "delete")){

        expression_to_calc = shaved_command.substr(
                6, shaved_command.length() - 6);
        expression_to_calc = this ->returnGraphName(expression_to_calc);

        this -> remove(expression_to_calc);

        return 0;

    }
    else if(checkSpecialCommand(shaved_command, "save")){

        expression_to_calc = shaved_command.substr(
                4, shaved_command.length() - 4);

        this -> save(expression_to_calc);
        return 0;

    }

    // We will check if there is a single "="
    int equalsSignLocation = this -> returnEqualsSignLocation(shaved_command);

    if(equalsSignLocation != -1){

        // On the left side, we will check if it's valid graph name.
        string graph_name = this -> removeSpacesFromSides(
                shaved_command.substr(0, equalsSignLocation));

        if(!(this -> checkValidGraphName(graph_name))){
            os << "Error: Invalid Graph name" << endl;
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
            os << "Error: No Graph Exists with this name" << endl;
            return 0;
        } catch(BadVertex& e){
            os << "Error: Invalid Vertex" << endl;
            return 0;
        }catch(Graph::BadVertex& e){
            os << "Error: Invalid Vertex" << endl;
            return 0;
        } catch(BadEdge& e){
            os << "Error: Invalid Edge" << endl;
            return 0;
        }catch(Graph::BadEdge& e){
            os << "Error: Invalid Edge" << endl;
            return 0;
        }catch(Graph::CantReadFile& e){
            os << "Error: Can't read the file" << endl;
            return 0;
        }

        this -> addGraph(graph_name, graph);
        return 0;

    }

    // If all of them are false, this is an illegal command.
    os << "Error: Illegal command" << endl;
    return 0;

}

void prompt(){

    int exit = 0;
    string command;
    Gcalc gcalc;

    while(!exit){

        std::cout << "Gcalc> ";
        getline(std::cin,command);

        exit = gcalc.handleCommand(std::cout, command);

    };

}

void bash(const string& inputFileName, const string& outputFileName){

    int exit = 0;
    string command;
    Gcalc gcalc;

    std::ifstream input_file(inputFileName.c_str());
    std::ofstream output_file(outputFileName.c_str());

    if (input_file.is_open() ) {
        if (output_file.is_open()) {
            {
                while (getline(input_file, command) && !exit) {
                    std::cout << command << endl;
                    exit = gcalc.handleCommand(output_file, command);
                }
                input_file.close();
                output_file.close();
            }
        }else std::cout << "Error: Unable to open output file";
    }else std::cout << "Error: Unable to open input file";

}

int main(int argc, char *argv[]){

    // prompt
    if(argc == 1){

        prompt();

    } else if (argc == 3){

        bash(argv[1], argv[2]);

    }else{

        std::cout << "Error: Bad amount of args" << endl;

    }

    return 0;

}