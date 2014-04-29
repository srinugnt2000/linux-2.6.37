cmd_net/ipv6/ipv6.ko := arm-none-linux-gnueabi-ld -EL -r  -T /root/kernel-dev/linux-2.6.37/scripts/module-common.lds --build-id  -o net/ipv6/ipv6.ko net/ipv6/ipv6.o net/ipv6/ipv6.mod.o
