#include <linux/kernel.h>       /* printk() */
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/fs.h>           /* everything() */

extern int call_init_event_notifiers(unsigned long val, void *v);
#define INIT_EVENT_CHAIN        0x52U

static int __init chain_2_init(void)
{
    printk(KERN_DEBUG "I'm in chain_2 init\n");
#if 0
    call_init_event_notifiers(INIT_EVENT_CHAIN, NULL);
#else
    call_init_event_notifiers(INIT_EVENT_CHAIN, "For test");
#endif

    return 0;
}

static void __exit chain_2_exit(void)
{
    printk(KERN_DEBUG "Goodbye to chain_2\n");
}

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("hptsf@163.com");

module_init(chain_2_init);
module_exit(chain_2_exit);
