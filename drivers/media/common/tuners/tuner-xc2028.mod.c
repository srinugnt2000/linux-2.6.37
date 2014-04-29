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
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xf9a482f9, "msleep" },
	{ 0xa90c928a, "param_ops_int" },
	{ 0x9a4b2c88, "i2c_transfer" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x206d8b6, "param_ops_string" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0xea147363, "printk" },
	{ 0xaafdc258, "strcasecmp" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x9f46ced8, "__sw_hweight64" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0x8694291b, "request_firmware" },
	{ 0xdccbd2f5, "release_firmware" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

