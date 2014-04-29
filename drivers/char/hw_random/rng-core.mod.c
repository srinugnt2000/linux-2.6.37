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
	{ 0x7d20c624, "device_remove_file" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x97255bdf, "strlen" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xc4d13e4b, "misc_register" },
	{ 0xd627480b, "strncat" },
	{ 0x2700b38a, "mutex_lock_interruptible" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0xb9bdbcfb, "noop_llseek" },
	{ 0x42a678f2, "device_create_file" },
	{ 0x9c55cec, "schedule_timeout_interruptible" },
	{ 0x701d0ebd, "snprintf" },
	{ 0xe2225650, "misc_deregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

