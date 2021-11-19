# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(unfold)

### where to find the libraries
#set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
### where to find the executables
#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# Setup include directory for this project
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/EigenLib)
include_directories(${PROJECT_TXT_DIR}/)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

ROOT_GENERATE_DICTIONARY(myUnfoldlibs_Dict FILEIO.h UNFOLD.h UNCERT.h HVis.h Vis.h  LINKDEF include/my_UnfoldLibs_LinkDef.h)

add_library(myUnfold SHARED src/FILEIO.cc src/UNFOLD.cc src/UNCERT.cc src/Vis.cc src/HVis.cc  myUnfoldlibs_Dict.cxx)

target_link_libraries(myUnfold ${ROOT_LIBRARIES})
