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
        MyTree operator=(const MyTree &otherTree);
        MyTree operator+(const MyTree &otherTree);
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
        void addSubTree(MyTree* newTree);
        MyTree optimizeTree();
    protected:
    private:
};