//
//  main.cpp
//  Lab 3
//
//  Created by Seong-Eun Cho on 7/20/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#include <iostream>
#include "Interpreter.h"

int main(int argc, const char* argv[]) {
    string infile, outfile;
    cin >> infile >> outfile;
    Scanner scan;
    scan.importFile(infile);
    //scan.exportFile(argv[2]);
    Parser parse;
    parse.addScanner(scan, outfile);
    parse.datalogProgram();
    Interpreter interpret;
    interpret.addParser(parse, outfile);
    interpret.print();
    
    return 0;
}
