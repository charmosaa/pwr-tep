#include "Error.h"
#include "Result.h"
#include "MyTree.h"
#include "FileSaver.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define OPERATORS {"+","-","/","*","sin","cos"}
#define TWO_CHILD_OPERATORS {"+","-","/","*"}
#define ONE_CHILD_OPERATORS {"sin","cos"}

#define ERROR_EQUATION_NOT_COMPLETE "equation not complete"
#define ERROR_FORBIDDEN_CHARS "forbidden chars in the equation"

bool isOperator(std::string string)
{
    std::vector<std::string> operatorList = OPERATORS;

    for(int i=0;i<operatorList.size();i++)
        if(string == operatorList[i])
            return true;
    return false;
}  

bool isTwoChildOperator(std::string string)
{
    std::vector<std::string> operatorList = TWO_CHILD_OPERATORS;
    std::vector<std::string>::iterator it = std::find(operatorList.begin(), operatorList.end(), string);

    if (it != operatorList.end()) 
       return true;
    return false;
}

bool isOneChildOperator(std::string string)
{
    std::vector<std::string> operatorList = ONE_CHILD_OPERATORS;
    std::vector<std::string>::iterator it = std::find(operatorList.begin(), operatorList.end(), string);

    if (it != operatorList.end()) 
       return true;
    return false;
}

bool noOtherSimbols(std::vector<std::string> input)
{
    for(int i=0;i<input.size();i++)
    {
        std::string current = input.at(i);

        if(!isOperator(current))
        {
            for(int j=0;j<current.size();j++)
            {   if(current[j]<'0' || current[j]>'9')
                {
                    if(current[j]<'a' || current[j]>'z')
                        return false;
                }
            }
        }
    }
    return true;
}

std::vector<std::string> parseInput(std::string input)
{
    int pos = input.find(" ");
    std::vector<std::string>value;
    while(pos>=0 && pos<=input.length())
    {
        value.push_back(input.substr(0,pos));
        
        input = input.substr(pos +1,input.length());
        pos = input.find(" ");
    }
    if(!input.empty())
        value.push_back(input);
    return value;
}

bool isCorrectEquation(std::vector<std::string> input)
{
    if(isOperator(input[0]))
    { 
        int leftTreeSize = 1;
        int leftExpectedSize = 1;
        int size = input.size();

        while(leftTreeSize <= leftExpectedSize)
        {
            if(leftTreeSize >= size)
                return false;
               
            std::string nodeValue = input.at(leftTreeSize);
            if(isTwoChildOperator(nodeValue))
                leftExpectedSize+=2;
            else if(isOneChildOperator(nodeValue))
                leftExpectedSize++;
            leftTreeSize++;
        }
        std::vector<std::string>rightVect = {input.begin()+leftTreeSize,input.end()};

        if(isTwoChildOperator(input[0])) 
        {
            if(rightVect.empty())
                return false;
        }
    }
    return true; 
}


Result<double, Error> divide(double dDividend, double dDivisor)
{
    if (dDivisor == 0)
    {
        return Result<double, Error>::fail(new Error("cannot divide by zero"));
    }
    return Result<double, Error>::ok(dDividend / dDivisor);
}

Result<MyTree, Error> createTree(std::string equation)
{
    std::vector<std::string> vectorInput = parseInput(equation);
    std::vector<Error*> errors;
    if(noOtherSimbols(vectorInput))
    {
        if(isCorrectEquation(vectorInput))
        {
            MyTree tree(vectorInput);
            return Result<MyTree, Error>::ok(tree);
        }    
        errors.push_back(new Error(ERROR_EQUATION_NOT_COMPLETE));
    }
    else
    {
        if(!isCorrectEquation(vectorInput))
            errors.push_back(new Error(ERROR_EQUATION_NOT_COMPLETE));
        errors.push_back(new Error(ERROR_FORBIDDEN_CHARS));
    } 
    return Result<MyTree,Error>::fail(errors);
}


int main()
{
    
    Result<double,Error> r11 (divide(12.5, 2.1));
    Result<double,Error> r21 (r11);
    Result<double,Error> r31 (divide(1.1, 0));

    r11.print();
    r31.print();

    std::cout<<"\n\nchanged: \n"<<std::endl;
    r31 = r21;

    r11.print();
    r31.print();
    r21.print();

    std::cout<<r21.isSuccess()<<std::endl;
    std::cout<<r11.isSuccess()<<std::endl;

    Result<MyTree,Error> r1 (createTree("a"));
    Result<MyTree,Error> r2 (createTree("- a b"));
    Result<MyTree,Error> r3 (createTree("+ f$"));
    Result<MyTree,Error> r4 (r2);

    std::cout<<"\n\nbefore: -----------------------------------------------------\n"<<std::endl;
    r1.print();
    r2.print();
    r3.print();
    r4.print();
    std::cout<<"-------------------------------------------------------------------\n"<<std::endl;

    r1 = r4;
    r2 = r3;

    std::cout<<"\n\nchanged: -----------------------------------------------------\n"<<std::endl;

    r1.print();
    r2.print();
    r3.print();
    r4.print();

    std::cout<<"-------------------------------------------------------------------\n"<<std::endl;

    FileSaver<MyTree,Error> fileSaver;
    std::string filename = "lab4_results_file.txt";
    fileSaver.saveToFile(r2,filename);
}
//check commits