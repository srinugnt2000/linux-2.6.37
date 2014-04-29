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
	{ 0xbeb24957, "d_path" },
	{ 0x7d20c624, "device_remove_file" },
	{ 0x1b56903, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xd5b037e1, "kref_put" },
	{ 0x2b688622, "complete_and_exit" },
	{ 0xab455eb0, "up_read" },
	{ 0xd82f797c, "dequeue_signal" },
	{ 0x97255bdf, "strlen" },
	{ 0x12e5185c, "dev_set_drvdata" },
	{ 0x9378905a, "bdev_read_only" },
	{ 0x20000329, "simple_strtoul" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0x9ba6ef37, "filp_close" },
	{ 0x4e830a3e, "strnicmp" },
	{ 0x677bb305, "param_ops_bool" },
	{ 0xa60a76cc, "vfs_fsync" },
	{ 0xdf99f91b, "usb_gadget_unregister_driver" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xc6d533e1, "down_read" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x5baaba0, "wait_for_completion" },
	{ 0xacc1ebd1, "param_ops_charp" },
	{ 0x33dcc088, "vfs_read" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x6f4af182, "device_register" },
	{ 0x11089ac7, "_ctype" },
	{ 0x42064352, "dev_err" },
	{ 0x71c90087, "memcmp" },
	{ 0x23269a13, "strict_strtoul" },
	{ 0xd2267400, "init_uts_ns" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xadb3d81e, "up_write" },
	{ 0xb1b22911, "down_write" },
	{ 0x400cc59f, "fput" },
	{ 0xd79b5a02, "allow_signal" },
	{ 0x42a678f2, "device_create_file" },
	{ 0x92fef852, "_dev_info" },
	{ 0x9f984513, "strrchr" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x1000e51, "schedule" },
	{ 0x35c2ba9e, "refrigerator" },
	{ 0xe3e80d5c, "wake_up_process" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0x5d362048, "usb_gadget_probe_driver" },
	{ 0x83800bfa, "kref_init" },
	{ 0x37a0cba, "kfree" },
	{ 0xd04bc966, "kthread_create" },
	{ 0x9d669763, "memcpy" },
	{ 0xd1329880, "param_array_ops" },
	{ 0x6959fe0d, "send_sig_info" },
	{ 0x9775cdc, "kref_get" },
	{ 0x55ff5e70, "invalidate_mapping_pages" },
	{ 0xf90652d1, "dev_warn" },
	{ 0x529a085e, "device_unregister" },
	{ 0xb742fd7, "simple_strtol" },
	{ 0x60f71cfa, "complete" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x99bb8806, "memmove" },
	{ 0x73b164d, "param_ops_ushort" },
	{ 0xbbf7663c, "dev_set_name" },
	{ 0x13095525, "param_ops_uint" },
	{ 0x19204fb6, "dev_get_drvdata" },
	{ 0xaa94c694, "__init_rwsem" },
	{ 0x2a911ba5, "vfs_write" },
	{ 0xfae879e5, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

