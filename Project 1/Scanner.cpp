//
//  Scanner.cpp
//  Project 1
//
//  Created by Seong-Eun Cho on 6/26/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#include <stdio.h>
#include "Scanner.h"

using namespace std;

void Scanner::importFile(string fileName){
    ifstream inFile(fileName);
    char currentChar;
    Token currentToken;
    int line = 1;
    string currentLine;
    while (inFile.get(currentChar)){
        
        if (currentChar == '\n'){
            line++;
            continue;
        }
        if (iswspace(currentChar)){
            continue;
        }
        switch (currentChar){
            case '#':
                getline(inFile, currentLine);
                line++;
                break;
            case ',':
                currentToken.tokenType = COMMA;
                currentToken.data = ",";
                currentToken.line = line;
                tokenHolder.push_back(currentToken);
                break;
            case '.':
                currentToken.tokenType = PERIOD;
                currentToken.data = ".";
                currentToken.line = line;
                tokenHolder.push_back(currentToken);
                break;
            case '?':
                currentToken.tokenType = Q_MARK;
                currentToken.data = "?";
                currentToken.line = line;
                tokenHolder.push_back(currentToken);
                break;
            case '(':
                currentToken.tokenType = LEFT_PAREN;
                currentToken.data = "(";
                currentToken.line = line;
                tokenHolder.push_back(currentToken);
                break;
            case ')':
                currentToken.tokenType = RIGHT_PAREN;
                currentToken.data = ")";
                currentToken.line = line;
                tokenHolder.push_back(currentToken);
                break;
            case ':':
                processColon(inFile, currentToken, line);
                break;
            case '\'':
                processString(inFile, currentToken, line);
                break;
            default:
                if (isalpha(currentChar)){
                    processAlpha(inFile, currentToken, currentChar, line);
                }
                else {
                    error(inFile, line);
                }
        }
    }
    
    if (errorLine == 0){
        currentToken.tokenType = EOFILE;
        currentToken.data = "";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
}

void Scanner::processColon (ifstream& inFile, Scanner::Token currentToken, int line){
    if (inFile.peek() == '-'){
        inFile.get();
        currentToken.tokenType = COLON_DASH;
        currentToken.data = ":-";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
    else {
        currentToken.tokenType = COLON;
        currentToken.data = ":";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
}

void Scanner::processString (ifstream &inFile, Scanner::Token currentToken, int line){
    char nextChar;
    string content;
    while (inFile.get(nextChar)){
        if (nextChar == '\''){
            currentToken.tokenType = STRING;
            currentToken.data = '\'' + content + '\'';
            currentToken.line = line;
            tokenHolder.push_back(currentToken);
            return;
        }
        else if (nextChar != '\n'){
            content += nextChar;
        }
        else {
            error(inFile, line);
        }
    }
    if (inFile.eof()){
        error(inFile, line);
    }
}

void Scanner::processAlpha (ifstream &inFile, Scanner::Token currentToken, char currentChar, int line){
    char nextChar;
    string content;
    content += currentChar;
    while ((nextChar = inFile.peek())){
        if (isalpha(nextChar) || isdigit(nextChar)){
            content += nextChar;
            inFile.get();
        }
        else break;
    }
    
    if (content == "Schemes"){
        currentToken.tokenType = SCHEMES;
        currentToken.data = "Schemes";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
    else if (content == "Facts"){
        currentToken.tokenType = FACTS;
        currentToken.data = "Facts";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
    else if (content == "Rules"){
        currentToken.tokenType = RULES;
        currentToken.data = "Rules";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
    else if (content == "Queries"){
        currentToken.tokenType = QUERIES;
        currentToken.data = "Queries";
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
    else {
        currentToken.tokenType = ID;
        currentToken.data = content;
        currentToken.line = line;
        tokenHolder.push_back(currentToken);
    }
}

void Scanner::error(ifstream &inFile, int line){
    inFile.close();
    errorLine = line;
}

void Scanner::exportFile(string fileName){
    ofstream outFile(fileName);
    string typeToString;
    for (int i = 0; i < tokenHolder.size(); i++){
        switch (tokenHolder[i].tokenType){
            case COMMA:
                typeToString = "COMMA";
                break;
            case PERIOD:
                typeToString = "PERIOD";
                break;
            case Q_MARK:
                typeToString = "Q_MARK";
                break;
            case LEFT_PAREN:
                typeToString = "LEFT_PAREN";
                break;
            case RIGHT_PAREN:
                typeToString = "RIGHT_PAREN";
                break;
            case COLON:
                typeToString = "COLON";
                break;
            case COLON_DASH:
                typeToString = "COLON_DASH";
                break;
            case SCHEMES:
                typeToString = "SCHEMES";
                break;
            case FACTS:
                typeToString = "FACTS";
                break;
            case RULES:
                typeToString = "RULES";
                break;
            case QUERIES:
                typeToString = "QUERIES";
                break;
            case ID:
                typeToString = "ID";
                break;
            case STRING:
                typeToString = "STRING";
                break;
            case EOFILE:
                typeToString = "EOF";
                break;
        }
        cout << "(" << typeToString << ",\"" << tokenHolder[i].data << "\"," << tokenHolder[i].line << ")" << endl;
        outFile << "(" << typeToString << ",\"" << tokenHolder[i].data << "\"," << tokenHolder[i].line << ")" << endl;
    }
    if (errorLine != 0){
        cout << "Input Error on line " << errorLine;
        outFile << "Input Error on line " << errorLine;
    }
    else {
        cout << "Total Tokens = " << tokenHolder.size();
        outFile << "Total Tokens = " << tokenHolder.size();
    }
}