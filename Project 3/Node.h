//
//  Node.h
//  Lab 3
//
//  Created by Seong-Eun Cho on 8/4/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <iostream>
#include <string>
#include <vector>
#include "Rule.h"

class Node {
    friend class Graph;
private:
    string name;
    Rule myRule;
    set<string> dependency;
    set<string> reverseDependency;
    int pon;
    bool mark = false;
public:
    int getPON(){
        return pon;
    }
    Rule getRule(){
        return myRule;
    }
    set<string> getDependency(){
        return dependency;
    }
};

#endif /* Node_h */
