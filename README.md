Dependencies:
  ROOT
  Eigen -> static library that is included with the download no action req'd
  GNU make
  CMake

Compile: 
  mkdir build
  cd build
  cmake ../
  make -jN

Usage:
  Add the following line to your rootlogon.C or run the command when you open 
  a ROOT environment 
   gSystem->Load("path/to/RESUC/build/libmyUnfold.so"); 
