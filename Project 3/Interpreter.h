//
//  Interpreter.h
//  Lab 3
//
//  Created by Seong-Eun Cho on 7/20/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h
#include "Parser.h"
#include "Database.h"
#include "Graph.h"
using namespace std;

class Interpreter {
private:
    Parser parse;
    Database myDatabase;
    string fileName;
    Graph myGraph;
public:
    void addParser(Parser parse, string fileName);
    
    void schemeEvaluation();
    void factEvaluation();
    string dependencyEvaluation();
    string ruleEvaluation(const vector<string>& SCC);
    void selfDependency(const vector<string>& SCC, int& change);
    string queryEvaluation();
    
    void print();
};

#endif /* Interpreter_h */
