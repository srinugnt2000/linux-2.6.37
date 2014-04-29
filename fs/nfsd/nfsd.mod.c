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
	{ 0xb8dfc412, "vfs_create" },
	{ 0xbeb24957, "d_path" },
	{ 0xc2f245fe, "auth_domain_put" },
	{ 0x1b56903, "kmalloc_caches" },
	{ 0xd835d981, "set_groups" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x405c1144, "get_seconds" },
	{ 0xf9a482f9, "msleep" },
	{ 0xd5b037e1, "kref_put" },
	{ 0x546a3d30, "sunrpc_cache_update" },
	{ 0xab455eb0, "up_read" },
	{ 0x635e1840, "mem_map" },
	{ 0x8b713bc9, "__mnt_is_readonly" },
	{ 0x8345170c, "lease_get_mtime" },
	{ 0x264ee673, "single_open" },
	{ 0x4c66feae, "vfs_readdir" },
	{ 0xbb7b3b2b, "inode_permission" },
	{ 0x97255bdf, "strlen" },
	{ 0xd0ee38b8, "schedule_timeout_uninterruptible" },
	{ 0xccf3c5ec, "auth_unix_lookup" },
	{ 0xa2f26446, "seq_open" },
	{ 0xf50184d2, "svc_pool_stats_open" },
	{ 0x67e5cb, "vfs_link" },
	{ 0x4724261c, "svc_print_addr" },
	{ 0xe8a35ff6, "seq_escape" },
	{ 0x8d9e6bd3, "single_release" },
	{ 0xf2763e56, "sunrpc_cache_pipe_upcall" },
	{ 0x709cc168, "seq_puts" },
	{ 0x5c4b2132, "vfs_llseek" },
	{ 0x2e4a0e9b, "svc_addsock" },
	{ 0x20000329, "simple_strtoul" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0x43648a67, "touch_atime" },
	{ 0x1329d4bf, "dput" },
	{ 0x12e280e3, "svc_proc_unregister" },
	{ 0x170ec140, "seq_printf" },
	{ 0x612f6be8, "svc_find_xprt" },
	{ 0x2845c5d9, "remove_proc_entry" },
	{ 0xe2fae716, "kmemdup" },
	{ 0xfeeb5efc, "dentry_open" },
	{ 0xb8c0d0d5, "nlmsvc_ops" },
	{ 0xcbddd3c7, "vfs_mknod" },
	{ 0x800df1d7, "groups_free" },
	{ 0x71fa908a, "cache_flush" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xa60a76cc, "vfs_fsync" },
	{ 0xf213322f, "mount_single" },
	{ 0xbdc193e1, "svc_seq_show" },
	{ 0x2c6fd8bd, "vfs_symlink" },
	{ 0x86dd7f40, "path_get" },
	{ 0x5157173c, "cache_register" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x2f81b816, "seq_read" },
	{ 0x6a369090, "override_creds" },
	{ 0xb3a307c6, "si_meminfo" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0x151dd8b8, "mnt_drop_write" },
	{ 0x7d11c268, "jiffies" },
	{ 0x360d4790, "svc_set_client" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xc6d533e1, "down_read" },
	{ 0x46c4b962, "mutex_lock_killable" },
	{ 0x1779da86, "vfs_rmdir" },
	{ 0x80724750, "unlock_rename" },
	{ 0x89ebfb76, "splice_direct_to_actor" },
	{ 0x347a4095, "svc_xprt_names" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xcf0ab34b, "cache_check" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x25e1d6ec, "auth_unix_add_addr" },
	{ 0xf8fcb82c, "kern_path" },
	{ 0xc72ca943, "vfs_readv" },
	{ 0x5f754e5a, "memset" },
	{ 0x2d53e64e, "proc_mkdir" },
	{ 0x421ce0f4, "kill_litter_super" },
	{ 0x73c3b0b9, "default_llseek" },
	{ 0x6eea229d, "svcauth_unix_purge" },
	{ 0xb07abe2, "unshare_fs_struct" },
	{ 0x11089ac7, "_ctype" },
	{ 0x5c2f7651, "svc_destroy" },
	{ 0x2f6e3674, "svc_sock_names" },
	{ 0xea147363, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0x2fec006e, "sunrpc_cache_lookup" },
	{ 0x71c90087, "memcmp" },
	{ 0xca1983a8, "simple_transaction_read" },
	{ 0xb03c074f, "auth_unix_forget_old" },
	{ 0x328a05f1, "strncpy" },
	{ 0xb3c82ba9, "seq_putc" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x2891ddb2, "lock_rename" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0x3a349307, "svc_create_pooled" },
	{ 0xe97f4ce5, "qword_get" },
	{ 0xc8e96dea, "qword_addhex" },
	{ 0xae6db6a9, "__splice_from_pipe" },
	{ 0xa80b4ee3, "unix_domain_find" },
	{ 0x330ba8eb, "svc_process" },
	{ 0xb32b83fd, "svc_set_num_threads" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xa5de92e0, "exportfs_encode_fh" },
	{ 0xadb3d81e, "up_write" },
	{ 0x77e2eb18, "cache_unregister" },
	{ 0x958d7c0a, "init_net" },
	{ 0xb1b22911, "down_write" },
	{ 0x400cc59f, "fput" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x21fd9643, "prepare_creds" },
	{ 0xd79b5a02, "allow_signal" },
	{ 0xedcf6be4, "qword_add" },
	{ 0xcf1d002f, "flush_signals" },
	{ 0xc9e15a80, "__fsnotify_parent" },
	{ 0x427afeed, "svc_xprt_put" },
	{ 0xcc3f17b9, "simple_transaction_release" },
	{ 0xcb922942, "svc_create_xprt" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0xbf9d1b96, "nfsd_debug" },
	{ 0x7f8236d1, "mnt_want_write" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x619ca8a, "getboottime" },
	{ 0xb49185c8, "exportfs_decode_fh" },
	{ 0x1a3b9319, "cache_purge" },
	{ 0x97c9d1af, "vfs_statfs" },
	{ 0xc27487dd, "__bug" },
	{ 0x510bb3d0, "__module_put_and_exit" },
	{ 0x254cb4d4, "svc_proc_register" },
	{ 0x3db57b3e, "vfs_mkdir" },
	{ 0xdf2e6cb9, "__put_cred" },
	{ 0xccedfdb4, "inode_change_ok" },
	{ 0x95ef853c, "path_put" },
	{ 0x50cb481c, "simple_transaction_set" },
	{ 0x230419bc, "sync_inode_metadata" },
	{ 0x73ecb9cb, "vfs_writev" },
	{ 0xa8878642, "vfs_unlink" },
	{ 0xe5919cb1, "xdr_encode_opaque" },
	{ 0x3254b01b, "register_filesystem" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x4aaab2b1, "groups_alloc" },
	{ 0xccc2372e, "rpc_pton" },
	{ 0x1d2e87c6, "do_gettimeofday" },
	{ 0x2f4d8be7, "proc_create_data" },
	{ 0xff3e7751, "follow_down" },
	{ 0xbee41702, "seq_lseek" },
	{ 0x547cef1f, "svc_exit_thread" },
	{ 0x4b874cba, "svc_max_payload" },
	{ 0x37a0cba, "kfree" },
	{ 0x56128f4, "simple_transaction_get" },
	{ 0x1a2116f, "follow_up" },
	{ 0x9d669763, "memcpy" },
	{ 0x13ae820a, "fsnotify" },
	{ 0x58460275, "svc_reserve" },
	{ 0x9775cdc, "kref_get" },
	{ 0x343413a6, "simple_fill_super" },
	{ 0x3a327821, "abort_creds" },
	{ 0xf6933c48, "lockd_up" },
	{ 0x6b30fceb, "put_page" },
	{ 0x374ed073, "scnprintf" },
	{ 0xa7b91a7b, "lockd_down" },
	{ 0x5b288dc9, "unregister_filesystem" },
	{ 0xe51032a9, "nlmsvc_unlock_all_by_sb" },
	{ 0xb742fd7, "simple_strtol" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x87b12423, "seq_release" },
	{ 0xc8b0d58a, "svc_recv" },
	{ 0x99bb8806, "memmove" },
	{ 0xe307d0db, "__break_lease" },
	{ 0x94a76cab, "auth_domain_find" },
	{ 0x7d0d4321, "lookup_one_len" },
	{ 0x51e6a4a2, "vfs_rename" },
	{ 0x5c6a03ef, "lock_may_write" },
	{ 0xced97e1, "vfs_getattr" },
	{ 0xfcdfea26, "lock_may_read" },
	{ 0x2919b156, "xdr_decode_string_inplace" },
	{ 0x66b2a859, "nr_free_buffer_pages" },
	{ 0x9c152440, "notify_change" },
	{ 0x50b3eb28, "svc_close_xprt" },
	{ 0x2a2283b, "revert_creds" },
	{ 0xe3bf0f92, "get_write_access" },
	{ 0xb8493909, "vfs_fsync_range" },
	{ 0x911b1a30, "seq_path" },
	{ 0x1a618932, "nlmsvc_unlock_all_by_ip" },
	{ 0xe914e41e, "strcpy" },
	{ 0xdd465922, "locks_mandatory_area" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=exportfs";
