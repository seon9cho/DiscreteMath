//
//  main.cpp
//  Project 2
//
//  Created by Seong-Eun Cho on 6/30/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#include <iostream>
#include "Scanner.h"
#include "Parser.h"

int main(int argc, const char* argv[]) {
    string infile, outfile;
    cin >> infile >> outfile;
    Scanner scan;
    scan.importFile(infile);
    //scan.exportFile(outfile);
    Parser parse(scan, outfile);
    parse.datalogProgram();
    parse.print();
    
    return 0;
}
