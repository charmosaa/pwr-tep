#include "Error.h"

Error::Error()
{
    description = "";
}

Error::Error(std::string description)
{
    this->description=description;
}

Error::Error(const Error& other)
{
    description=other.description;
}

std::string Error::toString()
{
    return description;
}