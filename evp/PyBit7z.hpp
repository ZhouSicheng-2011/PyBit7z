/*
This is the main wrapper of bit7z for Python 3.8 or higher versions (pybind11-3.0.2)
*/

/*
If you want to use this program on Windows 7, please add "/DWIN7_COMPAT" opition in cl compiler command
*/
#ifdef WIN7_COMPAT
  #define _WIN32_WINNT 0x0601
  #define WINVER 0X0601
#endif

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/chrono.h>
#include <pybind11/gil.h>
namespace py = pybind11;

