#pragma once

#include <string>
#include "MyNode.h"
#include <vector>
#include <map>

class MyTree
{
    public:
        MyTree();
        MyTree(std::vector<std::string> values);
        MyTree(const MyTree& otherTree);
        MyTree(MyTree &&otherTree);
        MyTree& operator=(MyTree &&otherTree);
        MyTree& operator=(MyTree &otherTree);
        MyTree operator+(MyTree &otherTree);
        virtual ~MyTree();
        MyNode* root;
        void setLeftChild(MyTree *child);
        void setRightChild(MyTree *child);
        std::vector<std::string> parseInput(std:: string input);
        std::string toString();
        void createVariablesMap();
        void printVariables();
        std::map <std::string, std::string> variables;
        double calculateOutput();
        MyNode* getLeftMostChild();
        void addSubTree(const MyTree& newTree);
        MyTree optimizeTree();
        friend std::ostream& operator<<(std::ostream& os, MyTree& obj);
    protected:
    private:
};