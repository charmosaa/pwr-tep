#pragma once


template <typename T>
class MySmartPointer
{
    public:
    MySmartPointer(T *pcPointer) { pc_pointer = pcPointer; }
    ~MySmartPointer() { delete pc_pointer; }
    T& operator*() { return(*pc_pointer); }
    T* operator->() { return(pc_pointer); }
    private:
    T *pc_pointer;

};//class MySmartPointer

