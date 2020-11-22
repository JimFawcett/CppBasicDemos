#---------------------------------------------------
# HelloCMakeLib - Demonstrate building C++ Library
#---------------------------------------------------

project(HelloCMakeLib)
set(CMake_CXX_STANDARD 20)

#---------------------------------------------------
# build HelloCMakeLib.lib in folder build/debug
#---------------------------------------------------
add_library(HelloCMakeLib STATIC hello_lib.cpp)

