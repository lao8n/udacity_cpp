// in admin command prompt
mklink make "C:\MinGW\bin\mingw32-make.exe"

// had to build these steps
https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md
C:\src\vcpkg\vckpg.exe

C:\src\vcpkg>.\vcpkg.exe search expat
cd C:\Users\lao8n\Documents\P0267_RefImpl\Debug
del CMakeCache.txt
rmdir /s /q CMakeFiles

had to edit CMakeLists where rather than libiconv C:\Users\lao8n\Documents\P0267_RefImpl\P0267_RefImpl\P0267_RefImpl\cairo\win32
find_library(ICONV_LIB Iconv)
libcharset -> charset
expat -> libexpat
C:\Users\lao8n\Documents\P0267_RefImpl\P0267_RefImpl\Tests
	find_library(PNG_LIB_DEBUG libpng16d)
	find_library(PNG_LIB_RELEASE libpng16)

cmake .. -G "Visual Studio 17 2022" "-DCMAKE_TOOLCHAIN_FILE=C:\src\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" 
cmake .. -G "MinGW Makefiles" "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_TOOLCHAIN_FILE=C:\src\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows"

removed from cmakelists

if( NOT DEFINED IO2D_WITHOUT_TESTS )
	enable_testing()
	add_subdirectory(P0267_RefImpl/Tests)
endif()

also added
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)

set CMAKE_PREFIX_PATH=C:\Users\lao8n\Documents\P0267_RefImpl\build\P0267_RefImpl\P0267_RefImpl\CMakeFiles\Export\31736c4fd947c5cd63018067dcd32abd

gives the following error 
C:\Users\lao8n\OneDrive\Documents\udacity_cpp\cpp_foundations\open_street_map\build>cmake ..                                                                                        
-- Selecting Windows SDK version 10.0.22000.0 to target Windows 10.0.22621.
CMake Error at C:/Users/lao8n/Documents/P0267_RefImpl/build/P0267_RefImpl/P0267_RefImpl/CMakeFiles/Export/31736c4fd947c5cd63018067dcd32abd/io2dConfig.cmake:111 (message):
  The imported target "io2d::io2d_core" references the file

     "C:/Users/lao8n/Documents/P0267_RefImpl/build/P0267_RefImpl/P0267_RefImpl/lib/io2d_core.lib"

  but this file does not exist.  Possible reasons include:

  * The file was deleted, renamed, or moved to another location.

  * An install or uninstall procedure did not complete successfully.

  * The installation package was faulty and contained

     "C:/Users/lao8n/Documents/P0267_RefImpl/build/P0267_RefImpl/P0267_RefImpl/CMakeFiles/Export/31736c4fd947c5cd63018067dcd32abd/io2dConfig.cmake"

  but not all the files it references.

Call Stack (most recent call first):
  CMakeLists.txt:15 (find_package)

To build and run
mkdir build && cd build
cmake ..
make

./OSM_A_star_search
./test
