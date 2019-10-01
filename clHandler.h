/**
 * @file clHandler.h
 * @author Skyme (sergey.51351@gmail.com)
 * @brief
 *      class "clHandler" header file
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief 
 *      clHandler class. A distinctive object that can manage secure counting
 *      in terms of four basic functions ('+', '-', '/', '*').
 *      Also is a class of single purpose, cannot get another data.
 * @tparam <T> 
 */
template <class T>
class clHandler {
private:

    T result;
    double pResult;
    std::runtime_error errCode = std::runtime_error("");
    /**
     * @brief 
     *      Expressions main functions, counts result.
     * @param left 
     * @param right 
     */
    void add(T &left, T &right){
        result = left + right; 
    }
    void sub(T &left, T &right){
        result = left - right; 
    }
    void mlp(T &left, T &right){
        result = left * right; 
    }
    void div(T &left, T &right){
        if (right == 0){
            result = 0;
            throw "Division by zero.\n";
        } else {
            result = left / right;
        }
    }
    void pDiv(T &left, T &right){
        if (right == 0){
            pResult = 0.0;
            throw "Division by zero.\n";
        } else {
            pResult = (double)left / (double)right;
        }
    }
public:
    /**
     * @brief Get the Result object
     * 
     * @return T 
     */
    T GetResult (){
        return result;
    }
    double GetPreciseResult(){
        return pResult;
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
     * @brief Construct a new cl Handler object and catches errors.
     *      
     * @param left 
     * @param right 
     * @param op 
     */
    clHandler (T &left, T &right, char op){
        try {
            switch (op){
                case '+': add(left, right); break;
                case '-': sub(left, right); break;
                case '*': mlp(left, right); break;
                case '/': div(left, right); break;
                case ':': pDiv(left,right); break;
                default: throw "Unsupported operation type.\n";
            }
        }
        catch (char const* err){
            errCode = std::runtime_error(err);
        }
        catch (std::exception& err){
            errCode = std::runtime_error("Undefined exception.\n");
        }
    };
    ~clHandler (){};
};