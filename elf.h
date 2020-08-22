#pragma once
#include "filereader.h"
#include "elfheader.h"
#include "programheader.h"

class ELF{
    public:
    ELF(std::string filename) : _filereader(filename), _elfheader(_filereader.begin()), _progheader(_elfheader.GetProgramHeaderOffset()){
        
        //for (auto ch : *_filereader.data())
        //    std::cout << "";//(int)ch;
    }

    private:
        FileReader _filereader;
        ELFHeader  _elfheader;
        ProgramHeader _progheader;
        
};