//
//  Parser.cpp
//  Project 2
//
//  Created by Seong-Eun Cho on 6/30/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#include <stdio.h>
#include "Parser.h"
using namespace std;

Parser::Parser(Scanner scan, string fileName){
    this->scan = scan;
    this->fileName = fileName;
    currentToken = scan.tokenHolder[i];
}

void Parser::parseFile(){
    
}

void Parser::datalogProgram(){
    if (currentToken.tokenType == SCHEMES){
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(EOFILE);
    }
    else error();
}

void Parser::schemeList(){
    if (currentToken.tokenType == ID){
        scheme();
        schemeList();
    }
    else;
}

void Parser::factList(){
    if (currentToken.tokenType == ID){
        fact();
        factList();
    }
    else;
}

void Parser::ruleList(){
    if (currentToken.tokenType == ID){
        rule();
        ruleList();
    }
    else;
}

void Parser::queryList(){
    if (currentToken.tokenType == ID){
        query();
        queryList();
    }
    else;
}

void Parser::scheme(){
    if (currentToken.tokenType == ID){
        currentPredicate.addID(currentToken.data);
        predicate();
        myDatalog.mySchemes.push_back(currentPredicate);
        currentPredicate.clear();
    }
    else error();
}

void Parser::fact(){
    if (currentToken.tokenType == ID){
        currentPredicate.addID(currentToken.data);
        predicate();
        myDatalog.myFacts.push_back(currentPredicate);
        currentPredicate.clear();
        match(PERIOD);
    }
    else error();
}

void Parser::rule(){
    if (currentToken.tokenType == ID){
        currentPredicate.addID(currentToken.data);
        predicate();
        currentRule.add(currentPredicate);
        currentPredicate.clear();
        
        match(COLON_DASH);
        
        currentPredicate.addID(currentToken.data);
        predicate();
        currentRule.add(currentPredicate);
        currentPredicate.clear();
        
        predicateList();
        myDatalog.myRules.push_back(currentRule);
        currentRule.clear();
        match(PERIOD);
    }
    else error();
}

void Parser::query(){
    if (currentToken.tokenType == ID){
        currentPredicate.addID(currentToken.data);
        predicate();
        myDatalog.myQueries.push_back(currentPredicate);
        currentPredicate.clear();
        match(Q_MARK);
    }
    else error();
}

void Parser::predicateList(){
    if (currentToken.tokenType == COMMA){
        match(COMMA);
        currentPredicate.addID(currentToken.data);
        predicate();
        currentRule.add(currentPredicate);
        currentPredicate.clear();
        predicateList();
    }
    else;
}

void Parser::predicate(){
    if (currentToken.tokenType == ID){
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
    }
    else error();
}

void Parser::parameterList(){
    if (currentToken.tokenType == COMMA){
        match(COMMA);
        parameter();
        parameterList();
    }
    else;
}

void Parser::parameter(){
    if (currentToken.tokenType == STRING){
        currentPredicate.addParameter(currentToken.data);
        myDatalog.myDomain.insert(currentToken.data);
        match(STRING);
    }
    else if (currentToken.tokenType == ID){
        currentPredicate.addParameter(currentToken.data);
        match(ID);
    }
    else error();
}

void Parser::match(Type matchingType){
    if (currentToken.tokenType == matchingType){
        i++;
        currentToken = scan.tokenHolder[i];
    }
    else error();
}

void Parser::error(){
    ofstream outFile(fileName);
    parseError = true;
    cout << "Failure!\n"
        << "  (" << currentToken.typeToString() << ",\"" << currentToken.data << "\"," << currentToken.line << ")" << endl;
    outFile << "Failure!\n"
        << "  (" << currentToken.typeToString() << ",\"" << currentToken.data << "\"," << currentToken.line << ")" << endl;
    exit(0);
}

void Parser::print(){
    ofstream outFile(fileName);
    cout << "Success!\n"
    << myDatalog.toString();
    outFile << "Success!\n"
    << myDatalog.toString();
}

