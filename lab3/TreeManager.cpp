#include "TreeManager.h"
#include "MyTree.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>


enum commandNames{
    ENTER,
    VARS,
    PRINT,
    COMP,
    JOIN,
};

TreeManager::TreeManager()
{
    tree = nullptr;
}

TreeManager::~TreeManager()
{
    delete tree;
    std::cout<<"tree deleted by manager\n"<<std::endl;
}

std::vector<std::string> TreeManager:: parseInput(std::string input)
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

void TreeManager:: parseCommand(std::string command)
{
    int pos = command.find(" "); //finding first space
    std::string commandName;
    std::string commandBody;
    if(pos == -1)
        commandName = command;
    else{
        commandName = command.substr(0,pos);
        commandBody = command.substr(pos+1, command.size());
    }

    std::map<std::string, commandNames> mapNames = {{"enter",ENTER},{"vars",VARS},{"print",PRINT},{"comp",COMP},{"join",JOIN}};
    
    if(mapNames.count(commandName) == 0)
        std::cout<<"wrong command"<<std::endl;
    else
    {
        switch (mapNames[commandName])
        {
        case ENTER:
            if(noOtherSimbols(parseInput(commandBody))) //check no other signs
            {
                delete tree;
                tree = new MyTree(parseInput(commandBody)); 
                if(tree->toString() != commandBody)  
                    std::cout<<"your equation was not correct\nnew equation: "<<tree->toString()<<std::endl;
            }
            else
                std::cout<<"only small letters and numbers as variables"<<std::endl;
            break;
        case VARS:
            tree->printVariables();
            break;
        case PRINT:
            std::cout<<tree->toString()<<std::endl;
            break;
        case COMP:
            if(isAllNumbers(parseInput(commandBody)))  //check numeric
            {
                if(!treeVariablesToInt(parseInput(commandBody)))
                    std::cout<<"incorrect data"<<std::endl;
                else
                    std::cout<<"result: "<<tree->calculateOutput()<<std::endl;
            }
            else
                std::cout<<"values must be numeric"<<std::endl;
            break;
        case JOIN:
        if(noOtherSimbols(parseInput(commandBody)))//check no other signs
        {
            MyTree* subTree = new MyTree(parseInput(commandBody));
            if(subTree->toString() != commandBody)
                std::cout<<"your equation was not correct\nnew equation: "<<subTree->toString()<<std::endl;
            joinTree(subTree); 
        }
        else
            std::cout<<"only small letters and numbers as variables"<<std::endl;
            break;
        default:
            std::cout<<"wrong command"<<std::endl;
            break;
        }
    }

}

bool TreeManager:: treeVariablesToInt(std::vector<std::string> integers)
{
    tree -> createVariablesMap();
    if(tree->variables.size()==0)
    {
        std::cout<<"no variables in tree"<<std::endl;
        return true;
    }
    else if(integers.size() == tree->variables.size())
    {
        int i=0;
        for(auto it: tree -> variables)
        {  
            tree->variables[it.first] = integers[i];
            i++;
        }
        return true;
    }
    else
        return false;
}

void TreeManager:: joinTree(MyTree* newTree)
{
    if(!tree->root->isOperator)//root is the node to substitue
    {
        delete tree;
        tree = newTree;
    }
    else{
        tree->addSubTree(newTree);
    }
}

bool TreeManager:: noOtherSimbols(std::vector<std::string> input)
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
        
        

bool TreeManager:: isAllNumbers(std::vector<std::string> input)
{
    for(int i=0;i<input.size();i++)
    {
        std::string current = input.at(i);
        for(int j=0;j<current.size();j++)
            if(current[j]<'0' || current[j]>'9')
                return false;
    }
    return true;
}


bool TreeManager::isOperator(std::string string)
{
    if(string == "+" || string == "-" || string == "*" || string == "/" || string == "sin" || string == "cos")
        return true;
    return false;
}

MyTree TreeManager :: optimizedTree()
{
    return tree->optimizeTree();
}