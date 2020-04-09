#!/bin/bash

cmake \
    -C ../host-configs/llnl-toss3-gcc8.1.cmake \
    -DENABLE_APOLLO=ON \
    -DAPOLLO_DIR=$HOME/src/apollo/install \
    ..
