#!/bin/bash

#INFORMAÇÃO IMPORTA -> usar Ubuntu 12.04 lTS

#INFORMAÇÃO IMPORTA -> instalar o QtSDK 4

echo "Instalando libraries default"
sudo apt-get update
sudo apt-get install build-essential cmake libqt4-dev libgl1-mesa-dev libglu1-mesa-dev libprotobuf-dev libode-dev protobuf-compiler libgtkmm-2.4-dev freeglut3 freeglut3-dev binutils-gold libavformat-dev x264 v4l-utils ffmpeg libcgal-dev libboost-all-dev

#Serguir o seguinte tutorial para instalar a opencv a partir do código fonte http://opencvlearn.blogspot.com.br/2012/04/install-opencv-24-ubuntu-1110.html
echo "Instalando opencv"
sudo apt-get install python-opencv opencv-doc libcv-dev libcvaux-dev libhighgui-dev
echo "Finalizando..."

echo "Instalando Vartypes 0.7"
tar xfz vartypes-0.7.tar.gz
cd vartypes-0.7
mkdir build
cd build
cmake ..
make 
sudo make install
cd ..
cd ..
echo "Finalizando..."

echo "Instalando Box2D"
tar xfz box2d.tar.gz
cd box2d
mkdir build
cd build
cmake ..
make 
sudo make install
cd ..
cd ..
echo "Finalizando..."

echo "Instalando RefereeBox"
tar xfz ssl-refbox-robocup-2013.tar.gz
cd ssl-refbox-robocup-2013
make 
cd ..
echo "Finalizando..."
