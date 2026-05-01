/*
This file binds the Bit7zLibrary, the DLL provider of bit7z.
(bit7z uses it to call the DLL of 7-zip, like 7z.dll, 7za.dll and so on)
(For more details, see website https://github.com/rikyoz/bit7z/wiki/7z-DLLs)
(To get the extra DLLs, download 7z-extra package from https://www.7-zip.org/a/7z2600-extra.7z)
(Want other versions of 7-zip DLLs? Use the version number you want to replace "2600" in the above URL, for example, "2501" for 7-zip 25.01)
Author: ZhouSicheng-2011
Time: 2026-02-26
License: This project is under the Apache-2.0 Lincense, see LICENSE for more details.
*/


#include <API.hpp>
#include <bit7z/bitformat.hpp>

void init_formats(py::module mod){
    py::class_<bit7z::BitInFormat>(mod, "BitInFormat")
        .def(py::init<unsigned char>(), "Constructs a BitInFormat object with the ID value used by the 7z SDK. Warning: Don't use it unless you know 7-zip SDK well. This constructor is just for binding the formats easier, you only need to use the formats constants provided by bit7z.")
        .def("__eq__", &bit7z::BitInFormat::operator==, "Checks if two BitInFormat objects are equal.")
        .def("__ne__", &bit7z::BitInFormat::operator!=, "Checks if two BitInFormat objects are not equal.")
        .def("value", &bit7z::BitInFormat::value, "Returns the ID value of this BitInFormat object.");
        
    py::class_<bit7z::BitInOutFormat>(mod, "BitOutFormat")
        .def(py::init<unsigned char>(), "Constructs a BitOutFormat object with the ID value used by the 7z SDK. Warning: Don't use it unless you know 7-zip SDK well. This constructor is just for binding the formats easier, you only need to use the formats constants provided by bit7z.")
        .def("__eq__", &bit7z::BitInOutFormat::operator==, "Checks if two BitOutFormat objects are equal.")
        .def("__ne__", &bit7z::BitInOutFormat::operator!=, "Checks if two BitOutFormat objects are not equal.")
        .def("value", &bit7z::BitInOutFormat::value, "Returns the ID value of this BitOutFormat object.");

    mod.attr("FORMAT_APM") = bit7z::BitFormat::APM;
    mod.attr("FORMAT_ARJ") = bit7z::BitFormat::Arj;
    mod.attr("FORMAT_AUTO") = bit7z::BitFormat::Auto;
    mod.attr("FORMAT_BZIP2") = bit7z::BitFormat::BZip2;
    mod.attr("FORMAT_CAB") = bit7z::BitFormat::Cab;
    mod.attr("FORMAT_CHM") = bit7z::BitFormat::Chm;
    mod.attr("FORMAT_COFF") = bit7z::BitFormat::COFF;
    mod.attr("FORMAT_COMPOUND") = bit7z::BitFormat::Compound;
    mod.attr("FORMAT_CPIO") = bit7z::BitFormat::Cpio;
    mod.attr("FORMAT_CRAMFS") = bit7z::BitFormat::CramFS;
    mod.attr("FORMAT_DEB") = bit7z::BitFormat::Deb;
    mod.attr("FORMAT_DMG") = bit7z::BitFormat::Dmg;
    mod.attr("FORMAT_ELF") = bit7z::BitFormat::Elf;
    mod.attr("FORMAT_EXT") = bit7z::BitFormat::Ext;
    mod.attr("FORMAT_FAT") = bit7z::BitFormat::Fat;
    mod.attr("FORMAT_FLV") = bit7z::BitFormat::Flv;
    mod.attr("FORMAT_GPT") = bit7z::BitFormat::GPT;
    mod.attr("FORMAT_GZIP") = bit7z::BitFormat::GZip;
    mod.attr("FORMAT_HFS") = bit7z::BitFormat::Hfs;
    mod.attr("FORMAT_HXS") = bit7z::BitFormat::Hxs;
    mod.attr("FORMAT_IHEX") = bit7z::BitFormat::IHex;
    mod.attr("FORMAT_ISO") = bit7z::BitFormat::Iso;
    mod.attr("FORMAT_LZH") = bit7z::BitFormat::Lzh;
    mod.attr("FORMAT_LZMA") = bit7z::BitFormat::Lzma;
    mod.attr("FORMAT_LZMA86") = bit7z::BitFormat::Lzma86;
    mod.attr("FORMAT_MACHO") = bit7z::BitFormat::Macho;
    mod.attr("FORMAT_MBR") = bit7z::BitFormat::Mbr;
    mod.attr("FORMAT_MSLZ") = bit7z::BitFormat::Mslz;
    mod.attr("FORMAT_MUB") = bit7z::BitFormat::Mub;
    mod.attr("FORMAT_NSIS") = bit7z::BitFormat::Nsis;
    mod.attr("FORMAT_NTFS") = bit7z::BitFormat::Ntfs;
    mod.attr("FORMAT_PE") = bit7z::BitFormat::Pe;
    mod.attr("FORMAT_PPMD") = bit7z::BitFormat::Ppmd;
    mod.attr("FORMAT_QCOW") = bit7z::BitFormat::QCow;
    //...
}
