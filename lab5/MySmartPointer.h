#pragma once

class RefCounter
{
public:
RefCounter() { count = 0; }
int add() { return(++count); }
int dec() { return(--count); }
int get() { return(count); }
private:
int count;
};//class RefCounter

template <typename T>
class MySmartPointer
{
    public:
    MySmartPointer(T *pointer);
    MySmartPointer(const MySmartPointer &other);
    ~MySmartPointer();
    T& operator*() { return(*pointer); }
    T* operator->() { return(pointer); }
    MySmartPointer& operator=(MySmartPointer &other);
    private:
    T *pointer;
    RefCounter *refCounter;

};//class MySmartPointer

template<typename T>
MySmartPointer<T>::MySmartPointer(T *pointer)
{
    this->pointer = pointer;
    refCounter = new RefCounter();
    refCounter->add();
}

template<typename T>
MySmartPointer<T>::MySmartPointer(const MySmartPointer &other)
{
    pointer = other.pointer;
    refCounter = other.refCounter;
    refCounter->add();
}

template<typename T>
MySmartPointer<T>::~MySmartPointer()
{
    if(refCounter && refCounter->dec() == 0)
    {
        delete pointer;
        delete refCounter;
    }
}

template<typename T>
MySmartPointer<T>& MySmartPointer<T>::operator=(MySmartPointer &other)
{
    if(refCounter && refCounter->dec() == 0)
    {
        delete pointer;
        delete refCounter;
    }

    pointer = other.pointer;
    refCounter = other.refCounter;
    refCounter->add();
    return *this;
}
