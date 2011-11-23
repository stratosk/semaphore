#!/bin/bash

export KBUILD_BUILD_VERSION="Semaphore_JVT_1.9.0"

export LOCALVERSION="-I9000XXJVT-CL617736"

make CROSS_COMPILE=/opt/toolchains/android-toolchain-eabi/bin/arm-eabi- ARCH=arm -j4
