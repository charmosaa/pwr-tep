#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "MyTree.h"

class TreeManager
{
    public:
        TreeManager();
        MyTree* tree;
        ~TreeManager();
        std::vector<std::string> parseInput(std::string input);
        void parseCommand(std::string command);
        bool treeVariablesToInt(std::vector<std::string>);
        void joinTree(MyTree* newTree);
        MyTree optimizedTree();
    protected:
    private:
        bool noOtherSimbols(std::vector<std::string> input);
        bool isAllNumbers(std::vector<std::string> input);
        bool isOperator(std::string string);
};
