# setup.py
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

import sys
import platform
import os
import pathlib

HERE = pathlib.Path(__file__).parent
README = (HERE / "README.md").read_text(encoding="utf-8")

ver_major = 0
ver_minor = 0
ver_patch = 1
__version__ = f"{ver_major}.{ver_minor}.{ver_patch}"

macros = [("VERSION_INFO", __version__)]
try:
    if sys._is_gil_enabled() == False:
        macros.append(("PYTHON_313_PLUS_FREE_THREADING_BUILD", ""))
except:
    pass

if platform.system() == "Windows":
    bit7z_type = "windows-msvc"
    bit7z_lib_dir = f"bit7z-{bit7z_type}/lib/x64"
    cpp_flags = ["/O2", "/favor:blend", "/std:c++17", "/utf-8", \
                 f"/DVER_MAJOR={ver_major}", f"/DVER_MINOR={ver_minor}", \
                    f"/DVER_PATCH={ver_patch}"]
    libs = [
            "bit7z", # bit7z static library
            "pyos", # Python style system API library
            "OleAut32" # dependency of bit7z on Windows                              
            ]
    deps = ["7zip/7z.dll"]
elif platform.system() == "Linux":
    bit7z_type = "linux-gcc"
    bit7z_lib_dir = f"bit7z-{bit7z_type}/lib/x64"
    cpp_flags = ["-O3", "-std=c++17", \
                 f"-DVER_MAJOR={ver_major}", f"-DVER_MINOR={ver_minor}", \
                    f"-DVER_PATCH={ver_patch}"]
    libs = [
        "bit7z", # bit7z static library
        "pyos", # Python style system API library
        "dl" # dependency of bit7z on Linux
    ]
    deps = ["7zip/7z.so"]

ext_modules = [
    Pybind11Extension(
        "bit7z_python",                                     
        ["src/core.cpp"],           
        define_macros = macros,
        include_dirs = [
            os.path.normpath(os.path.abspath(f"bit7z-{bit7z_type}/include/bit7z")),
            os.path.normpath(os.path.abspath("src")),
            os.path.normpath(os.path.abspath("include"))
        ],
        library_dirs = [
            os.path.normpath(os.path.abspath(bit7z_lib_dir)),
            os.path.normpath(os.path.abspath("include/dist"))
        ],
        libraries = libs,
        extra_compile_args = cpp_flags
    ),
]

setup(
    name="bit7z_python",
    version=__version__,
    author="ZhouSicheng-2011",
    author_email="ZSCinYBSZ2023@outlook.com",
    url="https://github.com/ZhouSicheng-2011/bit7z-python",
    license="Apache-2.0",
    description="Python bindings for bit7z",
    long_description=README,
    long_description_content_type="text/markdown",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.9",
    package_data={
        "bit7z_python": deps
    }
)