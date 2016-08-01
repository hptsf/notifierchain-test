#include <linux/kernel.h>       /* printk() */
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/fs.h>           /* everything() */

extern int register_init_event_notifier(struct notifier_block *nb);
#define INIT_EVENT_CHAIN        0x52U

/* realize the notifier_call func */
int event_callback(struct notifier_block *nb, unsigned long event, void *v)
{
    switch(event){
    case INIT_EVENT_CHAIN:
        if(NULL == v)
            printk(KERN_DEBUG "Get a chain event\n");
        else
            printk(KERN_DEBUG "Get a chain event[%s]\n", (char *)v);
        break;

    default:
        break;
     }

    return NOTIFY_DONE;
}

/* define a notifier_block */
static struct notifier_block init_event_notifier = {
    .notifier_call = event_callback,
};

static int __init chain_1_init(void)
{
    printk(KERN_DEBUG "I'm in chain_1 init\n");
    register_init_event_notifier(&init_event_notifier);
    return 0;
}

static void __exit chain_1_exit(void)
{
    printk(KERN_DEBUG "Goodbye to clain_1\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hptsf@163.com");

module_init(chain_1_init);
module_exit(chain_1_exit);
