//
//  main.cpp
//  Project 1
//
//  Created by Seong-Eun Cho on 6/26/16.
//  Copyright © 2016 Seong-Eun Cho. All rights reserved.
//

#include <iostream>
#include "Scanner.h"

int main(int argc, const char* argv[]) {
    Scanner scan;
    scan.importFile(argv[1]);
    scan.exportFile(argv[2]);
    
    return 0;
}
