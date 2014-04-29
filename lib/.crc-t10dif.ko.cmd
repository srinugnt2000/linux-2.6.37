cmd_lib/crc-t10dif.ko := arm-none-linux-gnueabi-ld -EL -r  -T /root/kernel-dev/linux-2.6.37/scripts/module-common.lds --build-id  -o lib/crc-t10dif.ko lib/crc-t10dif.o lib/crc-t10dif.mod.o
