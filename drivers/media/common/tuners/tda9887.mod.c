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
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xea147363, "printk" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0x37a0cba, "kfree" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

