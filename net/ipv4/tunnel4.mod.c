#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbdacf18c, "module_layout" },
	{ 0x609f1c7e, "synchronize_net" },
	{ 0x686123a5, "icmp_send" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xf7be0daa, "inet_del_protocol" },
	{ 0x3b1e31a5, "__pskb_pull_tail" },
	{ 0xea147363, "printk" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x7c839892, "inet_add_protocol" },
	{ 0xa2393d95, "kfree_skb" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

