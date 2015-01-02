import shutil
import os
import sys

currentPath = os.path.dirname(os.path.realpath(__file__))

def setupDist(path): 
    if os.path.exists(path):
        shutil.rmtree(path)
    os.makedirs(path)
    os.makedirs(path + "/Games")
    shutil.copy(currentPath + "/README_pigaco.md", path + "/README.md")

def copyBinaries(path):
    shutil.copy(currentPath + "/build/pigaco", path + "/pigaco")

path = "dist"

if len(sys.argv) == 2:
    path = sys.argv[1]

setupDist(path)
copyBinaries(path)
