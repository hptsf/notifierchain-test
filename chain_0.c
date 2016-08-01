#include <linux/kernel.h>       /* printk() */
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/fs.h>           /* everything() */

#define INIT_EVENT_CHAIN        0x52U
static RAW_NOTIFIER_HEAD(init_event_chain);

/* define notifier_call_chain */
int call_init_event_notifiers(unsigned long val, void *v)
{
    return raw_notifier_call_chain(&init_event_chain, val, v);
}
EXPORT_SYMBOL(call_init_event_notifiers);

/* define notifier_chain_register func */
int register_init_event_notifier(struct notifier_block *nb)
{
    int err;

    err = raw_notifier_chain_register(&init_event_chain, nb);
    if(err){
        printk(KERN_ERR "register notifier chain failed\n");
        goto out;
    }

out:
    return err;
}
EXPORT_SYMBOL(register_init_event_notifier);

static int __init chain_0_init(void)
{
    printk(KERN_DEBUG "I'm in chain_0 init\n");

    return 0;
}

static void __exit chain_0_exit(void)
{
    printk(KERN_DEBUG "Goodbye to chain_0\n");
}

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("hptsf@163.com");

module_init(chain_0_init);
module_exit(chain_0_exit);
