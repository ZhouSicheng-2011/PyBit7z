import py7zr
import os
import time
import shutil


if os.path.exists("./test"):
    shutil.rmtree("./test", ignore_errors=True)

with py7zr.SevenZipFile("E:/gtk-build.7z", mode='r') as fp:
    s = time.time()
    fp.extractall("./test")
    print(time.time() - s)

shutil.rmtree("./test", ignore_errors=True)  