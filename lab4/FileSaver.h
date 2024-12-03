#pragma once

#include "Result.h"

#include <fstream>


template<typename T,typename E>
class FileSaver
{
    public:
        void saveToFile(Result<T, E>& result, std::string& filename) 
        {
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr<<"file cannot be opened"<<std::endl;
                return;
            }

            file<<result;
            file<<"\n";

            file.close();
        }   
    private:

};