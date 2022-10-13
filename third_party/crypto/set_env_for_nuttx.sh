#!/bin/sh

echo 'Setting up environment for GCC + Nuttx...'
export CROSS_COMPILE=arm-none-eabi-
export ARCH=arm
export ARM_CPU=cortex-m4
export COMPILER_TYPE=gcc
export TEE_OS=nuttx
export ARM_VENDOR=ambiq
export AMBIQ_ROOT=$(realpath ../ambiqsuite)

# Set this variable to the location of the root of your nuttx file tree.
export NUTTX_ROOT=/home/username/repos/nuttx/
echo ''
echo '******** WARNING ********'
echo 'You will need to fix the NUTTX_ROOT variable in'
echo 'set_env_for_nuttx.sh to rebuild crypto libraries.'
echo ''


echo 'Setup complete.'
echo ''
echo 'To build MbedTLS libraries, run the following:'
echo ''
echo './prepare_mbedtls.sh clone'
echo './prepare_mbedtls.sh lib'
echo ''
echo 'To rebuild PAL:'
echo ' make -C host/src ARM_CPU=$ARM_CPU TEE_OS=$TEE_OS'
