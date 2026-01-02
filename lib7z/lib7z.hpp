#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <chrono>
using namespace std;
#include <bit7z.hpp>
#include <bitarchiveeditor.hpp>
#include <bitarchivereader.hpp>
#include <bitarchiveitem.hpp>
#include <bitarchiveiteminfo.hpp>
using namespace bit7z;

//7z DLL(suppose these DLLs are all in the system path variable)
const Bit7zLibrary& dll_7z = Bit7zLibrary{"7z.dll"};
const Bit7zLibrary& dll_7za = Bit7zLibrary{"7za.dll"};

const Bit7zLibrary& load_7z_dll(const string& path){
    Bit7zLibrary& lib = Bit7zLibrary(path);
    return lib;
}

//Other functions
//...

//Lib7z main class
class Lib7zArchive{
    public:
        Lib7zArchive(const string& filename, const Bit7zLibrary& dll, const BitInOutFormat& format, const string& password={});
        Lib7zArchive(const string& filename, const Bit7zLibrary& dll, const BitInFormat& format, const string& password={});
};