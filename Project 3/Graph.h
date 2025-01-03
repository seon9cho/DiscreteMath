//
//  Graph.h
//  Lab 3
//
//  Created by Seong-Eun Cho on 8/4/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <map>
#include <sstream>
#include "Node.h"

struct Comp {
    bool operator() (Node lhs, Node rhs){
        return lhs.getPON() > rhs.getPON();
    }
};
class Graph {
    friend class Interpreter;
private:
    map<string, Node> myNodes;
    set<Node, Comp> sortedNodes;
    vector<vector<string>> SCC;
    
public:
    void receiveRules(vector<Rule> myRules){
        for (unsigned int i= 0; i < myRules.size(); i++){
            Node tempNode;
            tempNode.name = "R" + to_string(i);
            tempNode.myRule = myRules[i];
            myNodes.insert(pair<string, Node>(tempNode.name, tempNode));
        }
    }
    
    void dependency(){
        for (auto m1 : myNodes){
            for (unsigned int j = 0; j < m1.second.myRule.getAllPredicate().size(); j++){
                for (auto m2 : myNodes){
                    if (m1.second.myRule.getAllPredicate().at(j).getPredicateID() == m2.second.myRule.getProduct().getPredicateID()){
                        myNodes[m1.first].dependency.insert(myNodes[m2.first].name);
                        myNodes[m2.first].reverseDependency.insert(myNodes[m1.first].name);
                    }
                }
            }
        }
    }
    
    void dfs(Node& x, int& count){
        myNodes[x.name].mark = true;
        for (auto r : x.reverseDependency){
            if (!myNodes[r].mark){
                dfs(myNodes[r], count);
            }
        }
        cout << count << endl;
        myNodes[x.name].pon = count;
        count++;
    }
    void dfsForest(){
        int count = 1;
        for (auto n : myNodes){
            if (!myNodes[n.first].mark){
                dfs(n.second, count);
            }
        }
    }
    
    void sortNodes(){
        for (auto n : myNodes){
            myNodes[n.first].mark = false;
            sortedNodes.insert(n.second);
        }
    }
    
    void scc(Node& x, vector<string>& tempSCC){
        x.mark = true;
        tempSCC.push_back(x.name);
        for (auto d : x.dependency){
            if (!myNodes[d].mark){
                scc(myNodes[d], tempSCC);
            }
        }
    }
    void sccForest(){
        for (auto n : sortedNodes){
            if (!myNodes[n.name].mark){
                vector<string> tempSCC;
                scc(myNodes[n.name], tempSCC);
                SCC.push_back(tempSCC);
            }
        }
    }
    
    string print(){
        stringstream ss;
        dependency();
        dfsForest();
        
        ss << "Dependency Graph" << endl;
        for (auto m : myNodes){
            ss << "  " << myNodes[m.first].name << ":";
            for (auto d : m.second.dependency){
                ss << " " << d;
            }
            ss << endl;
        }
        ss << endl;
        
        ss << "Reverse Graph" << endl;
        for (auto m : myNodes){
            ss << "  " << myNodes[m.first].name << ":";
            for (auto r : m.second.reverseDependency){
                ss << " " << r;
            }
            ss << endl;
        }
        ss << endl;
        
        ss << "Postorder Numbers" << endl;
        for (auto m : myNodes){
            ss << "  " << myNodes[m.first].name << ": " << myNodes[m.first].pon << endl;
        }
        ss << endl;
        
        sortNodes();
        ss << "SCC Search Order" << endl;
        for (auto n : sortedNodes){
            ss << "  " << n.name << endl;
        }
        ss << endl;
        
        sccForest();
        cout << "SCC vector" << endl;
        for (int i = 0; i < SCC.size(); i++){
            cout << "SCC: ";
            for (int j = 0; j < SCC[i].size(); j++){
                cout << SCC[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        
        return ss.str();
    }
};

#endif /* Graph_h */
