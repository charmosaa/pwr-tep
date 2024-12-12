#include "MyNode.h"
#include <string>
#include <iostream>
#include <map>
#include <math.h>

MyNode::MyNode()
{
    isNumber = false;
    isOperator = false;
    isVariable = false;
    isCorrect = true;
    children = 0;
    parentNode = nullptr;
    childNodes = nullptr;
    nodeValue = "";
}

MyNode :: MyNode(std::string value)
{
    isNumber = false;
    isOperator = false;
    isVariable = false;
    isCorrect = true;
    children = 0;
    parentNode = nullptr;
    childNodes = nullptr;
    
    nodeValue = value;
    if(nodeValue == "+" || nodeValue == "-" || nodeValue == "*" || nodeValue == "/")
    {
        isOperator = true;
        children = 2;
    }
    else if(nodeValue == "sin" || nodeValue == "cos")
    {
        isOperator = true;
        children = 1;
    }
    else
    {
        int alphaInString = 0; //number of alphabetical chars in string
        int numInString = 0; //numbers in string
        int otherChars = 0; //forbiden chars

        for(int i=0;i<value.size();i++)
        {
            if(value[i]>='0' && value[i]<='9')
                numInString++;
            else if((value[i]>='a' && value[i]<='z') || (value[i]>='A' && value[i]<='Z' ))
                alphaInString++;
            else
                otherChars++;
        }
        if(numInString == value.size())
            isNumber = true;
        else if(alphaInString + numInString == value.size())
            isVariable = true;
        else
            isCorrect = false;
    }
    if(children>0)
        childNodes = new MyNode*[children];
}

MyNode :: MyNode(const MyNode& otherNode)
{
    isNumber = otherNode.isNumber;
    isOperator = otherNode.isOperator;
    isVariable = otherNode.isVariable;
    isCorrect = otherNode.isCorrect;

    nodeValue = otherNode.nodeValue;
    children = otherNode.children;

    parentNode = nullptr;
    childNodes = nullptr;

    if(isOperator)
    {
        childNodes = new MyNode* [children];
        for(int i=0;i<children;i++)
        {
            childNodes[i] = new MyNode(*otherNode.childNodes[i]);
            childNodes[i]->setParent(this);
        }  
    }  
}


MyNode::~MyNode()
{
    for(int i=0;i<children;i++)
        delete childNodes[i];
    delete[] childNodes;
    std::cout<<nodeValue<<"deleted"<<std::endl;
}

void MyNode:: setLeftChild(MyNode* child)
{
    if(children>0)
        childNodes[0] = child;
}

void MyNode:: setRightChild(MyNode* child)
{
    if(children>0)
        childNodes[1] = child;
}

void MyNode:: setParent(MyNode* parent)
{
    parentNode = parent;
}

std::string MyNode :: toEquation()
{   
    if(this == nullptr)
        return "EMPTY TREE";
    std::string equation;
    equation = nodeValue;
    for(int i=0;i<children;i++)
        equation = equation +" "+childNodes[i]->toEquation();
    return equation;
}

 std::map<std::string, std::string> MyNode:: variablesInSubNodes()
 {
    std::map<std::string,std::string> variableMap;
    if(isVariable)
        variableMap[nodeValue] = "";
    else if(isOperator)
    {
        for(int i=0;i<children;i++)
        {
            for (auto it: childNodes[i]->variablesInSubNodes())
                variableMap[it.first] = "";  
        }
    }
    return variableMap;   
 }

 double MyNode:: calculate(std::map<std::string, std::string>& variablesInt)
 {
    double result = 0;
    if(isOperator)
    {
        switch (nodeValue[0])
        {
        case '+':
            result = childNodes[0]->calculate(variablesInt) + childNodes[1]->calculate(variablesInt);
            break;
        case '-':
            result = childNodes[0]->calculate(variablesInt) - childNodes[1]->calculate(variablesInt);
            break;
        case '*':
            result = childNodes[0]->calculate(variablesInt) * childNodes[1]->calculate(variablesInt);
            break;
        case '/':
            result = childNodes[0]->calculate(variablesInt) / (double) childNodes[1]->calculate(variablesInt);
            break;
        default:
            if(nodeValue == "sin")
            {
                result = sin(childNodes[0]->calculate(variablesInt));
            }
            else if(nodeValue == "cos")
            {
                result = cos(childNodes[0]->calculate(variablesInt));
            }
            break;
        }
    }
    else if(isVariable)
        result = stringToInt(variablesInt[nodeValue]);
    else if(isNumber)
        result = stringToInt(nodeValue);
    
    return result;
 }

 int MyNode:: stringToInt(std::string string)
 {
    int result = 0;
    for(int i=0;i<string.size();i++)
    {
        result*=10;
        result=result+(string[i]-'0');
    }
    return result;
 }

 MyNode* MyNode:: getLeftMostChild()
 {
    if(isOperator)
        return childNodes[0]->getLeftMostChild();
    return this;
 }

void MyNode:: optimize()
{
    if(isOperator)
    {
        if(variablesInSubNodes().empty())
        {
            std::map<std::string, std::string> variables = variablesInSubNodes();
            nodeValue = intToStr(calculate(variables));
            isOperator = false;
            isNumber = true;
            for(int i=0;i<children;i++)
                delete childNodes[i];
            delete childNodes;
            children = 0;
        }
        else{
            for(int i=0;i<children;i++)
                childNodes[i]->optimize();
        }
    }
}

std::string MyNode:: intToStr(int x)
{
    std::string result = "";
    if(x==0)
        return "0";
    while(x>0)
    {
        int lastNum = x%10;
        char c = lastNum+'0';
        result = c+result;
        x/=10;
    }
    return result;

}