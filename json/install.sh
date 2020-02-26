#!/bin/sh

# install json-c
cd
git clone https://github.com/json-c/json-c
cd json-c
cd autogen.sh
./configure
make
make install
