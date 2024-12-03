#include <iostream>
#include <string>
#include <vector>

#include "MyTree.h"
#include "MyNode.h"

MyTree :: MyTree()
{
    root = nullptr;
}

MyTree :: MyTree(std::vector<std::string> values)
{
    root = new MyNode(values.at(0));

    if(root->isOperator)
    { 
        int leftTreeSize = 1;
        int leftExpectedSize = 1;
        int size = values.size();

        while(leftTreeSize <= leftExpectedSize)
        {
            while(leftTreeSize >= size)
            {
                values.push_back("1");
                size++;
            }    
            std::string nodeValue = values.at(leftTreeSize);
            if(nodeValue == "+" || nodeValue == "-" || nodeValue == "*" || nodeValue == "/")
                leftExpectedSize+=2;
            else if(nodeValue == "sin" || nodeValue == "cos")
                leftExpectedSize++;
            leftTreeSize++;
        }

        std::vector<std::string>leftVect = {values.begin()+1,values.begin()+leftTreeSize};
        std::vector<std::string>rightVect = {values.begin()+leftTreeSize,values.end()};

        setLeftChild(new MyTree(leftVect));
        if(root->children == 2) 
        {
            if(rightVect.empty())
                rightVect.push_back("1");
            setRightChild(new MyTree(rightVect));
        }                 
           
    } 

}


MyTree::MyTree(const MyTree& otherTree)
{
    root = new MyNode(*otherTree.root);
}

MyTree :: ~MyTree()
{
    delete root;
    std::cout<<"tree deleted\n"<<std::endl;
}


void MyTree :: setLeftChild(MyTree *child)
{
    root->setLeftChild(child->root);
    (child->root)->setParent(root);
}
void MyTree :: setRightChild(MyTree *child)
{
    root->setRightChild(child->root);
    (child->root)->setParent(root);
}


std::string MyTree::toString()
{
    return root->toEquation();
}

void MyTree::createVariablesMap()
{
    variables = root -> variablesInSubNodes();
}

void MyTree::printVariables()
{
    createVariablesMap();
    for(auto i: variables)
        std::cout<<i.first<<" "<<i.second<<std::endl;
}

double MyTree:: calculateOutput()
{
    return root->calculate(variables);
}

MyNode* MyTree:: getLeftMostChild()
{
    return root->getLeftMostChild();
}

void MyTree:: addSubTree(MyTree* newTree)
{
    MyNode* nodeToSubstitute = getLeftMostChild();
    nodeToSubstitute->parentNode->setLeftChild(newTree->root);
    newTree->root->setParent(nodeToSubstitute->parentNode);
    delete nodeToSubstitute;
}

MyTree MyTree:: operator=(const MyTree &otherTree)
{
    delete root;
    root = new MyNode(*otherTree.root);
    return *this;
}
        
        
MyTree MyTree:: operator+(const MyTree &otherTree)
{
    MyTree newTree(*this);
    newTree.addSubTree(new MyTree(otherTree));
    return newTree;
}

MyTree MyTree:: optimizeTree()
{
    MyTree optimizedTree(*this);
    optimizedTree.root->optimize();
    return optimizedTree;
}

std::ostream& operator<<(std::ostream& os, MyTree& obj)
{
    os<<obj.toString();
    return os;
}