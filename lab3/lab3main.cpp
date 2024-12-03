
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "TreeManager.h"
#include "MyTree.h"

using namespace std;

int main()
{
    bool isRunning = true;
    TreeManager treeManager;
    string input = "+ 48 * 9 a";
    string input2 = "sin x";

    MyTree tree1 (treeManager.parseInput(input));
    MyTree tree2 (treeManager.parseInput(input2));
    MyTree tree3 = tree1 + tree2;
    
    cout<<"tree3: "<<tree3.toString()<<endl;

    cout<<"tree2: "<<tree2.toString()<<endl;
    
    cout<<"tree1: "<<tree1.toString()<<endl<<endl<<endl;  

    string input4 = "+ a / 4 + 1 1";
    MyTree tree4(treeManager.parseInput(input4));
    MyTree *tree5 = new MyTree(tree4.optimizeTree());
    

    cout<<"tree4: "<<tree4.toString()<<endl;
    cout<<"tree5: "<<tree5->toString()<<endl<<endl<<endl;  

    
    input4 = "+ 48 / 4 + 1 1";
    MyTree tree6(treeManager.parseInput(input4));
    MyTree *tree7 = new MyTree( tree6.optimizeTree());

    cout<<"tree6: "<<tree6.toString()<<endl;
    cout<<"tree7: "<<tree7->toString()<<endl<<endl<<endl;  
    
    while(isRunning)
    {
        cout<<"enter command: ";
        getline(cin, input);
        if(input == "end")
        {
            isRunning = false;
        }   
        else{
            treeManager.parseCommand(input);
            cout << endl;
        }
    }

    return 0;
}




