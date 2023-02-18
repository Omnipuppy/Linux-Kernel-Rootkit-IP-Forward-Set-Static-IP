#include <linux/module.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/inet.h>
#include <net/ip.h>
#include <net/inet_common.h>

static char* static_ip = "192.168.1.100"; // Default static IP address

module_param(static_ip, charp, S_IRUGO);

static int __init ip_forwarding_init(void)
{
    struct in_addr addr;

    printk(KERN_INFO "Enabling IP forwarding and setting static IP address to %s...\n", static_ip);
    
    // Enable IP forwarding
    sysctl_ip_forward = 1;
    
    // Parse static IP address from command line argument
    if (in4_pton(static_ip, -1, (u8 *)&addr, '\0', NULL) != 1) {
        printk(KERN_ERR "Invalid static IP address %s\n", static_ip);
        return -EINVAL;
    }

    // Set static IP address
    if (ip_set_addr(&init_net, &inet->conf, &addr, NULL)) {
        printk(KERN_ERR "Failed to set static IP address %s\n", static_ip);
        return -EINVAL;
    }

    return 0;
}

static void __exit ip_forwarding_exit(void)
{
    printk(KERN_INFO "Disabling IP forwarding...\n");
    sysctl_ip_forward = 0; // Disable IP forwarding
}

module_init(ip_forwarding_init);
module_exit(ip_forwarding_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Andrew");
MODULE_DESCRIPTION("Kernel module to enable IP forwarding and set a static IP address");
