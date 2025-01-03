//
//  Relation.h
//  Lab 3
//
//  Created by Seong-Eun Cho on 7/20/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Relation_h
#define Relation_h
#include "Scheme.h"
#include "Tuple.h"
#include <set>
#include <sstream>
using namespace std;

class Relation {
    friend class Database;
    friend class Interpreter;
private:
    string name;
    Scheme schemeNames;
    Scheme schemeRenames;
    set<Tuple> allTuples;
    struct qValue{
        string content = "";
        string var = "";
    };
    vector<qValue> currentQuery;
    set<Tuple> selectedTuples;
public:
    void addName (string name){
        this->name = name;
    }
    void addScheme (vector<string> attributes){
        for (unsigned int i = 0; i < attributes.size(); i++){
            schemeNames.push_back(attributes[i]);
        }
    }
    void addTuple (vector<string> values){
        Tuple currentTuple;
        for (unsigned int i = 0; i < values.size(); i++){
            currentTuple.push_back(values[i]);
        }
        allTuples.insert(currentTuple);
    }
    string getName(){
        return name;
    }
    
    bool canJoin (const Relation& r2, const Tuple& t1, const Tuple& t2, const Scheme& s1){
        vector<pair<int, int>> indexes;
        for (unsigned int i = 0; i < s1.size(); i++){
            for (unsigned int j = 0; j < r2.schemeNames.size(); j++){
                if (s1[i] == r2.schemeNames[j]){
                    indexes.push_back(pair<int, int>(i, j));
                }
            }
        }
        for (unsigned int i = 0; i < indexes.size(); i++){
            if (t1[indexes[i].first] != t2[indexes[i].second]){
                return false;
            }
        }
        
        return true;
    }
    void join(Tuple t1, Tuple t2){
        for (unsigned int i = 0; i < t2.size(); i++){
            t1.push_back(t2[i]);
        }
        allTuples.insert(t1);
    }
    void deleteRemainingTuples(){
        set<Tuple> tempSet;
        for (auto T : allTuples){
            if (T.size() == schemeNames.size()){
                tempSet.insert(T);
            }
        }
        allTuples.clear();
        allTuples = tempSet;
    }
    
    void applyRule (const Relation& r1){
        vector<int> indexes;
        for (unsigned int i = 0; i < schemeNames.size(); i++){
            for (unsigned int j = 0; j < r1.schemeNames.size(); j++){
                if (schemeNames[i] == r1.schemeNames[j]){
                    indexes.push_back(j);
                    break;
                }
            }
        }
        for (auto T : r1.allTuples){
            Tuple tempT;
            for (unsigned int i = 0; i < indexes.size(); i++){
                tempT.push_back(T[indexes[i]]);
            }
            allTuples.insert(tempT);
        }
    }
    
    string evaluateQuery(vector<string> values){
        int count = 0;
        giveQValue(values);
        for (unsigned int i = 0; i < currentQuery.size(); i++){
            schemeRenames.push_back(currentQuery[i].var);
        }
        for (set<Tuple>::iterator it = allTuples.begin(); it != allTuples.end(); it++){
            bool validity = true;
            select(validity, it);
            if (validity == true){
                selectedTuples.insert(*it);
                count++;
            }
        }
        return printQuery(count);
    }
    void select(bool &validity, set<Tuple>::iterator it){
        vector<qValue> tempQValues = currentQuery;
        for (unsigned int i = 0; i < it->size(); i++){
            if (tempQValues[i].var != "" && tempQValues[i].content == ""){
                tempQValues[i].content = it->at(i);
                for (unsigned int j = i; j < tempQValues.size(); j++){
                    if (tempQValues[i].var == tempQValues[j].var){
                        tempQValues[j].content = tempQValues[i].content;
                    }
                }
            } else {
                if (tempQValues[i].content != it->at(i)){
                    validity = false;
                    break;
                }
            }
        }
    }
    string project(){
        stringstream ss;
        ss << "project\n";
        bool empty = true;
        determineEmpty(empty);
        if (empty == false){
            for (set<Tuple>::iterator it = selectedTuples.begin(); it != selectedTuples.end(); it++){
                ss << " ";
                for (unsigned int i = 0; i < schemeNames.size(); i++){
                    bool repeat = false;
                    if (i > 0){
                        for (int j = i - 1; j >= 0; j--){
                            if (schemeRenames[i] == schemeRenames[j]){
                                repeat = true;
                            }
                        }
                    }
                    if (schemeRenames[i] != "" && repeat == false){
                        ss << " " << schemeNames[i] << "=" << it->at(i);
                    }
                }
                ss << endl;
            }
        }
        return ss.str();
    }
    string rename(){
        stringstream ss;
        ss << "rename\n";
        bool empty = true;
        determineEmpty(empty);
        if (empty == false){
            for (set<Tuple>::iterator it = selectedTuples.begin(); it != selectedTuples.end(); it++){
                ss << " ";
                for (unsigned int i = 0; i < schemeRenames.size(); i++){
                    bool repeat = false;
                    if (i > 0){
                        for (int j = i - 1; j >= 0; j--){
                            if (schemeRenames[i] == schemeRenames[j]){
                                repeat = true;
                            }
                        }
                    }
                    if (schemeRenames[i] != "" && repeat == false){
                        ss << " " << schemeRenames[i] << "=" << it->at(i);
                    }
                }
                ss << endl;
            }
        }
        return ss.str();
    }
    
    void giveQValue(vector<string> values){
        for (unsigned int i = 0; i < values.size(); i++){
            qValue temp;
            if (values[i][0] == '\''){
                temp.content = values[i];
            } else temp.var = values[i];
            currentQuery.push_back(temp);
        }
    }
    
    string printTuples(){
        stringstream ss;
        ss << name << endl;
        for (set<Tuple>::iterator it = allTuples.begin(); it != allTuples.end(); it++){
            ss << " ";
            for (unsigned int i = 0; i < schemeNames.size(); i++){
                ss << " " << schemeNames[i] << "=" << it->at(i);
            }
            ss << endl;
        }
        ss << endl;
        return ss.str();
    }
    string printRules(){
        stringstream ss;
        for (set<Tuple>::iterator it = allTuples.begin(); it != allTuples.end(); it++){
            ss << " ";
            for (unsigned int i = 0; i < schemeNames.size(); i++){
                ss << " " << schemeNames[i] << "=" << it->at(i);
            }
            ss << endl;
        }
        return ss.str();
    }
    string printQuery(int count){
        stringstream ss;
        if (count == 0){
            ss << "No\n" << endl;
        } else {
            ss << "Yes(" << count << ")\n"
            << "select" << endl;
            for (set<Tuple>::iterator it = selectedTuples.begin(); it != selectedTuples.end(); it++){
                ss << " ";
                for (unsigned int i = 0; i < schemeNames.size(); i++){
                    ss << " " << schemeNames[i] << "=" << it->at(i);
                }
                ss << endl;
            }
            ss << project();
            ss << rename();
            ss << endl;
        }
        return ss.str();
    }
    void determineEmpty(bool& empty){
        for (unsigned int i = 0; i < schemeRenames.size(); i++){
            if (schemeRenames[i] != ""){
                empty = false;
            }
        }
    }
    void clearQuery(){
        currentQuery.clear();
    }
};

#endif /* Relation_h */
