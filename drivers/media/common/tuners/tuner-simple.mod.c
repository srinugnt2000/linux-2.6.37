#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbdacf18c, "module_layout" },
	{ 0x1b56903, "kmalloc_caches" },
	{ 0xa90c928a, "param_ops_int" },
	{ 0x9a4b2c88, "i2c_transfer" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0x7d11c268, "jiffies" },
	{ 0x3c83de93, "i2c_clients_command" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xc2821775, "tuner_count" },
	{ 0xea147363, "printk" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0xd1329880, "param_array_ops" },
	{ 0xcb4b189, "tuners" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=tuner-types";

