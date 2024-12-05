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

int main() {
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

    //Tests for trees
    {
        MyTree* subTree = new MyTree(parseInput("cos y")); //check that
        MySmartPointer<MyTree> sp1(new MyTree(parseInput("+ 1 sin x")));
        std::cout << "Value in sp1: " << sp1->toString() << std::endl;
        sp1->addSubTree(subTree);
        std::cout << "Updated value in sp1: " << (*sp1).toString() << std::endl;
    }

    std::cout << "----------" << std::endl;
    // Test 2: Copy constructor
    {
        MySmartPointer<MyTree> sp1(new MyTree(parseInput("* ab 10")));
        MySmartPointer<MyTree> sp2 = sp1; // Copy constructor
        std::cout << "Value in sp1: " << sp1->toString() << std::endl;
        std::cout << "Value in sp2: " << sp2->toString() << std::endl;
    } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    std::cout << "----------" << std::endl;

    // Test 3: Copy assignment
    {
        MySmartPointer<MyTree> sp1(new MyTree(parseInput("/ cos 1 5")));
        MySmartPointer<MyTree> sp2 (new MyTree(parseInput("/ 1 8")));
        sp2 = sp1; // Copy assignment
        std::cout << "Value in sp1: " << sp1->toString() << std::endl;
        std::cout << "Value in sp2: " << sp2->toString() << std::endl;
    } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    std::cout << "----------" << std::endl;
    // Test 4: Multiple references
    {
         MySmartPointer<MyTree> sp1(new MyTree(parseInput("/ cos 1 aaaa")));
        MySmartPointer<MyTree> sp2 = sp1; // Copy constructor
        MySmartPointer<MyTree> sp3 = sp2; // Copy constructor
        std::cout << "Value in sp1: " << sp1->toString() << std::endl;
        std::cout << "Value in sp2: " << sp2->toString() << std::endl;
        std::cout << "Value in sp3: " << sp3->toString() << std::endl;
    } 

    std::cout << "All tests completed successfully!" << std::endl;
    return 0;
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