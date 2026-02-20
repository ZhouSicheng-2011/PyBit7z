#ifndef BIT7Z_AUTO_FORMAT
#define BIT7Z_AUTO_FORMAT
#endif

#include <iostream>
using namespace std;
#include <bitarchivereader.hpp>
using namespace bit7z;
#include <time.hpp>
#include <pyos.hpp>

void test_extract(){
    Bit7zLibrary lib{"E:/7-Zip/7z.dll"};
    string path;
    cout<<"What file to extract? Please enter the path here:";
    cin>>path;
    if (os::path::exists(path) == false){
        cout<<"File path does not exists!";
        exit(1);
    }
    BitArchiveReader archive(lib, path, BitFormat::Auto);
    TimeProcessor timer = TimeProcessor();
    timer.startTimer();
    cout<<"Test start."<<endl;
    archive.extractTo("./test");
    double used_time = timer.stopTimer();
    cout<<used_time<<"s"<<endl;
}

int main(){
    test_extract();
    return 0;
}
/*compile:
cl /EHsc /MD /utf-8 /IE:\KwDownload\Lyric\Python\PyBit7z\bit7z-msvc-2022\include\bit7z /IE:\KwDownload\Lyric\Python\PyBit7z\include test.cpp /link E:\KwDownload\Lyric\Python\PyBit7z\bit7z-msvc-2022\lib\x64\Release\bit7z.lib E:\KwDownload\Lyric\Python\PyBit7z\include\dist\pyos.lib OleAut32.lib User32.lib kernel32.lib
*/