#!/bin/bash

# This script is used to setup thirdparty libraries for the project.

git clone --depth 5 git@github.com:microsoft/vcpkg.git thirdparty/vcpkg

cd thirdparty/vcpkg
./bootstrap-vcpkg.sh
./vcpkg install allegro5 loguru