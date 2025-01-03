//
//  DatalogProgram.h
//  Project 2
//
//  Created by Seong-Eun Cho on 7/6/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef DatalogProgram_h
#define DatalogProgram_h
#include <set>
#include "Rule.h"
using namespace std;

struct Comparator {
    bool operator() (string lhs, string rhs){
        return lhs < rhs;
    }
};

class DatalogProgram {
    friend class Parser;
    friend class Interpreter;
private:
    vector<Predicate> mySchemes;
    vector<Predicate> myFacts;
    vector<Rule> myRules;
    vector<Predicate> myQueries;
    set<string, Comparator> myDomain;
public:
    DatalogProgram(){};
    ~DatalogProgram(){
        clear();
    }
    
    string toString(){
        stringstream ss;
        ss << "Schemes(" << mySchemes.size() << "):\n";
        for (unsigned int i = 0; i < mySchemes.size(); i++){
            ss << "  " << mySchemes[i].toString() << endl;
        }
        ss << "Facts(" << myFacts.size() << "):\n";
        for (unsigned int i = 0; i < myFacts.size(); i++){
            ss << "  " << myFacts[i].toString() << endl;
        }
        ss << "Rules(" << myRules.size() << "):\n";
        for (unsigned int i = 0; i < myRules.size(); i++){
            ss << "  " << myRules[i].toString() << endl;
        }
        ss << "Queries(" << myQueries.size() << "):\n";
        for (unsigned int i = 0; i < myQueries.size(); i++){
            ss << "  " << myQueries[i].toString() << endl;
        }
        ss << "Domain(" << myDomain.size() << "):\n";
        set<string, Comparator>::iterator it;
        for (it = myDomain.begin(); it != myDomain.end(); it++){
            ss << "  " << *it << endl;
        }
        return ss.str();
    }
    void clear(){
        mySchemes.clear();
        myFacts.clear();
        myRules.clear();
        myQueries.clear();
        myDomain.clear();
    }
    
};

#endif /* DatalogProgram_h */
