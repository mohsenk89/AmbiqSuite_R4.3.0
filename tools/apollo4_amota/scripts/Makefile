#*******************************************************************************
#
# Simple Makefile to prepare binaries for AMOTA for Apollo4.
#
#*******************************************************************************

TOOL_CHAIN?=gcc

APOLLO4_BOARD = apollo4b_blue_evb
UPDATEBIN_APOLLO4_BLUE =../../../boards/$(APOLLO4_BOARD)/examples/ble/ble_freertos_amota/$(TOOL_CHAIN)/bin/ble_freertos_amota.bin
APPBIN_APOLLO4_BLUE =../../../boards/$(APOLLO4_BOARD)/examples/ble/ble_freertos_amota/$(TOOL_CHAIN)/bin/ble_freertos_amota.bin

all: $(APPBIN_APOLLO4_BLUE) $(UPDATEBIN_APOLLO4_BLUE) $(UPDATEBIN_APOLLO4_BLUE_ETHERMIND) $(APPBIN_APOLLO4_BLUE_ETHERMIND)
	# Apollo4 Cordio
	cp $(APPBIN_APOLLO4_BLUE) starter_binary_apollo4_blue.bin
	cp -r ../../apollo4b_scripts/oem_tools_pkg* oem_tools_pkg
	cp -r ../../apollo4b_scripts/arm_utils* arm_utils
	cp ../../apollo4b_scripts/am_defines.py am_defines.py
	cp ../../apollo4b_scripts/apollo4b_keys.py apollo4b_keys.py
	cp ../../apollo4b_scripts/create_cust_image_blob.py create_cust_image_blob.py
	cp ../../apollo4b_scripts/key_table.py key_table.py
	cp ../../apollo4b_scripts/sample/keys.ini keys.ini
	python create_cust_image_blob.py -c firmware.ini
	python ota_binary_converter.py --appbin temp_binary_apollo4_blue.bin -o update_binary_apollo4_blue
	@rm -rf temp_binary_apollo4_blue.bin
	@rm -rf key_table.py
	@rm -rf keys.ini
	@rm -rf am_defines.py
	@rm -rf create_cust_image_blob.py
	@rm -rf oem_tools_pkg
	@rm -rf arm_utils
	@rm -rf apollo4b_keys.py

$(APPBIN_APOLLO4_BLUE):
	$(MAKE) -C ../../../boards/$(APOLLO4_BOARD)/examples/ble/ble_freertos_amota/$(TOOL_CHAIN)/ $(MAKECMDGOALS)

clean:
	rm -rf *.bin
	rm -rf $(APPBIN_APOLLO4_BLUE)
	