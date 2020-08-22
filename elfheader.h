#pragma once
#include <iostream>
#include <cstring>


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

class ELFHeader{
    protected:

        void ReadMagic(){
            ReadRaw(_magic, _reader_address);
            std::cout << "MAGIC: " << std::hex << _magic << std::endl;
        }

        void ReadAddressSize(){
            ReadRaw(_address_size, _reader_address);
            std::cout << "Address Size: " << std::hex << (int)_address_size << std::endl;
        }

        void ReadEndianness(){
            ReadRaw(_endianess, _reader_address);
            std::cout << "Endian: " << std::hex << (int)_endianess << std::endl;
        }

        void ReadVersion(){
            ReadRaw(_version, _reader_address);
            std::cout << "ELF Version: " << std::hex << (int)_version << std::endl;
        }

        void ReadOperatingSystemABI(){
            ReadRaw(_os_abi, _reader_address);
            std::cout << "ABI: " << std::hex << (int)_os_abi << std::endl;
        }

        void ReadABIVersion(){
            ReadRaw(_abi_version, _reader_address);
            std::cout << "ABI Version: " << std::hex << (int)_abi_version << std::endl;
        }

        void Padding(size_t range){
            for (size_t i = 0; i < range; i++)
                if (*(_reader_address+i) != 0)
                    std::cerr << "Warning: Padding nonzero!!!" << std::endl;
            _reader_address+=range;
        }

        void ReadOBJType(){
            ReadRaw(_obj_type, _reader_address);
            std::cout << "Object File Type: " << std::hex << (int)_obj_type << std::endl;
        }

        void ReadInstructionSet(){
            ReadRaw(_instruction_set, _reader_address);
            std::cout << "Instruction Set: " << std::hex << (int)_instruction_set << std::endl;
        }
    
        void ReadEntryAddress(){
            ReadRaw(_e_entry, _reader_address, static_cast<uint8_t>(_address_size));
            std::cout << "Entry Point: " << std::hex << (int)_e_entry << std::endl;
        }

        void ReadProgramHeaderTable(){
            ReadRaw(_e_phoff, _reader_address, static_cast<uint8_t>(_address_size));
            std::cout << "Program Header Table: " << std::hex << (int)_e_phoff << std::endl;
        }

        void ReadShoff(){
            ReadRaw(_e_shoff, _reader_address, static_cast<uint8_t>(_address_size));
            std::cout << "Shoff: " << std::hex << (int)_e_shoff << std::endl;
        }

        void ReadFlags(){
            ReadRaw(_e_flags, _reader_address);
            std::cout << "Flags: " << std::hex << (int)_e_flags << std::endl;
        }

    public:

       ELFHeader(std::vector<uint8_t>::iterator begin) : _reader_address(begin){
           ReadMagic();
           ReadAddressSize();
           ReadEndianness();
           ReadVersion();
           ReadOperatingSystemABI();
           ReadABIVersion();
           Padding(7);
           ReadOBJType();
           ReadInstructionSet();
           _reader_address+=4;//version again?
           ReadEntryAddress();
           ReadProgramHeaderTable();
           ReadShoff();
           ReadFlags();
       }


    private:
        std::vector<uint8_t>::iterator _reader_address;
        uint32_t _magic;

        enum class AddressSize : uint8_t{
            X32 = 0x01,
            x64 = 0x02
        } _address_size;

        enum class Endianness : uint8_t{
            LittleEndian = 0x01,
            BigEndian    = 0x02
        } _endianess;

        uint8_t _version;

        enum class OperatingSystemABI : uint8_t{
            SystemV       = 0x00,
            HP_UX         = 0x01,
            NetBSD        = 0x02,
            Linux         = 0x03,
            GNU_Hurd      = 0x04,
            Solaris       = 0x06,
            AIX           = 0x07,
            IRIX          = 0x08,
            FreeBSD       = 0x09,
            Tru64         = 0x0A,
            NovellModesto = 0x0B,
            OpenBSD       = 0x0C,
            OpenVMS       = 0x0D,
            NonStopKernel = 0x0E,
            AROS          = 0x0F,
            FenixOS       = 0x10,
            CloudABI      = 0x11,
            OpenVOS       = 0x12
        } _os_abi;

        uint8_t _abi_version;
        
        enum class ObjectFileType : uint16_t{
            ET_NONE   = 0x00,
            ET_REL    = 0x01,
            ET_EXEC   = 0x02,
            ET_DYN    = 0x03,
            ET_CORE   = 0x04,
            ET_LOOS   = 0xfe00,
            ET_HIOS   = 0xfeff,
            ET_LOPROC = 0xff00,
            ET_HIPROC = 0xffff
        } _obj_type;

        enum class InstructionSet : uint16_t{
            ET_NONE   = 0x00,
            ET_REL    = 0x01,
            ET_EXEC   = 0x02,
            ET_DYN    = 0x03,
            ET_CORE   = 0x04,
            ET_LOOS   = 0xfe00,
            ET_HIOS   = 0xfeff,
            ET_LOPROC = 0xff00,
            ET_HIPROC = 0xffff
        } _instruction_set;

        uint64_t _e_entry;
        uint64_t _e_phoff;
        uint64_t _e_shoff;
        uint32_t _e_flags;
};