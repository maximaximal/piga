import shutil
import os
import sys

currentPath = os.path.dirname(os.path.realpath(__file__))

def setupDist(path): 
    if not os.path.exists(path):
        os.makedirs(path)
        if not os.path.exists(path + "/Games"):
            os.makedirs(path + "/Games")
        if not os.path.exists(path + "/Data"):
            os.makedirs(path + "/Data")
            os.makedirs(path + "/Data/Fonts")

    shutil.copy(currentPath + "/README_pigaco.md", path + "/README.md")

def copyBinaries(path):
    shutil.copy(currentPath + "/build/pigaco", path + "/pigaco")

path = "dist"

if len(sys.argv) == 2:
    path = sys.argv[1]

setupDist(path)
copyBinaries(path)

print("Distribution Created!")
