#!/bin/bash

pkill -9 root;
cd ../build;
make -j4;
cd ../scripts;
root Odessa_SIRT_FakeData.C; 
