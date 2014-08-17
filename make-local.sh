#! /bin/bash
if [ -n "${ROBOT_TOOLCHAIN+1}" ]; then
    echo "Building framework to run locally (on robot)"
    qibuild configure -c $ROBOT_TOOLCHAIN -DIS_REMOTE=OFF
    qibuild make -c $ROBOT_TOOLCHAIN
else
    echo "Please define ROBOT_TOOLCHAIN with the name of the qibuild toolchain to use for builds running off-robot"
    exit 1
fi
