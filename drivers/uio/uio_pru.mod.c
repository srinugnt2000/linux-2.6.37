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
	{ 0xba540b82, "platform_driver_register" },
	{ 0x1b56903, "kmalloc_caches" },
	{ 0x22e246e6, "__uio_register_device" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x9ad0d04a, "davinci_ioremap" },
	{ 0xed60a3be, "dma_alloc_coherent" },
	{ 0xb60848f7, "platform_get_resource" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x12754d6d, "clk_enable" },
	{ 0x42064352, "dev_err" },
	{ 0xad83a8d, "clk_get" },
	{ 0x2e1ca751, "clk_put" },
	{ 0x12e5185c, "dev_set_drvdata" },
	{ 0x7089aaf0, "dma_free_coherent" },
	{ 0xa24d2473, "davinci_iounmap" },
	{ 0x37a0cba, "kfree" },
	{ 0x6d343868, "uio_unregister_device" },
	{ 0x19204fb6, "dev_get_drvdata" },
	{ 0x1f1e12ae, "platform_driver_unregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "428233F95418DED99CF18CE");
