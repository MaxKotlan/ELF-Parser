#pragma once

class ProgramHeader{
    public:
        ProgramHeader(std::vector<uint8_t>::iterator begin){
            for (int i = 0; i < 10; i++)
                std::cout << (int)*(begin++) << " "; 
            std::cout << "Program Header begins at: 0x" << ((*begin)) << std::endl;
        }

};