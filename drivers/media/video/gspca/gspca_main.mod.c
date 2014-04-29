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
	{ 0x1b56903, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xf9a482f9, "msleep" },
	{ 0xa90c928a, "param_ops_int" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x12e5185c, "dev_set_drvdata" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xa57afc74, "ktime_get" },
	{ 0xd68117bd, "usb_kill_urb" },
	{ 0x475a0ec5, "__video_register_device" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0x999e8297, "vfree" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x5f754e5a, "memset" },
	{ 0x2700b38a, "mutex_lock_interruptible" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0xea147363, "printk" },
	{ 0x121852a8, "video_unregister_device" },
	{ 0x8f0ae6ca, "usb_set_interface" },
	{ 0x328a05f1, "strncpy" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xfe288a2b, "usb_free_coherent" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x6a61096e, "vm_insert_page" },
	{ 0x5d9f18fb, "module_put" },
	{ 0xc114497, "usb_submit_urb" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x88107062, "video_devdata" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xe4579367, "input_register_device" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0xa6eb3d95, "usb_clear_halt" },
	{ 0x663824ce, "input_free_device" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0xb9e52429, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0x83e15ad6, "input_unregister_device" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0xf15f9a3a, "usb_ifnum_to_if" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x8b19e604, "vmalloc_to_page" },
	{ 0x89ec0888, "usb_alloc_coherent" },
	{ 0x19204fb6, "dev_get_drvdata" },
	{ 0xbc814bed, "usb_free_urb" },
	{ 0xf44c59f9, "video_ioctl2" },
	{ 0x501125d9, "usb_alloc_urb" },
	{ 0xc10c750c, "input_allocate_device" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

