#!/bin/sh

echo 'Setting up environment for GCC + no OS...'
export CROSS_COMPILE=arm-none-eabi-
export ARCH=arm
export ARM_CPU=cortex-m4
export COMPILER_TYPE=gcc
export TEE_OS=no_os
export ARM_VENDOR=ambiq
export AMBIQ_ROOT=$(realpath ../..)

echo 'Setup complete.'
echo ''
echo 'To build MbedTLS libraries, run the following:'
echo ''
echo './prepare_mbedtls.sh clone'
echo './prepare_mbedtls.sh lib'
echo ''
echo 'To rebuild PAL:'
echo ' make -C host/src ARM_CPU=$ARM_CPU TEE_OS=$TEE_OS'
