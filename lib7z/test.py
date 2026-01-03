import py7zr
import os
import time
import shutil


if os.path.exists("./test"):
    shutil.rmtree("./test", ignore_errors=True)

with py7zr.SevenZipFile("E:/14.2.0posix-19.1.1-12.0.0-msvcrt-r2.7z", mode='r') as fp:
    s = time.time()
    fp.extractall("./test")
    print(time.time() - s)

shutil.rmtree("./test", ignore_errors=True)  