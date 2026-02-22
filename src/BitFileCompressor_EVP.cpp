//bit7z header
#include <bitfilecompressor.hpp>

//My headers
#include <API.hpp>

//BitFileCompressor interface
void init_bitcompressor(py::module& mod){
    py::class_<bit7z::BitFileCompressor>(mod, "BitFileCompressor")
        .def()
}