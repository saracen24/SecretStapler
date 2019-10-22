#!/bin/bash

pushd "3rdparty/randombit/botan"

# Configure
python configure.py --with-cmake --without-documentation --without-sphinx --without-pdf --without-rst2man --without-doxygen

pushd "build"
# Configure and build
cmake .. -G "Ninja"
cmake --build . --config Release --parallel 4
popd

popd
