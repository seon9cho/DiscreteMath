//
//  Predicate.h
//  Project 2
//
//  Created by Seong-Eun Cho on 7/6/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Predicate_h
#define Predicate_h
#include <vector>
#include <sstream>
#include "Parameter.h"
using namespace std;

class Predicate {
private:
    string predicateID;
    vector<Parameter> allParameter;
public:
    Predicate(){};
    ~Predicate(){
        clear();
    }
    
    void addID(string content){
        predicateID = content;
    }
    
    void addParameter(string content){
        Parameter newParameter(content);
        allParameter.push_back(newParameter);
    }
    string getPredicateID(){
        return predicateID;
    }
    vector<string> getAllParameter(){
        vector<string> allParameterToString;
        for (unsigned int i = 0; i < allParameter.size(); i++){
            allParameterToString.push_back(allParameter[i].toString());
        }
        return allParameterToString;
    }
    string toString(){
        stringstream ss;
        ss << predicateID << "(";
        for (unsigned int i = 0; i < allParameter.size(); i++){
            if (i != allParameter.size() - 1)
                ss << allParameter[i].toString() << ",";
            else ss << allParameter[i].toString() << ")";
        }
        return ss.str();
    }
    
    void clear(){
        predicateID = "";
        allParameter.clear();
    }
};

#endif /* Predicate_h */
