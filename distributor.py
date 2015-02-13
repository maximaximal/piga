import shutil
import os
import sys

currentPath = os.path.dirname(os.path.realpath(__file__))

def copytree(src, dst, symlinks=False, ignore=None):
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)

def setupDist(path): 
    if not os.path.exists(path):
        os.makedirs(path)
        if not os.path.exists(path + "/Games"):
            os.makedirs(path + "/Games")
            
    shutil.copy(currentPath + "/README_pigaco.md", path + "/README.md")

def copyBinaries(path):
    shutil.copy(currentPath + "/build/pigaco", path + "/pigaco")
    
def copyData(path):
    copytree(currentPath + "/Data", path + "/Data/")

path = "dist"

if len(sys.argv) == 2:
    path = sys.argv[1]

setupDist(path)
copyBinaries(path)
copyData(path)

print("Distribution Created!")
