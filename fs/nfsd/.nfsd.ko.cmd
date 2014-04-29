cmd_fs/nfsd/nfsd.ko := arm-none-linux-gnueabi-ld -EL -r  -T /root/kernel-dev/linux-2.6.37/scripts/module-common.lds --build-id  -o fs/nfsd/nfsd.ko fs/nfsd/nfsd.o fs/nfsd/nfsd.mod.o
