/**
 * @file clReader.h
 * @author Skyme (sergey.51351@gmail.com)
 * @brief
 *      class "clReader" header file
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "clData.h"

/**
 * @brief 
 *      Structure that stores two identicly-sized vectors:
 *      vector of clData<T> as left, and a vector of
 *      errors that might have happen during the reading
 *      and counting process, as right.
 * @tparam T is a template class
 */
template <class T>
struct MyVectorStruct {
    std::vector<clData<T>> left;
    std::vector<std::runtime_error> right;                                                                                                                                                                                                                                                                                                                                                                                                                                          
};

/**
 * @brief
 *      A class that implements the reading from and writing
 *      to file function.
 * @note
 *      Almost, if not absolutly, ommited during the calc_test.so
 *      compilation, because of transReceiver class,
 *      that allows to interact with clData directly, in order
 *      to accelerate the testing process.
 */
class clReader {
public:
    /**
     * @brief 
     *      clReader::readFile method. Allows to read all file into the "left"
     *      vector of MyVectorStruct in format of Data<T> and catch the errors into
     *      the "right" vector accordingly.
     * @tparam T 
     * @param data: where to read file.
     * @param filename: name of the file to read.
     * @param verbose: if you want to write data to console.
     */
    template <class T>
    void readFile(MyVectorStruct<T> &data, const char* filename, bool verbose){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
        std::ifstream fin(filename);
        std::string tmpl, tmpr, tmpo;
        while (fin >> tmpl >> tmpo >> tmpr){
            try {
                clData<T> tdata = clData<T>(std::stold(tmpl), std::stold(tmpr), tmpo[0]);
                data.left.push_back(tdata);
                data.right.push_back(tdata.GetError());
            } catch (std::exception& err){
                data.left.push_back(clData<T>(0,0,'+'));
                data.right.push_back(std::runtime_error("Invalid datatype.\n"));
                continue;
            }
            if (verbose)
                std::cout << tmpl << " " << tmpo << " " << tmpr << ";\n";
        }
        fin.close();
    }
    /**
     * @brief 
     *      clRaader::writeFile method. Allows to write previously counted data
     *      into the file specified by filename.
     * @tparam T 
     * @param data: MyVectorStruct data to use.
     * @param filename: name of the file to write to.
     * @param verbose: if you want to write data to console.
     */
    template <class T>
    void writeFile (MyVectorStruct<T> &data, const char* filename, bool verbose){
        std::ofstream fout(filename);
        auto itL = data.left.begin();
        auto itR = data.right.begin();
        for (auto i = 0; i < (int)data.left.size(); i++){
            if ((*itR).what() == std::runtime_error("").what())
                fout << (*itL).GetLeft() << " " << (*itL).GetOperation() << " " << (*itL).GetRight()
                    << " = " << (*itL).GetResult() << "\n";
                    if (verbose)
                        std::cout << (*itL).GetLeft() << " " << (*itL).GetOperation() << " " 
                            << (*itL).GetRight() << " = " << (*itL).GetResult() << "\n";
            else
                fout << (*itR).what();
            itL++; itR++;
        }
        fout.close();
    }

    clReader (){};
    ~clReader (){};
};