#!/usr/bin/env bash

# Installing compilers
# https://help.ubuntu.com/community/InstallingCompilers
sudo apt-get -y install build-essential

# Installing version control software
sudo apt-get -y install git

# Installing Ceres dependencies
# CMake
sudo apt-get -y install cmake
# google-glog + gflags
sudo apt-get -y install libgoogle-glog-dev
# BLAS & LAPACK
sudo apt-get -y install libatlas-base-dev
# Eigen3
sudo apt-get -y install libeigen3-dev
# SuiteSparse and CXSparse (optional)
# - If you want to build Ceres as a *static* library (the default)
#   you can use the SuiteSparse package in the main Ubuntu package
#   repository:
# sudo apt-get -y  install libsuitesparse-dev
# - However, if you want to build Ceres as a *shared* library, you must
#   add the following PPA:
sudo add-apt-repository ppa:bzindovic/suitesparse-bugfix-1319687
sudo apt-get update
sudo apt-get -y install libsuitesparse-dev

# cloning ceres from src

git clone https://ceres-solver.googlesource.com/ceres-solver

mkdir ceres-bin
cd ceres-bin
cmake ../ceres-solver
make -j3
sudo make install 
