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
	{ 0xcfd7b0a8, "xfrm_register_mode" },
	{ 0x99bb8806, "memmove" },
	{ 0xc27487dd, "__bug" },
	{ 0x7929054c, "xfrm_unregister_mode" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

