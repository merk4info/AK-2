#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#include "worm.h"

MODULE_AUTHOR("Vlod <nopof0201info@gmail.com>");
MODULE_DESCRIPTION("Worm hello");
MODULE_LICENSE("GPL");

LIST_HEAD(placed_list);

static uint counter = 0;

struct time_stat {
    struct list_head list;
    uint i;
    ktime_t start_time;
    ktime_t end_time;
};

void print_worm(int i) {
    struct time_stat *item = kmalloc(sizeof(struct time_stat), GFP_KERNEL);
    if (i == 6) item = NULL;

    item->i = counter++;

    item->start_time = ktime_get();
    pr_info("Hello, worm! %d\n", i);
    item->end_time = ktime_get();

    list_add(&item->list, &placed_list);
}

EXPORT_SYMBOL(print_worm);

static int __init worm_init(void) {
    return 0;
}

static void __exit worm_exit(void) {
    struct time_stat *it, *n;
    list_for_each_entry_safe(it, n, &placed_list, list) {
        pr_debug("Ітерація %d: %lldns\n", it->i, ktime_to_ns(it->end_time) - ktime_to_ns(it->start_time));
        list_del(&it->list);
        kfree(it);
    }
}

module_init(worm_init)
module_exit(worm_exit)
