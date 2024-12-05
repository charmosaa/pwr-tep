#include <iostream>
#include "MySmartPointer.h"

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

int main() {
    // Test 1: Basic functionality
    {
       // TestObject t(45);
       // MySmartPointer<TestObject> sp1(&t); //gdy statycznie zalokujemy podwojnie usunie nam objekt (bedzie próbował)
        MySmartPointer<TestObject> sp1(new TestObject(45));
        std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
        sp1->setValue(100);
        std::cout << "Updated value in sp1: " << (*sp1).getValue() << std::endl;
    } // sp1 goes out of scope, and TestObject should be destroyed.

    std::cout << "----------" << std::endl;

    // Test 2: Copy constructor
    {
        MySmartPointer<TestObject> sp1(new TestObject(10));
        MySmartPointer<TestObject> sp2 = sp1; // Copy constructor
        std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
        std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

    std::cout << "----------" << std::endl;

    // Test 3: Copy assignment
    {
        MySmartPointer<TestObject> sp1(new TestObject(20));
        MySmartPointer<TestObject> sp2 (new TestObject(30));
        sp2 = sp1; // Copy assignment
        std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
        std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
    } // Both sp1 and sp2 go out of scope; TestObject should be destroyed once.

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

    // Test 6: Multiple references
    {
        MySmartPointer<TestObject> sp1(new TestObject(90));
        MySmartPointer<TestObject> sp2 = sp1; // Copy constructor
        MySmartPointer<TestObject> sp3 = sp2; // Copy constructor
        std::cout << "Value in sp1: " << sp1->getValue() << std::endl;
        std::cout << "Value in sp2: " << sp2->getValue() << std::endl;
        std::cout << "Value in sp3: " << sp3->getValue() << std::endl;
    } // All references go out of scope; TestObject should be destroyed once.

    std::cout << "All tests completed successfully!" << std::endl;
    return 0;
}
