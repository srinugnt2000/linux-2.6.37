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
	{ 0x4c66feae, "vfs_readdir" },
	{ 0x97255bdf, "strlen" },
	{ 0x1329d4bf, "dput" },
	{ 0xd3428a10, "dget_locked" },
	{ 0xfeeb5efc, "dentry_open" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xea147363, "printk" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x400cc59f, "fput" },
	{ 0xc27487dd, "__bug" },
	{ 0x9d669763, "memcpy" },
	{ 0x7d0d4321, "lookup_one_len" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

