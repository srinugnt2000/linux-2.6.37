cmd_arch/arm/lib/strnlen_user.o := arm-none-linux-gnueabi-gcc -Wp,-MD,arch/arm/lib/.strnlen_user.o.d  -nostdinc -isystem /home/stesalit/arm-2009q1/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.3/include -I/root/kernel-dev/linux-2.6.37/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-davinci/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -include asm/unified.h -msoft-float        -c -o arch/arm/lib/strnlen_user.o arch/arm/lib/strnlen_user.S

deps_arch/arm/lib/strnlen_user.o := \
  arch/arm/lib/strnlen_user.S \
  /root/kernel-dev/linux-2.6.37/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /root/kernel-dev/linux-2.6.37/arch/arm/include/asm/linkage.h \
  /root/kernel-dev/linux-2.6.37/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/smp.h) \
  /root/kernel-dev/linux-2.6.37/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /root/kernel-dev/linux-2.6.37/arch/arm/include/asm/hwcap.h \
  /root/kernel-dev/linux-2.6.37/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \

arch/arm/lib/strnlen_user.o: $(deps_arch/arm/lib/strnlen_user.o)

$(deps_arch/arm/lib/strnlen_user.o):
