#!/bin/sh
protoc --cpp_out=../ *.proto

# criando um biblioteca statica para ser usada nos outros sistemas
cd ..
qmake-qt4
make clean
make
