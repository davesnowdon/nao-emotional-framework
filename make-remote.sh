#! /bin/bash
if [ -n "${PC_TOOLCHAIN+1}" ]; then
    echo "Building framework to run remotely (off robot)"
    qibuild configure -c $PC_TOOLCHAIN -DIS_REMOTE=ON
    qibuild make -c $PC_TOOLCHAIN
else
    echo "Please define PC_TOOLCHAIN with the name of the qibuild toolchain to use for builds running off-robot"
    exit 1
fi
