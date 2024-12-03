#pragma once

#include <string>
#include <map>

class MyNode
{
    public:
        MyNode();
        MyNode(std::string value);
        MyNode(MyNode& otherNode);
        virtual ~MyNode();
        bool isNumber;
        bool isOperator;
        bool isVariable;
        bool isCorrect;
        std::string nodeValue;
        MyNode** childNodes;
        MyNode* parentNode;
        int children;
        void setLeftChild(MyNode *child);
        void setRightChild(MyNode *child);
        void setParent(MyNode *parent);
        std::string toEquation();
        std::map<std::string, std::string> variablesInSubNodes();
        double calculate(std::map<std::string, std::string>& variablesInt);
        MyNode* getLeftMostChild();
        void optimize();
    protected:
    private:
        int stringToInt(std::string string);
        std::string intToStr(int x);
};

