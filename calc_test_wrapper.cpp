/**
 * @file calc_test_wrapper.cpp
 * @author Skyme (sergey.51351@gmail.com)
 * @brief
 *      wrapper class was designed to be a layer between c++ and Python.
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <boost/python.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "clReader.h"
#include "clData.h"
#include "clHandler.h"

using namespace boost::python;

/**
 * @brief 
 *      Class transReceiver, establishes all sorts of communications
 *      between python and c++.
 */
class transReceiver {

private:
    static MyVectorStruct<int> dataset;

public:
    /**
     * @brief 
     *      Pushes data into the clData contayner and gets result
     *      into the static field MyVectorStruct dataset.
     * @param tmpl: left operand.
     * @param tmpo: operator.
     * @param tmpr: right operand.
     */
    static void PushData(std::string tmpl, char tmpo, std::string tmpr){
        try {
            clData<int> tdata = clData<int>(std::stold(tmpl), std::stold(tmpr), tmpo);
            dataset.left.push_back(tdata);
            dataset.right.push_back(tdata.GetError());
        } catch (std::exception& err){
            dataset.left.push_back(clData<int>(0,0,'+'));
            dataset.right.push_back(std::runtime_error("Invalid datatype.\n"));
        }
    };

    /**
     * @brief Get the list of Input values.
     * 
     * @return list 
     */
    static list GetInput() {
        list l;
        auto itL = dataset.left.begin();
        auto itR = dataset.right.begin();
        for (auto i = 0; i < (int)dataset.left.size(); i++){
            if ( std::strcmp((*itR).what(), std::runtime_error("Invalid datatype.\n").what()) != 0 &&
		 std::strcmp((*itR).what(), std::runtime_error("Unsupported operation type.\n").what()) != 0 ) {
                std::string s;
                s += std::to_string((*itL).GetLeft()); s += " "; s += (*itL).GetOperation();
                s += " "; s += std::to_string((*itL).GetRight());
                l.append(s);
            }
            else
                l.append( std::string((*itR).what()) );
            itL++; itR++;
        }
        return l;
    };

    /**
     * @brief Get the list of Output counted values.
     * 
     * @return list 
     */
    static list GetOutput() {
        list l;
        auto itL = dataset.left.begin();
        auto itR = dataset.right.begin();
        for (auto i = 0; i < (int)dataset.left.size(); i++){
            if ( std::strcmp((*itR).what(), std::runtime_error("").what()) == 0) {
                std::string s;
                s += std::to_string((*itL).GetResult());
                l.append(s);
            }
            else
                l.append( std::string((*itR).what()) );
            itL++; itR++;
        }
        return l;
    };
    transReceiver (){};
    ~transReceiver (){};
};

/**
 * @brief 
 *      Here wrapp the transReceiver into python code.
 */
MyVectorStruct<int> transReceiver::dataset = MyVectorStruct<int>();
BOOST_PYTHON_MODULE( calc_test )
{
    class_<transReceiver, boost::noncopyable>( "transReceiver" )
        .def( "PushData", &transReceiver::PushData, args( "tmpl", "tmpo", "tmpr" ) )
        .staticmethod( "PushData" )
        .def( "GetInput", &transReceiver::GetInput )
        .staticmethod( "GetInput" )
        .def( "GetOutput", &transReceiver::GetOutput )
        .staticmethod( "GetOutput" )
    ;
}
