//
//  Database.h
//  Lab 3
//
//  Created by Seong-Eun Cho on 7/20/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Database_h
#define Database_h
#include "Relation.h"
#include <map>
using namespace std;

class Database {
    friend class Interpreter;
private:
    map<string, Relation> allData;
public:
    void addScheme (string name, vector<string> attributes){
        Relation emptyRelation;
        emptyRelation.addName(name);
        emptyRelation.addScheme(attributes);
        allData.insert(pair<string, Relation>(name, emptyRelation));
    }
    void addTuple (string name, vector<string> values){
        allData.at(name).addTuple(values);
    }
    
    void checkConstant (vector<Relation> &allRelations){
        for (unsigned int i = 0; i < allRelations.size(); i++){
            for(unsigned int j = 0; j < allRelations[i].schemeNames.size(); j++){
                if (allRelations[i].schemeNames[j][0] == '\''){
                    set<Tuple> tempSet = allRelations[i].allTuples;
                    for (auto T : allRelations[i].allTuples){
                        if (T[j] != allRelations[i].schemeNames[j]){
                            tempSet.erase(T);
                        }
                    }
                    allRelations[i].allTuples = tempSet;
                }
            }
        }
    }
    string evaluateRule (Relation &product, vector<Relation> &allRelations, int &change){
        stringstream ss;
        for (unsigned int i = 0; i < allRelations.size(); i++){
            allRelations[i].allTuples = allData[allRelations[i].name].allTuples;
        }
        checkConstant(allRelations);
        
        Relation r1 = allRelations[0];
        for (unsigned int i = 1; i < allRelations.size(); i++){
            Scheme s1 = r1.schemeNames;
            Relation r2 = allRelations[i];
            r1.addScheme(r2.schemeNames);
            Relation tempRelation = r1;
            for (auto t1 : r1.allTuples){
                for (auto t2 : r2.allTuples){
                    if (r1.canJoin(r2, t1, t2, s1)){
                        tempRelation.join(t1, t2);
                    }
                }
            }
            r1 = tempRelation;
            r1.deleteRemainingTuples();
        }
        product.applyRule(r1);
        product.schemeNames = allData[product.name].schemeNames;
        for (auto T : allData[product.name].allTuples){
            product.allTuples.erase(T);
        }
        if (product.allTuples.size() != 0){
            change++;
        }
        ss << product.printRules();
        
        for (auto T : product.allTuples){
            allData[product.name].allTuples.insert(T);
        }
        return ss.str();
    }

    string evaluateQuery (string name, vector<string> values){
        Relation tempRelation = allData.at(name);
        return tempRelation.evaluateQuery(values);
        //allData.at(name).clearQuery();
    }
};

#endif /* Database_h */
