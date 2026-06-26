import os
import pathlib
import platform

def _set_dll_path():
    dll_dir = pathlib.Path(__file__) / "dll"

    if platform.system() == "Windows":
        os.add_dll_directory(str(dll_dir))
    
    elif platform.system() == "Linux":
        current = os.environ.get("LD_LIBRARY_PATH")
        if current is not None:
            os.environ["LD_LIBRARY_PATH"] = current + ":" + str(dll_dir)
        else:
            os.environ["LD_LIBRARY_PATH"] = str(dll_dir)
    
    elif platform.system() == "Darwin":
        current = os.environ.get("DYLD_LIBRARY_PATH")
        if current is not None:
            os.environ["DYLD_LIBRARY_PATH"] = current + ":" + str(dll_dir)
        else:
            os.environ["DYLD_LIBRARY_PATH"] = str(dll_dir)
    
    else:
        raise OSError("This is not a supported platform!")

_set_dll_path()