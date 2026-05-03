/*
This file binds the Bit7zLibrary, the DLL provider of bit7z.
(bit7z uses it to call the DLL of 7-zip, like 7z.dll, 7za.dll and so on)
(For more details, see website https://github.com/rikyoz/bit7z/wiki/7z-DLLs)
(To get the extra DLLs, download 7z-extra package from https://www.7-zip.org/a/7z2600-extra.7z)
(Want other versions of 7-zip DLLs? Use the version number you want to replace "2600" in the above URL, for example, "2501" for 7-zip 25.01)
Author: ZhouSicheng-2011
Time: 2026-02-23
License: This project is under the Apache-2.0 Lincense, see LICENSE for more details.
*/

#include <bit7z/bit7zlibrary.hpp>
#include <API.hpp>

void init_lib(py::module& mod){
    //Bind the default 7-zip dll of bit7z
    mod.attr("DEFAULT_7ZIP_DLL") = py::cast(bit7z::kDefaultLibrary);

    //Bind the Bit7zLibrary class
    py::class_<bit7z::Bit7zLibrary>(mod, "Bit7zLibrary")
        .def(py::init<const std::string&>(), "Constructs a Bit7zLibrary object by loading the specified 7zip shared library. By default, it searches a 7z.dll in the same path of the application. Args: libraryPath(str): the path to the shared library file to be loaded.")
        .def("set_large_page_mode", &bit7z::Bit7zLibrary::setLargePageMode, "Set the 7-zip shared library to use large memory pages.");
}

