/**
 * @file clData.h
 * @author Skyme (sergey.51351@gmail.com)
 * @brief
 *      class "clData" header file
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <stdexcept>
#include "clHandler.h"

/**
 * @brief 
 *      clData<T> class. Stores the expression inside formatted as:
 *      left operand, operator, right operand, result, error(must be 
 *      empty in most cases).
 * @tparam T 
 */
template <class T>
class clData {
private:
    T leftNumber, rightNumber, result;
    std::runtime_error errCode = std::runtime_error("");
    char operation;

    /**
     * @brief
     *      Is used immediately after object creation, cannot be calles again
     *      for the same object. Counts expression result by using external
     *      class clHandler.
     */
    void count (){
        clHandler<T> tHandler = clHandler<T>(leftNumber, rightNumber, operation);
        result = tHandler.GetResult();
        errCode = tHandler.GetError();
    }
public:
    /**
     * @brief Get the Left object
     * 
     * @return <T>
     */
    T GetLeft (){
        return leftNumber;
    }
    /**
     * @brief Get the Right object
     * 
     * @return <T> 
     */
    T GetRight () {
        return rightNumber;
    }
    /**
     * @brief Get the Operation object
     * 
     * @return char 
     */
    char GetOperation (){
        return operation;
    }
    /**
     * @brief Get the Result object
     * 
     * @return <T> 
     */
    T GetResult (){
        return result;
    }
    /**
     * @brief Get the Error object
     * 
     * @return std::runtime_error 
     */
    std::runtime_error GetError (){
        return errCode;
    }

    /**
     * @brief Construct a new clData object;
     *      used by default, because there is no other way to write the data in it.
     * @param left: value of left operand of expression.
     * @param right: value of right operand of expression.
     * @param op: operand of expression, has a type char.
     */
    clData (T left, T right, char op){
        leftNumber = left;
        rightNumber = right;
        operation = op;
        this->count();
    };
    /**
     * @brief Construct a new clData object;
     *      used by default, because there is no other way to write the data in it.
     * @param left: value of left operand of expression.
     * @param right: value of right operand of expression.
     * @param op: operand of expression, has a type char.
     * @param counted: false if you don't want to count with creation, has a type bool.
     */
    clData (T left, T right, char op, bool counted){
        leftNumber = left;
        rightNumber = right;
        operation = op;
        if (counted){
            this->count();
        }
    };
    ~clData (){

    };
};