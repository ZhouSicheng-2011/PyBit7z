/*
This file binds the BitFileCompressor, the file compressor of bit7z.
Author: ZhouSicheng-2011
Time: 2026-05-01
License: This project is under the Apache-2.0 Lincense, see LICENSE for more details.
*/

//bit7z header
#include <bitfilecompressor.hpp>

//My headers
#include <API.hpp>

//BitFileCompressor interface
void init_bitcompressor(py::module& mod){
    py::class_<bit7z::BitFileCompressor>(mod, "BitFileCompressor")
        .def(py::init<const bit7z::Bit7zLibrary&, const bit7z::BitInOutFormat&>())
        .def("clear_password", &bit7z::BitFileCompressor::clearPassword, "Clear the current password used by the handler. Calling clearPassword() will disable the encryption/decryption of archives.")
        .def("compress", py::overload_cast<const std::map<std::string, std::string>&, const std::string&>(&bit7z::BitFileCompressor::compress))
        ;
}