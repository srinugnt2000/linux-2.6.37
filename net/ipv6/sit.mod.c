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
	{ 0xdb1f7158, "xfrm4_tunnel_register" },
	{ 0xc3462201, "register_pernet_device" },
	{ 0x47bed1f5, "netif_rx" },
	{ 0xdb11f96d, "ipv6_chk_prefix" },
	{ 0x6d3cf258, "__secpath_destroy" },
	{ 0x3b1e31a5, "__pskb_pull_tail" },
	{ 0x81b77123, "sock_wfree" },
	{ 0x39aac8a0, "ip_local_out" },
	{ 0xd307d871, "__ip_select_ident" },
	{ 0xa2393d95, "kfree_skb" },
	{ 0x2a18c74, "nf_conntrack_destroy" },
	{ 0x1ef71ec2, "skb_push" },
	{ 0xef3496a9, "consume_skb" },
	{ 0xf66d4658, "skb_realloc_headroom" },
	{ 0xc6c8866d, "icmpv6_send" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0xd542439, "__ipv6_addr_type" },
	{ 0x1b56903, "kmalloc_caches" },
	{ 0x6868adf2, "kmem_cache_alloc" },
	{ 0xbc10dd97, "__put_user_4" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x8024dbb, "netdev_state_change" },
	{ 0x609f1c7e, "synchronize_net" },
	{ 0x7dceceac, "capable" },
	{ 0x17a142df, "__copy_from_user" },
	{ 0x1251d30f, "call_rcu" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0xea147363, "printk" },
	{ 0x85670f1d, "rtnl_is_locked" },
	{ 0x37a0cba, "kfree" },
	{ 0x8523f2c4, "register_netdevice" },
	{ 0x9d669763, "memcpy" },
	{ 0x9d87a52c, "dev_alloc_name" },
	{ 0x349cba85, "strchr" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0xea4c8bb4, "__dev_get_by_index" },
	{ 0x66387ba5, "dst_release" },
	{ 0x20634d9c, "ip_route_output_key" },
	{ 0x5f754e5a, "memset" },
	{ 0x9a47d5a, "register_netdev" },
	{ 0x50c89f23, "__alloc_percpu" },
	{ 0xe914e41e, "strcpy" },
	{ 0xf93e6abc, "alloc_netdev_mq" },
	{ 0xf1c7b94d, "free_netdev" },
	{ 0xc9ec4e21, "free_percpu" },
	{ 0x7d11c268, "jiffies" },
	{ 0x958d7c0a, "init_net" },
	{ 0x6e720ff2, "rtnl_unlock" },
	{ 0x9fdecc31, "unregister_netdevice_many" },
	{ 0xc7a4fbed, "rtnl_lock" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0xc27487dd, "__bug" },
	{ 0x8d522714, "__rcu_read_lock" },
	{ 0x9c7a2d3f, "unregister_netdevice_queue" },
	{ 0x60a13e90, "rcu_barrier" },
	{ 0xa4279b9f, "unregister_pernet_device" },
	{ 0x1357e85c, "xfrm4_tunnel_deregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=tunnel4,ipv6";

