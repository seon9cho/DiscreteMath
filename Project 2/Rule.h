//
//  Rule.h
//  Project 2
//
//  Created by Seong-Eun Cho on 7/6/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Rule_h
#define Rule_h
#include "Predicate.h"
using namespace std;

class Rule {
private:
    vector<Predicate> allPredicate;
public:
    Rule(){};
    
    void add(Predicate newPredicate){
        allPredicate.push_back(newPredicate);
    }
    
    string toString(){
        stringstream ss;
        ss << allPredicate[0].toString() << " :- ";
        for (unsigned int i = 1; i < allPredicate.size(); i++){
            if (i != allPredicate.size() - 1)
                ss << allPredicate[i].toString() << ",";
            else ss << allPredicate[i].toString();
        }
        return ss.str();
    }
    
    void clear(){
        allPredicate.clear();
    }
};

#endif /* Rule_h */
