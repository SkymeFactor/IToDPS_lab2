/**
 * @file Main.cpp
 * @author Skyme (sergey.51351@gmail.com)
 * @brief
 *      Main file, contains entry point when
 *      compiled with Makefile
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include "clReader.h"
#include "clData.h"
#include "clHandler.h"

/**
 * @brief 
 *      Main function. Creates clReader,
 *      reads from "input.txt", counts, and
 *      stores result in "output.txt".
 * @param argc 
 * @param argv 
 * @return int
 */
int main(int argc, char* argv[]) {

    MyVectorStruct<int> dataset;
    clReader reader;

    std::cout << "stage 1: reading.\n";
    reader.readFile(dataset, "input.txt", false);
    std::cout << "stage 2: writing.\n";
    reader.writeFile(dataset, "output.txt", false);
    std::cout << "Computing finished.\n";
    
    return 0;
}