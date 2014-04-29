cmd_net/ipv6/sit.ko := arm-none-linux-gnueabi-ld -EL -r  -T /root/kernel-dev/linux-2.6.37/scripts/module-common.lds --build-id  -o net/ipv6/sit.ko net/ipv6/sit.o net/ipv6/sit.mod.o
