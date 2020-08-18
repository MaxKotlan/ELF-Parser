#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class FileReader{
    public:
        FileReader(std::string path) : _path(path){
            _file = fopen (_path.c_str(),"rb+");
            if (!_file){
                std::cout << "Could not open";
                exit(-1);
            }
            fseek(_file, 0L, SEEK_END);
            _data.resize(ftell(_file));
            fseek(_file, 0L, SEEK_SET);
            
            fread(_data.data(), _data.size(), sizeof(uint8_t), _file);
        }

        std::vector<uint8_t>* data() { return &_data; };

    private:
        std::string _path;
        FILE* _file;
        std::vector<uint8_t> _data;
};