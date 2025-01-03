//
//  Token.h
//  Project 2
//
//  Created by Seong-Eun Cho on 6/30/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#ifndef Token_h
#define Token_h
struct Token {
    Type tokenType;
    std::string data;
    int line;
    
    std::string typeToString(){
        switch (tokenType){
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case EOFILE:
                return "EOF";                
        }
        return "";
    }
};

#endif /* Token_h */
