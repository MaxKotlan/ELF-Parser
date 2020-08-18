#include <iostream>
#include "elf.h"

int main(int argc, char** argv){
    if (argc != 2) {
        std::cout << "Missing Filepath" << std::endl;
        return -1;
    }
    ELF(std::string(argv[1]));

    return 0;
}