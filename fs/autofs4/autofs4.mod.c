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
	{ 0x17a142df, "__copy_from_user" },
	{ 0x81e38b92, "d_invalidate" },
	{ 0x349cba85, "strchr" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x97255bdf, "strlen" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x67053080, "current_kernel_time" },
	{ 0x1329d4bf, "dput" },
	{ 0x170ec140, "seq_printf" },
	{ 0x353e3fa5, "__get_user_4" },
	{ 0x44e9a829, "match_token" },
	{ 0xfeeb5efc, "dentry_open" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0x85df9b6c, "strsep" },
	{ 0x5592e36e, "have_submounts" },
	{ 0x81a54ac3, "generic_read_dir" },
	{ 0x8155eb46, "mount_nodev" },
	{ 0x86dd7f40, "path_get" },
	{ 0xe66c92bd, "may_umount" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0x94af632e, "complete_all" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x5baaba0, "wait_for_completion" },
	{ 0x4cc19e9f, "dcache_dir_lseek" },
	{ 0xc4d13e4b, "misc_register" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xf8fcb82c, "kern_path" },
	{ 0x5f754e5a, "memset" },
	{ 0x421ce0f4, "kill_litter_super" },
	{ 0x99bfbe39, "get_unused_fd" },
	{ 0x2700b38a, "mutex_lock_interruptible" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0xea147363, "printk" },
	{ 0xbbc8e99a, "d_rehash" },
	{ 0x71c90087, "memcmp" },
	{ 0xe3e4f6d2, "d_alloc_root" },
	{ 0x328a05f1, "strncpy" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0xb9bdbcfb, "noop_llseek" },
	{ 0xdd27fa87, "memchr" },
	{ 0x4e3567f7, "match_int" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x400cc59f, "fput" },
	{ 0x45d1f9d8, "__task_pid_nr_ns" },
	{ 0x7dceceac, "capable" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0xbc10dd97, "__put_user_4" },
	{ 0x1000e51, "schedule" },
	{ 0xfb6af58d, "recalc_sigpending" },
	{ 0x55586ded, "may_umount_tree" },
	{ 0xc27487dd, "__bug" },
	{ 0x3f4547a7, "put_unused_fd" },
	{ 0x95ef853c, "path_put" },
	{ 0x7631e39f, "simple_empty" },
	{ 0x3b59d9f8, "dcache_readdir" },
	{ 0x3254b01b, "register_filesystem" },
	{ 0xb9e52429, "__wake_up" },
	{ 0x96c82cb6, "d_lookup" },
	{ 0xee0d63fd, "init_pid_ns" },
	{ 0x55548b3d, "dcache_dir_open" },
	{ 0xff3e7751, "follow_down" },
	{ 0xe953b21f, "get_next_ino" },
	{ 0x3e5285ac, "iput" },
	{ 0xe1c0635d, "dcache_dir_close" },
	{ 0x9c55cec, "schedule_timeout_interruptible" },
	{ 0x37a0cba, "kfree" },
	{ 0x1a2116f, "follow_up" },
	{ 0x9d669763, "memcpy" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x31c50218, "fget" },
	{ 0x5e9dcb9e, "generic_readlink" },
	{ 0x17637142, "simple_statfs" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0x5b288dc9, "unregister_filesystem" },
	{ 0xe2e8065e, "memdup_user" },
	{ 0x1f4f9326, "new_inode" },
	{ 0xe2225650, "misc_deregister" },
	{ 0x97d93fd2, "d_instantiate" },
	{ 0xe914e41e, "strcpy" },
	{ 0xdcb0349b, "sys_close" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

