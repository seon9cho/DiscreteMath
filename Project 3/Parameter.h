//
//  Parameter.h
//  Project 2
//
//  Created by Seong-Eun Cho on 7/6/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Parameter_h
#define Parameter_h
#include <string>
using namespace std;

class Parameter {
private:
    string data;
public:
    Parameter(string data){
        this->data = data;
    }
    string toString(){
        return data;
    }
};

#endif /* Parameter_h */
