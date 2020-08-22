#pragma once


template <typename T>
void ReadRaw(T& result, std::vector<uint8_t>::iterator& it, uint8_t memorytype=0){
    switch(memorytype){
        case 0:
            std::memcpy(&result, &(*it), sizeof(T));
            it+=sizeof(T);
            break;
        case 1:
            std::memcpy(&result, &(*it), sizeof(uint32_t));
            it+=sizeof(uint32_t);
            break;
        case 2:
            std::memcpy(&result, &(*it), sizeof(uint64_t));
            it+=sizeof(uint64_t);
            break;
    }
}