#!/usr/bin/env bash

zypper ref
# install mercurial (for eigen version control)
zypper -n in mercurial git 
zypper -n in gcc-c++
zypper -n in libglog0 glog-devel 
# install suitesparse
zypper -n in suitesparse-devel suitesparse-devel-static libsuitesparseconfig-4_4_5
zypper -n in cmake

# Install eigen3 
wget http://bitbucket.org/eigen/eigen/get/3.2.7.tar.bz2
mkdir /usr/include/eigen3
tar xvf 3.2.7.tar.bz2 -C /usr/include/eigen3 --strip-components=1

echo "git clone https://github.com/glotaran/ceres-solver.git"
echo "cd ceres-solver"
echo "mkdir ceres-bin"
echo "cd ceres-bin"
echo "cmake .."
echo "make -j3"
echo "make test"
# Optionally install Ceres, it can also be exported using CMake which
# allows Ceres to be used without requiring installation, see the documentation
# for the EXPORT_BUILD_DIR option for more information.
echo "optional: make install"