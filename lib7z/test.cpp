#include <iostream>
using namespace std;
#include <bitarchivereader.hpp>
using namespace bit7z;
#include <time.hpp>


void test_extract(){
    Bit7zLibrary lib = Bit7zLibrary{"D:/AppData/7-Zip/7z.dll"};
    BitArchiveReader archive = BitArchiveReader(lib, "E:/14.2.0posix-19.1.1-12.0.0-msvcrt-r2.7z", BitFormat::SevenZip);
    TimeProcessor timer = TimeProcessor();
    timer.startTimer();
    archive.extractTo("./test");
    double used_time = timer.stopTimer();
    cout<<used_time<<"s"<<endl;
}