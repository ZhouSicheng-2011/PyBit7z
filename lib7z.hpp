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

//Archive Item Info
typedef struct Lib7zArchiveItemInfo
{
    string path;
    uint32_t CRC32;
    uint64_t csize;
    uint64_t rsize;
    //...

};
