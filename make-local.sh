#! /bin/bash

LIB_NAME=libnao-emotional-framework.so
INSTALLER_DIR=choreographe/installer/emotional-framework-installer
NATIVE_SUB_DIR=installer/native/lib
NATIVE_DIR=${INSTALLER_DIR}/${NATIVE_SUB_DIR}

if [ -n "${ROBOT_TOOLCHAIN+1}" ]; then
    echo "Building framework to run locally (on robot)"
    qibuild configure -c $ROBOT_TOOLCHAIN -DIS_REMOTE=OFF
    qibuild make -c $ROBOT_TOOLCHAIN
    echo "Copying library to installer application"
    cp -f build-${ROBOT_TOOLCHAIN}/sdk/lib/naoqi/${LIB_NAME}  ${NATIVE_DIR}
else
    echo "Please define ROBOT_TOOLCHAIN with the name of the qibuild toolchain to use for builds running off-robot"
    exit 1
fi
