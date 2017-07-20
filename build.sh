#!/bin/sh

mkdir build
cd build
. /opt/qt59/bin/qt59-env.sh
qmake ../src/NeuroLab.pro
make
