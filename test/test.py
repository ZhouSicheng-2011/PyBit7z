import py7zr
import os
import time
import shutil


if os.path.exists("./test"):
    shutil.rmtree("./test", ignore_errors=True)

path = input("What file to extract? Please enter the path here:")
if not os.path.exists(path):
    print("File path does not exists.")
    exit(1)

with py7zr.SevenZipFile(path, mode='r') as fp:
    s = time.time()
    fp.extractall("./test")
    print(time.time() - s, "s")

shutil.rmtree("./test", ignore_errors=True)  