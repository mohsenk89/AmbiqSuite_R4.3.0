Steps of generating AMOTA file:

1. Compile the ble_freertos_amota project to generate the new binary that you want to upgrade for the Apollo4b.

2. Go to SDK/tools/apollo4_amota/scripts folder, modify the items of TOOL_CHAIN and APOLLO4_BOARD in Makefile for your own development environment.
The default settings are:
TOOL_CHAIN?=gcc
APOLLO4_BOARD = apollo4b_blue_evb

3. Execute gcc make under the path SDK/tools/apollo4_amota/scripts, then you will get the final update_binary_apollo4_blue.bin with OTA header for the AMOTA.