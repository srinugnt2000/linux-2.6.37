cmd_lib/crc-ccitt.ko := arm-none-linux-gnueabi-ld -EL -r  -T /root/kernel-dev/linux-2.6.37/scripts/module-common.lds --build-id  -o lib/crc-ccitt.ko lib/crc-ccitt.o lib/crc-ccitt.mod.o
