//
//  Scanner.h
//  Project 1
//
//  Created by Seong-Eun Cho on 6/26/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

enum Type {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, EOFILE
};

class Scanner {
private:
    struct Token {
        Type tokenType;
        string data;
        int line;
    };
    vector<Token> tokenHolder;
    int errorLine = 0;
    
public:
    void importFile(string fileName);
    void exportFile(string fileName);
    void processString(ifstream& inFile, Token currentToken, int line);
    void processColon(ifstream& inFile, Token currentToken, int line);
    void processAlpha(ifstream& inFile, Token currentToken, char currentChar, int line);
    void error(ifstream& inFile, int line);
};

#endif /* Scanner_h */
