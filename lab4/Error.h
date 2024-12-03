#pragma once

#include <string>

class Error
{
    public:
        std::string description;
        Error();
        Error(std::string description);
        Error(const Error& other);
        std::string toString();
    private:

};