//
//  Parser.h
//  Project 1
//
//  Created by Seong-Eun Cho on 6/30/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Parser_h
#define Parser_h
#include "Scanner.h"
#include "DatalogProgram.h"
using namespace std;

class Parser {
private:
    Token currentToken;
    Scanner scan;
    int i = 0;
    bool parseError = false;
    DatalogProgram myDatalog;
    Predicate currentPredicate;
    Rule currentRule;
    string fileName;
public:
    Parser(Scanner scan, string fileName);
    void parseFile();
    
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void predicateList();
    void predicate();
    void parameterList();
    void parameter();
    void match(Type matchingType);
    void error();
    
    void print();
};

#endif /* Parser_h */
