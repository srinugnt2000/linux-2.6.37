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
	{ 0x3220236b, "__serio_register_driver" },
	{ 0xea147363, "printk" },
	{ 0x2f67f1b2, "input_event" },
	{ 0x1b56903, "kmalloc_caches" },
	{ 0x663824ce, "input_free_device" },
	{ 0xe4579367, "input_register_device" },
	{ 0xbc05a8f5, "serio_open" },
	{ 0x313341a3, "_set_bit_le" },
	{ 0x9d669763, "memcpy" },
	{ 0x701d0ebd, "snprintf" },
	{ 0xc10c750c, "input_allocate_device" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x83e15ad6, "input_unregister_device" },
	{ 0x12e5185c, "dev_set_drvdata" },
	{ 0xadd7a082, "serio_close" },
	{ 0x19204fb6, "dev_get_drvdata" },
	{ 0x1ca0ae2f, "serio_unregister_driver" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("serio:ty00pr*id*ex*");
