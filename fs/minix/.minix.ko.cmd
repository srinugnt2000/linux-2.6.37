cmd_fs/minix/minix.ko := arm-none-linux-gnueabi-ld -EL -r  -T /root/kernel-dev/linux-2.6.37/scripts/module-common.lds --build-id  -o fs/minix/minix.ko fs/minix/minix.o fs/minix/minix.mod.o
