##Nunf

NUnf is a cpp library for dealing with neutron spectrum unfolding. It allows creation of an Unfolding object which consists of a response matrix, 

##Installation
Dependencies:
  ROOT
  Eigen -> static library that is included with the download no action req'd
  GNU make
  CMake

Compile: 
 ```bash
  mkdir build
  cd build
  cmake ../
  make -jN
```

Usage:
  Add the following line to your rootlogon.C or run the command when you open 
  a ROOT environment 
```bash
   gSystem->Load("path/to/RESUC/build/libmyUnfold.so"); 
```



##Documentation
Todo: publish on a website
Until then: install doxygen https://www.doxygen.nl/manual/install.html
Then: run doxygen Doxyfile
