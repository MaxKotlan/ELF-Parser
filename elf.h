#pragma once
#include "filereader.h"

class ELF{
    public:
    ELF(std::string filename) : _filereader(filename){
        for (auto ch : *_filereader.data())
            std::cout << ch;
    }

    private:
        FileReader _filereader;
};