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
	{ 0x1b56903, "kmalloc_caches" },
	{ 0xc5247913, "alloc_disk" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x17a142df, "__copy_from_user" },
	{ 0x69357097, "blk_cleanup_queue" },
	{ 0x635e1840, "mem_map" },
	{ 0x6f795d6c, "bio_alloc" },
	{ 0xa90c928a, "param_ops_int" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x97255bdf, "strlen" },
	{ 0x3a9b6fb9, "blk_unregister_region" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x45410234, "kobject_uevent" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xa60a76cc, "vfs_fsync" },
	{ 0x49299c5, "blk_queue_flush" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xa54d80d7, "sysfs_remove_group" },
	{ 0xf3bef2f0, "__alloc_pages_nodemask" },
	{ 0x89ebfb76, "splice_direct_to_actor" },
	{ 0x1501d5d3, "invalidate_bdev" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0x5baaba0, "wait_for_completion" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xbe3fbbb2, "set_device_ro" },
	{ 0x5f754e5a, "memset" },
	{ 0xe2a4a73a, "blk_alloc_queue" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0xea147363, "printk" },
	{ 0x5b2effc, "kthread_stop" },
	{ 0x7bc615d2, "sysfs_create_group" },
	{ 0xcab9b437, "del_gendisk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x64be0faf, "blk_register_region" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0xcfb5c23d, "file_update_time" },
	{ 0x71a50dbc, "register_blkdev" },
	{ 0xae6db6a9, "__splice_from_pipe" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x400cc59f, "fput" },
	{ 0x562fbc03, "get_disk" },
	{ 0x40e8fbea, "contig_page_data" },
	{ 0x4d4a7988, "bio_endio" },
	{ 0xd90804d4, "bio_put" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0x5d9f18fb, "module_put" },
	{ 0x7dceceac, "capable" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0x4a7f774a, "__free_pages" },
	{ 0x7659e11e, "bd_set_size" },
	{ 0x2ca1aaa5, "pagecache_write_end" },
	{ 0xb79e1ce2, "blk_queue_make_request" },
	{ 0x1000e51, "schedule" },
	{ 0xadcc7e21, "put_disk" },
	{ 0xc27487dd, "__bug" },
	{ 0xe3e80d5c, "wake_up_process" },
	{ 0xb9e52429, "__wake_up" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0x37a0cba, "kfree" },
	{ 0xd04bc966, "kthread_create" },
	{ 0x9d669763, "memcpy" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x7265b653, "add_disk" },
	{ 0x45c06524, "set_user_nice" },
	{ 0x31c50218, "fget" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0xd5987848, "ioctl_by_bdev" },
	{ 0x60f71cfa, "complete" },
	{ 0x99bb8806, "memmove" },
	{ 0xba732d9b, "set_blocksize" },
	{ 0xced97e1, "vfs_getattr" },
	{ 0xbf6e68e7, "pagecache_write_begin" },
	{ 0x1057e3fc, "flush_dcache_page" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

