# Taken from https://github.com/shanep/griffin/tree/master/cmake
#
#
# The MIT License (MIT)
# Copyright (c) 2013 Foundation Code
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# GNU sdl2 image 
if(SDL2IMAGE_INCLUDE_DIR AND SDL2IMAGE_LIBRARY)
  set(SDL2IMAGE_FOUND TRUE)
else(SDL2IMAGE_INCLUDE_DIR AND SDL2IMAGE_LIBRARY)

  #mac with port install
  find_path(
    SDL2IMAGE_INCLUDE_DIR
    SDL2/SDL_image.h
    PATHS
    /opt/local/include/
    NO_DEFAULT_PATH)

  find_library(
    SDL2IMAGE_LIBRARY 
    sdl2_image
    /opt/local/lib
    NO_DEFAULT_PATH)


  #linux 
  find_path(
    SDL2IMAGE_INCLUDE_DIR
    SDL2/SDL_image.h)
  find_library(
    SDL2IMAGE_LIBRARY
    SDL2_image)
	
  #windows
  find_path(
    SDL2IMAGE_INCLUDE_DIR
    SDL2/SDL_image.h
    PATHS
    "C:/Program Files/SDL"
    NO_DEFAULT_PATH)

  find_library(
    SDL2IMAGE_LIBRARY 
    sdl2_image
    "C:/Program Files/SDL/lib/x86"
    NO_DEFAULT_PATH)



  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(sdl2image DEFAULT_MSG SDL2IMAGE_INCLUDE_DIR SDL2IMAGE_LIBRARY )
  mark_as_advanced(SDL2IMAGE_INCLUDE_DIR SDL2IMAGE_LIBRARY)
endif(SDL2IMAGE_INCLUDE_DIR AND SDL2IMAGE_LIBRARY)
