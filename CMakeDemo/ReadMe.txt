#---------------------------------------------------
# HelloCMake - Demonstrate building C++ with CMake
#   - Non-hierarchal version
#---------------------------------------------------

#---------------------------------------------------
project(HelloCMake)
#---------------------------------------------------
#   CMakeDemo dir
#   -- CMakeLists.txt (this file)
#   -- src dir
#      -- hello_cmake.cpp
#      -- helper.h, helper.cpp
#   -- libs dir
#      -- hello_lib dir
#         -- hello_lib.h, hello_lib.cpp 
#   -- build directory
#      -- Debug directory 
#         -- HelloCMake.exe 
#         -- ...
#      -- HelloCMake.dir directory
#         -- Debug directory 
#            -- hello_cmake.obj 
#            -- hello_lib.obj 
#            -- helper.obj
#            -- ...
#---------------------------------------------------

set(CMake_CXX_STANDARD 20)

#---------------------------------------------------
# build HelloCMake.obj in folder build/HelloCMake.dir/debug
#---------------------------------------------------
add_executable(HelloCMake src/hello_cmake.cpp)
add_executable(HelloCMake src/helper.cpp)

#---------------------------------------------------
# build HelloCMakeLib.lib in folder build/debug
#---------------------------------------------------
add_library(HelloCMakeLib STATIC libs/hello_lib/hello_lib.cpp)

#---------------------------------------------------
# link HelloCMake.obj and HelloCMakeLib.lib to 
# create HelloCMake.exe in folder  build/debug
#---------------------------------------------------
target_link_libraries(HelloCMake HelloCMakeLib)

#---------------------------------------------------
# Build process with CMake version 3.18.2
#---------------------------------------------------
#   1. add source files to project directories 
#   2. add CMakeLists.txt (this file)
#   3. mkdir build                 - this puts intermediate
#   4. cd build                      files in build directory
#   5. cmake ..                    - create cmake config files
#   6. cmake --build . [--config Debug | --config Release]
#   7. "./Debug/HelloCmake.exe"    - runs executable 
#   8. Notes:
#      - you can change any of the source files then: 
#          cmake --build . --config Debug
#          "./Debug/HelloCmake.exe
#      - delete contents of build directory to clean
#          cmake will regenerate
#   9. Note: 
#      - you can substitute Release for Debug 
#        in contents of 8.
#---------------------------------------------------
