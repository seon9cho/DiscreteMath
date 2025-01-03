//
//  Interpreter.cpp
//  Lab 3
//
//  Created by Seong-Eun Cho on 7/20/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#include <stdio.h>
#include "Interpreter.h"
using namespace std;

void Interpreter::addParser(Parser parse, string fileName){
    this->parse = parse;
    this->fileName = fileName;
}

void Interpreter::schemeEvaluation(){
    for (unsigned int i = 0; i < parse.myDatalog.mySchemes.size(); i++){
        myDatabase.addScheme(parse.myDatalog.mySchemes[i].getPredicateID(), parse.myDatalog.mySchemes[i].getAllParameter());
    }
}

void Interpreter::factEvaluation(){
    for (unsigned int i = 0; i < parse.myDatalog.myFacts.size(); i++){
        myDatabase.addTuple(parse.myDatalog.myFacts[i].getPredicateID(), parse.myDatalog.myFacts[i].getAllParameter());
    }
}

string Interpreter::dependencyEvaluation(){
    stringstream ss;
    myGraph.receiveRules(parse.myDatalog.myRules);
    ss << myGraph.print();
    for (unsigned int i = 0; i < myGraph.SCC.size(); i++){
        ss << "SCC:";
        for (unsigned int j = 0; j < myGraph.SCC[i].size(); j++){
            ss << " " << myGraph.SCC[i][j];
        }
        ss << endl;
        ss << ruleEvaluation(myGraph.SCC[i]);
    }
    return ss.str();
}

string Interpreter::ruleEvaluation(const vector<string>& SCC){
    stringstream ss;
    int change = 1;
    int count = 0;
    while (change != 0){
        change = 0;
        for (unsigned int i = 0; i < SCC.size(); i++){
            Relation productRelation;
            productRelation.addName(myGraph.myNodes[SCC[i]].getRule().getProduct().getPredicateID());
            productRelation.addScheme(myGraph.myNodes[SCC[i]].getRule().getProduct().getAllParameter());
            vector<Relation> allPredicateRelations;
            for (unsigned int j = 0; j < myGraph.myNodes[SCC[i]].getRule().getAllPredicate().size(); j++){
                Relation currentRelation;
                currentRelation.addName(myGraph.myNodes[SCC[i]].getRule().getAllPredicate().at(j).getPredicateID());
                currentRelation.addScheme(myGraph.myNodes[SCC[i]].getRule().getAllPredicate().at(j).getAllParameter());
                allPredicateRelations.push_back(currentRelation);
            }
            ss << myGraph.myNodes[SCC[i]].getRule().toString() << endl;
            ss << myDatabase.evaluateRule(productRelation, allPredicateRelations, change);
        }
        selfDependency(SCC, change);
        count++;
    }
    ss << endl;
    
    return ss.str();
}

void Interpreter::selfDependency(const vector<string>& SCC, int& change){
    bool selfDependent = false;
    if (SCC.size() == 1){
        for (auto d : myGraph.myNodes[SCC[0]].getDependency()){
            if (SCC[0] == d){
                selfDependent = true;
            }
        }
    } else selfDependent = true;
    if (!selfDependent){
        change = 0;
    }
}

string Interpreter::queryEvaluation(){
    stringstream ss;
    for (unsigned int i = 0; i < parse.myDatalog.myQueries.size(); i++){
        ss << parse.myDatalog.myQueries[i].toString() << "? ";
        ss << myDatabase.evaluateQuery(parse.myDatalog.myQueries[i].getPredicateID(), parse.myDatalog.myQueries[i].getAllParameter());
    }
    return ss.str();
}

void Interpreter::print(){
    ofstream outfile(fileName);
    stringstream ss;
    ss << "Scheme Evaluation\n" << endl;
    schemeEvaluation();
    
    ss << "Fact Evaluation\n" << endl;
    factEvaluation();
    map<string, Relation>::iterator it;
    for (it = myDatabase.allData.begin(); it != myDatabase.allData.end(); it++){
        ss << it->second.printTuples();
    }
    
    ss << "Rule Evaluation\n" << endl;
    ss << dependencyEvaluation();
    ss << "Rule Evaluation Complete\n" << endl;
    for (auto m : myDatabase.allData){
        ss << m.second.printTuples();
    }
    
    ss << "Query Evaluation\n" << endl;
    ss << queryEvaluation();
    cout << ss.str();
    outfile << ss.str();
}