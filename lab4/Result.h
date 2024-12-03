#pragma once
#include <vector>
#include <string>

#include <iostream>

template <typename T, typename E>
class Result
{
    public:
        Result(const T& value);
        Result(E* error);
        Result(std::vector<E*>& errors);
        Result(const Result<T, E>& other);
        ~Result();
        static Result<T, E> ok(const T& value);
        static Result<T, E> fail(E* error);
        static Result<T, E> fail(std::vector<E*>& errors);
        Result<T, E>& operator=(const Result<T, E>& other);
        bool isSuccess();
        T getValue();
        std::vector<E*>& getErrors();
        void print();
        void setValue(T value);
        template <typename U, typename F>
        friend std::ostream& operator<<(std::ostream& os, Result<U,F>& obj);
    private:
        T *value;
        std::vector<E*> errors;
};

template <typename T, typename E>
Result<T,E>::Result(const T& value)
{
    this->value = new T(value);
}

template <typename T, typename E>
Result<T,E>::Result(E* error)
{
    errors.push_back(new E(*error));
    value = nullptr;
}


template <typename T, typename E>
Result<T,E>::Result(std::vector<E*>& errors)
{
    for(int i=0;i<errors.size();i++)
        this->errors.push_back(new E(*errors[i]));
    value = nullptr;
}

template <typename T, typename E>
Result<T,E>::Result(const Result<T, E>& other)
{
    if(other.value == nullptr)
    {
        value = nullptr;
        for(int i=0;i<other.errors.size();i++)
            errors.push_back(new E(*other.errors[i]));
    }
    else
        value = new T(*other.value);
   
}

template <typename T, typename E>
Result<T,E>::~Result()
{
    for(int i=0;i<errors.size();i++)
        delete errors[i];
    errors.clear();
    delete value;
    std::cout<<"deleted result"<<std::endl;
}


template <typename T, typename E>
Result<T,E> Result<T, E>::ok(const T& value)
{
    return Result<T,E>(value);
}

template <typename T, typename E>
Result<T,E> Result<T, E>::fail(E* error) 
{
    return Result<T,E>(error);
}

template <typename T, typename E>
Result<T,E> Result<T, E>::fail(std::vector<E*>& errors)
{
    return Result<T,E>(errors);
}


template <typename T, typename E>
Result<T,E>& Result<T, E>::operator=(const Result<T, E>& other)
{
    delete value;
    for (int i=0;i<errors.size();i++)
        delete errors[i];
    errors.clear();

    if (other.value == nullptr)
    {
        value = nullptr;
    }
    else
    {
        value = new T(*other.value);
    }

    for (int i = 0; i < other.errors.size(); i++)
    {
        errors.push_back(new E(*other.errors[i]));
    }

    return *this;
}

template <typename T, typename E>
bool Result<T,E>::isSuccess()
{
    return value != nullptr;
}


template <typename T, typename E>
T Result<T,E>::getValue()
{
    return *value;
}

template <typename T, typename E>
void Result<T,E>::setValue(T value)
{
    delete this->value;
    this->value = new T(value);
}


template <typename T, typename E>
std::vector<E*>& Result<T,E>::getErrors()
{
    return errors;
}

template <typename T, typename E>
void Result<T,E>::print()
{
    if(isSuccess())
       std::cout<<*value<<std::endl;
    else
    {
        for(int i=0;i<errors.size();i++)
             std::cout<<errors[i]->toString()<<std::endl;
    }
    std::cout<<std::endl;
}

template <typename U, typename F>
std::ostream& operator<<(std::ostream& os, Result<U,F>& obj)
{
    if(obj.isSuccess())
       os<<*obj.value;
    else
    {
        for(int i=0;i<obj.errors.size();i++)
             os<<obj.errors[i]->toString()<<"\n";
    }
    return os;
}



template<typename E>
class Result<void, E>
{
    public:
        Result();
        Result(E *error);
        Result(std::vector<E*>& errors);
        Result(const Result<void, E>& other);
        ~Result();
        static Result<void, E> ok();
        static Result<void, E> fail(E* error);
        static Result<void, E> fail(std::vector<E*>& errors);
        Result<void, E>& operator=(const Result<void, E>& other);
        bool isSuccess();
        std::vector<E*>& getErrors();
    private:
        std::vector<E*> errors;
};

template <typename E>
Result<void,E>::Result()
{
    errors.clear();
}

template <typename E>
Result<void,E>::Result(E* error)
{
    errors.push_back(new E(*error));
}


template <typename E>
Result<void,E>::Result(std::vector<E*>& errors)
{
    for(int i=0;i<errors.size();i++)
        this->errors.push_back(new E(*errors[i]));
}

template <typename E>
Result<void,E>::Result(const Result<void, E>& other)
{
    for(int i=0;i<other.errors.size();i++)
        errors.push_back(new E(*other.errors[i]));
}

template <typename E>
Result<void,E>::~Result()
{
    for(int i=0;i<errors.size();i++)
        delete errors[i];
    errors.clear();
}


template <typename E>
Result<void,E> Result<void, E>::ok()
{
    return Result<void,E>();
}

template <typename E>
Result<void,E> Result<void, E>::fail(E* error) 
{
    return Result<void,E>(error);
}

template <typename E>
Result<void,E> Result<void, E>::fail(std::vector<E*>& errors)
{
    return Result<void,E>(errors);
}


template <typename E>
Result<void,E>& Result<void, E>::operator=(const Result<void, E>& other)
{
    for(int i=0;i<errors.size();i++)
        delete errors[i];
    errors.clear();

    for(int i=0;i<other.errors.size();i++)
        errors.push_back(new E(*other.errors[i]));

    return *this;
}

template <typename E>
bool Result<void, E>::isSuccess()
{
    return errors.empty();
}


template <typename E>
std::vector<E*>& Result<void,E>::getErrors()
{
    return errors;
}

