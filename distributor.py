import shutil
import os
import sys

currentPath = os.path.dirname(os.path.realpath(__file__))

def copytree(src, dest, ignore=None):
    if os.path.isdir(src):
        if not os.path.isdir(dest):
            os.makedirs(dest)
        files = os.listdir(src)
        if ignore is not None:
            ignored = ignore(src, files)
        else:
            ignored = set()
        for f in files:
            if f not in ignored:
                copytree(os.path.join(src, f), 
                                    os.path.join(dest, f), 
                                    ignore)
    else:
        shutil.copyfile(src, dest)

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
    copytree(currentPath + "/Data/Docroot/", path + "/")

path = "dist"

if len(sys.argv) == 2:
    path = sys.argv[1]

setupDist(path)
copyBinaries(path)
copyData(path)

print("Distribution Created!")
