/*
This file binds the BitInFormat and BitInOutFormat, the format provider of bit7z.
(bit7z uses it to know the format of the archive)
(For more details, see website https://github.com/rikyoz/bit7z/wiki/BitFormat)
Author: ZhouSicheng-2011
Time: 2026-05-03
License: This project is under the Apache-2.0 Lincense, see LICENSE for more details.
*/

//Enable bit7z auto format detection
#ifndef BIT7Z_AUTO_FORMAT
#define BIT7Z_AUTO_FORMAT
#endif

#include <API.hpp>
#include <bitformat.hpp>

void init_formats(py::module_& mod){
    py::class_<bit7z::BitInFormat>(mod, "BitInFormat")
        .def("__eq__", &bit7z::BitInFormat::operator==, "Checks if two BitInFormat objects are equal.")
        .def("__ne__", &bit7z::BitInFormat::operator!=, "Checks if two BitInFormat objects are not equal.")
        .def("value", &bit7z::BitInFormat::value, "Returns the ID value of this BitInFormat object.");
        
    py::class_<bit7z::BitInOutFormat>(mod, "BitOutFormat")
        .def("__eq__", &bit7z::BitInOutFormat::operator==, "Checks if two BitOutFormat objects are equal.")
        .def("__ne__", &bit7z::BitInOutFormat::operator!=, "Checks if two BitOutFormat objects are not equal.")
        .def("value", &bit7z::BitInOutFormat::value, "Returns the ID value of this BitOutFormat object.");

    // 导出格式常量 —— 使用 py::cast 并指定引用策略，避免拷贝不可拷贝对象
    mod.attr("FORMAT_APM") = py::cast(bit7z::BitFormat::APM, py::return_value_policy::reference);
    mod.attr("FORMAT_ARJ") = py::cast(bit7z::BitFormat::Arj, py::return_value_policy::reference);
    // mod.attr("FORMAT_AUTO") = py::cast(bit7z::BitFormat::Auto, py::return_value_policy::reference); // 已注释
    mod.attr("FORMAT_BZIP2") = py::cast(bit7z::BitFormat::BZip2, py::return_value_policy::reference);
    mod.attr("FORMAT_CAB") = py::cast(bit7z::BitFormat::Cab, py::return_value_policy::reference);
    mod.attr("FORMAT_CHM") = py::cast(bit7z::BitFormat::Chm, py::return_value_policy::reference);
    mod.attr("FORMAT_COFF") = py::cast(bit7z::BitFormat::COFF, py::return_value_policy::reference);
    mod.attr("FORMAT_COMPOUND") = py::cast(bit7z::BitFormat::Compound, py::return_value_policy::reference);
    mod.attr("FORMAT_CPIO") = py::cast(bit7z::BitFormat::Cpio, py::return_value_policy::reference);
    mod.attr("FORMAT_CRAMFS") = py::cast(bit7z::BitFormat::CramFS, py::return_value_policy::reference);
    mod.attr("FORMAT_DEB") = py::cast(bit7z::BitFormat::Deb, py::return_value_policy::reference);
    mod.attr("FORMAT_DMG") = py::cast(bit7z::BitFormat::Dmg, py::return_value_policy::reference);
    mod.attr("FORMAT_ELF") = py::cast(bit7z::BitFormat::Elf, py::return_value_policy::reference);
    mod.attr("FORMAT_EXT") = py::cast(bit7z::BitFormat::Ext, py::return_value_policy::reference);
    mod.attr("FORMAT_FAT") = py::cast(bit7z::BitFormat::Fat, py::return_value_policy::reference);
    mod.attr("FORMAT_FLV") = py::cast(bit7z::BitFormat::Flv, py::return_value_policy::reference);
    mod.attr("FORMAT_GPT") = py::cast(bit7z::BitFormat::GPT, py::return_value_policy::reference);
    mod.attr("FORMAT_GZIP") = py::cast(bit7z::BitFormat::GZip, py::return_value_policy::reference);
    mod.attr("FORMAT_HFS") = py::cast(bit7z::BitFormat::Hfs, py::return_value_policy::reference);
    mod.attr("FORMAT_HXS") = py::cast(bit7z::BitFormat::Hxs, py::return_value_policy::reference);
    mod.attr("FORMAT_IHEX") = py::cast(bit7z::BitFormat::IHex, py::return_value_policy::reference);
    mod.attr("FORMAT_ISO") = py::cast(bit7z::BitFormat::Iso, py::return_value_policy::reference);
    mod.attr("FORMAT_LZH") = py::cast(bit7z::BitFormat::Lzh, py::return_value_policy::reference);
    mod.attr("FORMAT_LZMA") = py::cast(bit7z::BitFormat::Lzma, py::return_value_policy::reference);
    mod.attr("FORMAT_LZMA86") = py::cast(bit7z::BitFormat::Lzma86, py::return_value_policy::reference);
    mod.attr("FORMAT_MACHO") = py::cast(bit7z::BitFormat::Macho, py::return_value_policy::reference);
    mod.attr("FORMAT_MBR") = py::cast(bit7z::BitFormat::Mbr, py::return_value_policy::reference);
    mod.attr("FORMAT_MSLZ") = py::cast(bit7z::BitFormat::Mslz, py::return_value_policy::reference);
    mod.attr("FORMAT_MUB") = py::cast(bit7z::BitFormat::Mub, py::return_value_policy::reference);
    mod.attr("FORMAT_NSIS") = py::cast(bit7z::BitFormat::Nsis, py::return_value_policy::reference);
    mod.attr("FORMAT_NTFS") = py::cast(bit7z::BitFormat::Ntfs, py::return_value_policy::reference);
    mod.attr("FORMAT_PE") = py::cast(bit7z::BitFormat::Pe, py::return_value_policy::reference);
    mod.attr("FORMAT_PPMD") = py::cast(bit7z::BitFormat::Ppmd, py::return_value_policy::reference);
    mod.attr("FORMAT_QCOW") = py::cast(bit7z::BitFormat::QCow, py::return_value_policy::reference);
    mod.attr("FORMAT_RAR") = py::cast(bit7z::BitFormat::Rar, py::return_value_policy::reference);
    mod.attr("FORMAT_RAR5") = py::cast(bit7z::BitFormat::Rar5, py::return_value_policy::reference);
    mod.attr("FORMAT_RPM") = py::cast(bit7z::BitFormat::Rpm, py::return_value_policy::reference);
    mod.attr("FORMAT_7Z") = py::cast(bit7z::BitFormat::SevenZip, py::return_value_policy::reference);
    mod.attr("FORMAT_SPLIT") = py::cast(bit7z::BitFormat::Split, py::return_value_policy::reference);
    mod.attr("FORMAT_SQUASHFS") = py::cast(bit7z::BitFormat::SquashFS, py::return_value_policy::reference);
    mod.attr("FORMAT_SWF") = py::cast(bit7z::BitFormat::Swf, py::return_value_policy::reference);
    mod.attr("FORMAT_SWFC") = py::cast(bit7z::BitFormat::Swfc, py::return_value_policy::reference);
    mod.attr("FORMAT_TAR") = py::cast(bit7z::BitFormat::Tar, py::return_value_policy::reference);
    mod.attr("FORMAT_TE") = py::cast(bit7z::BitFormat::TE, py::return_value_policy::reference);
    mod.attr("FORMAT_UDF") = py::cast(bit7z::BitFormat::Udf, py::return_value_policy::reference);
    mod.attr("FORMAT_UEFIC") = py::cast(bit7z::BitFormat::UEFIc, py::return_value_policy::reference);
    mod.attr("FORMAT_UEFIS") = py::cast(bit7z::BitFormat::UEFIs, py::return_value_policy::reference);
    mod.attr("FORMAT_VDI") = py::cast(bit7z::BitFormat::VDI, py::return_value_policy::reference);
    mod.attr("FORMAT_VHD") = py::cast(bit7z::BitFormat::Vhd, py::return_value_policy::reference);
    mod.attr("FORMAT_VHDX") = py::cast(bit7z::BitFormat::Vhdx, py::return_value_policy::reference);
    mod.attr("FORMAT_VMDK") = py::cast(bit7z::BitFormat::VMDK, py::return_value_policy::reference);
    mod.attr("FORMAT_WIM") = py::cast(bit7z::BitFormat::Wim, py::return_value_policy::reference);
    mod.attr("FORMAT_XAR") = py::cast(bit7z::BitFormat::Xar, py::return_value_policy::reference);
    mod.attr("FORMAT_XZ") = py::cast(bit7z::BitFormat::Xz, py::return_value_policy::reference);
    mod.attr("FORMAT_Z") = py::cast(bit7z::BitFormat::Z, py::return_value_policy::reference);
    mod.attr("FORMAT_ZIP") = py::cast(bit7z::BitFormat::Zip, py::return_value_policy::reference);
}