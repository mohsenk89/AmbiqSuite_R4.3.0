#*******************************************************************************
#
# Simple Makefile to prepare binaries for SBL OTA for Apollo4.
#
#*******************************************************************************

ENCRPTED_SBL0 = ../../../apollo4b_scripts/sbl_updates/SBL_ap4b_v3.0/encrypted_sbl0.bin
SBL_OTA = ../../../apollo4b_scripts/sbl_updates/SBL_ap4b_v3.0/sbl_ota.bin

all: $(ENCRPTED_SBL0) $(SBL_OTA)
	# Apollo4 Cordio
	cp $(ENCRPTED_SBL0) encrypted_sbl0.bin
	cp $(SBL_OTA) sbl_ota.bin
	cat encrypted_sbl0.bin sbl_ota.bin > temp_sbl_apollo4b.bin
	python3 ota_binary_converter.py --appbin temp_sbl_apollo4b.bin -o update_sbl_apollo4b
	@rm -rf temp_sbl_apollo4b.bin encrypted_sbl0.bin sbl_ota.bin

clean:
	rm -rf *.bin
	