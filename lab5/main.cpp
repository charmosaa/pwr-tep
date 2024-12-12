#include <iostream>
#include "MySmartPointer.h"
#include "MyTree.h"

class TestObject {
public:
    TestObject(int value) : value(value) {
        std::cout << "TestObject created with value: " << value << std::endl;
    }
    ~TestObject() {
        std::cout << "TestObject with value " << value << " destroyed" << std::endl;
    }
    int getValue() const { return value; }
    void setValue(int newValue) { value = newValue; }

private:
    int value;
};

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

int main() 
{
        // EXAMPLE 2
    // An example of adding trees
    MyTree tree(parseInput("cos x"));
    MyTree tree1(parseInput("+ ab c"));
    MyTree tree2(parseInput("- de f"));
    std::cout<<"\n------------moving constructor------\n";
    MyTree tree3(std::move(tree));
    std::cout<<"\n-----------copying constructor------\n";
    MyTree tree4(tree1);
    std::cout<<"\n-----------RESULTS------\n";

    //tree2 = tree1 + tree3;
    std::cout << "TREE 1: " << tree1.toString() << std::endl;
    std::cout << "TREE 2: " << tree2.toString() << std::endl;
    std::cout << "TREE 3: " << tree3.toString() << std::endl;
    std::cout << "TREE 4: " << tree4.toString() << std::endl;


    std::cout<<"\n------------moving operator------\n";
    tree2 = std::move(tree1);
    std::cout<<"\n-----------copying operatpr------\n";
    tree4 = tree3;
    std::cout<<"\n-----------RESULTS------\n";

    std::cout << "TREE 1: " << tree1<< std::endl;
    std::cout << "TREE 2: " << tree2<< std::endl;
    std::cout << "TREE 3: " << tree3<< std::endl;
    std::cout << "TREE 4: " << tree4<< std::endl;
    
    std::cout<<"\n------------adding------\n";
    tree1 = tree2 + tree3;
    // std::cout<<"\n-----------copying operatpr------\n";
    // tree4 = tree3;
    std::cout<<"\n-----------RESULTS------\n";

    std::cout << "TREE 1: " << tree1<< std::endl;
    std::cout << "TREE 2: " << tree2<< std::endl;
    std::cout << "TREE 3: " << tree3<< std::endl;
    std::cout << "TREE 4: " << tree4<< std::endl;
    std::cout<<"-----------END------\n\n";


    return 0;

    // //Test 5: MS trees
    // {
    //     MyTree tree1(parseInput("+ ab c"));
    //     MyTree tree2(parseInput("- de f"));

    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;

    //     std::cout << "----AFTER-----" << std::endl;
    //     tree1 = tree2;

    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;
    // }

    // std::cout << "----4------" << std::endl;
    // // Test 5: MS trees
    // {
    //     MyTree tree1(parseInput("+ ab c"));
    //     MyTree tree2(parseInput("- de f"));
    //     MyTree tree3(parseInput("cos x"));

    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;

    //     std::cout << "----AFTER-----" << std::endl;
    //     tree1 = tree2 + tree3;

        
    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;
    //     std::cout << "TREE 3: " << tree3.toString() << std::endl;
    // }

    // // EXAMPLE 2
// // An example of adding trees
// Tree<int> tree("+ 2 3");
// Tree<int> t1(std::move(tree));
// Tree<int> t2(t1);
// Tree<int> t3("- 4 5");
// t2 = t1 + t3;
// std::cout << t1.to_string() << std::endl;
// std::cout << t2.to_string() << std::endl;
// std::cout << t3.to_string() << std::endl;
// return 0;


    // //Tests for trees
    // {
    //     MyTree subTree(parseInput("cos y")); //check that
    //     MySmartPointer<MyTree> sp1(new MyTree(parseInput("+ 1 sin x")));
    //     std::cout << "Value in sp1: " << sp1->toString() << std::endl;
    //     *sp1 = *sp1 + subTree;
    //     std::cout << "Updated value in sp1: " << (*sp1).toString() << std::endl;
    // }

    // std::cout << "----2------" << std::endl;
    // // Test 2: Copy constructor
    // {
    //     MySmartPointer<MyTree> sp1(new MyTree(parseInput("* ab 10")));
    //     MySmartPointer<MyTree> sp2 = sp1; // Copy constructor
    //     std::cout << "Value in sp1: " << sp1->toString() << std::endl;
    //     std::cout << "Value in sp2: " << sp2->toString() << std::endl;
    // } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    // std::cout << "----3------" << std::endl;

    // // Test 3: Copy assignment
    // {
    //     MySmartPointer<MyTree> sp1(new MyTree(parseInput("/ cos 1 5")));
    //     MySmartPointer<MyTree> sp2 (new MyTree(parseInput("/ 1 8")));
    //     sp2 = sp1; // Copy assignment
    //     std::cout << "Value in sp1: " << sp1->toString() << std::endl;
    //     std::cout << "Value in sp2: " << sp2->toString() << std::endl;
    // } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    // std::cout << "----4------" << std::endl;
    // // Test 4: Multiple references
    // {
    //      MySmartPointer<MyTree> sp1(new MyTree(parseInput("/ cos 1 aaaa")));
    //     MySmartPointer<MyTree> sp2 = sp1; // Copy constructor
    //     MySmartPointer<MyTree> sp3 = sp2; // Copy constructor
    //     std::cout << "Value in sp1: " << sp1->toString() << std::endl;
    //     std::cout << "Value in sp2: " << sp2->toString() << std::endl;
    //     std::cout << "Value in sp3: " << sp3->toString() << std::endl;
    // } 

    //  std::cout << "----4------" << std::endl;
    // // Test 5: MS trees
    // {
    //     MyTree tree1(parseInput("+ ab c"));
    //     MyTree tree2(parseInput("- de f"));

    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;

    //     std::cout << "----AFTER-----" << std::endl;
    //     tree1 = tree2;

    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;
    // }

    // std::cout << "----4------" << std::endl;
    // // Test 5: MS trees
    // {
    //     MyTree tree1(parseInput("+ ab c"));
    //     MyTree tree2(parseInput("- de f"));

    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;

    //     std::cout << "----AFTER-----" << std::endl;
    //     tree1 = std::move(tree2);

        
    //     std::cout << "TREE 1: " << tree1.toString() << std::endl;
    //     std::cout << "TREE 2: " << tree2.toString() << std::endl;
    // }

    // std::cout << "All tests completed successfully!" << std::endl;
    // return 0;
}



    // std::cout << "----------" << std::endl;

    // // // Test 4: Move constructor
    // {
    //     MySmartPointer<TestObject> sp1(new TestObject(50));
    //     MySmartPointer<TestObject> sp2 = std::move(sp1); // Move constructor
    //     if (sp1.operator->() == nullptr) {
    //         std::cout << "sp1 is null after move." << std::endl;
    //     }
    //     std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    // } // sp2 goes out of scope; TestObject should be destroyed.

    // std::cout << "----------" << std::endl;

    // // Test 5: Move assignment
    // {
    //     MySmartPointer<TestObject> sp1(new TestObject(70));
    //     MySmartPointer<TestObject> sp2(new TestObject(80));
    //     sp2 = std::move(sp1); // Move assignment
    //     if (sp1.operator->() == nullptr) {
    //         std::cout << "sp1 is null after move." << std::endl;
    //     }
    //     std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    // } // sp2 goes out of scope; TestObject should be destroyed.

    // std::cout << "----------" << std::endl;



     // // Test 1
    // {
    //    // TestObject t(45);
    //    // MySmartPointer<TestObject> sp1(&t); //gdy statycznie zalokujemy podwojnie usunie nam objekt (bedzie próbował)
    //     MySmartPointer<TestObject> sp1(new TestObject(45));
    //     std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
    //     sp1->setValue(100);
    //     std::cout << "Updated value in sp1: " << (*sp1).getValue() << std::endl;
    // } // sp1 goes out of scope, and TestObject should be destroyed.

    // std::cout << "----------" << std::endl;

    // // Test 2: Copy constructor
    // {
    //     MySmartPointer<TestObject> sp1(new TestObject(10));
    //     MySmartPointer<TestObject> sp2 = sp1; // Copy constructor
    //     std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
    //     std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    // } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    // std::cout << "----------" << std::endl;

    // // Test 3: Copy assignment
    // {
    //     MySmartPointer<TestObject> sp1(new TestObject(20));
    //     MySmartPointer<TestObject> sp2 (new TestObject(30));
    //     sp2 = sp1; // Copy assignment
    //     std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
    //     std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    // } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    // // Test 4: Multiple references
    // {
    //     MySmartPointer<TestObject> sp1(new TestObject(90));
    //     MySmartPointer<TestObject> sp2 = sp1; // Copy constructor
    //     MySmartPointer<TestObject> sp3 = sp2; // Copy constructor
    //     std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
    //     std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    //     std::cout << "Value in sp3: " << sp3->getValue() << std::endl;
    // } 