#pragma once
#include "filereader.h"
#include "elfheader.h"

class ELF{
    public:
    ELF(std::string filename) : _filereader(filename){
        ELFHeader(_filereader.begin());
        //for (auto ch : *_filereader.data())
        //    std::cout << "";//(int)ch;
    }

    private:
        FileReader _filereader;
};