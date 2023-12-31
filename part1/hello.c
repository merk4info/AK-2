/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Vlod <nopof0201info@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint iteration_number = 1;

module_param(iteration_number, uint, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(iteration_number, " Кількість повторень");

LIST_HEAD(placed_list);
struct time_stat {
    struct list_head list;
    uint i;
    ktime_t time;
};

static int __init hello_init(void) {
    if (iteration_number > 10) {
        printk(KERN_ERR "Алярм!"); //памілка
        return -EINVAL;
    }

    if (iteration_number == 0 || (iteration_number >= 5 && iteration_number <= 10)) //попередження
        printk(KERN_WARNING "Ахтунг! Перевір значення параметра\n");

    for (int i = 0; i < iteration_number; i++) {
        struct time_stat *item = kmalloc(sizeof(struct time_stat), GFP_KERNEL);
        item->i = i;
        item->time = ktime_get();
        list_add(&item->list, &placed_list);

        printk(KERN_INFO "Hello, world!\n");
    }

    return 0;
}

static void __exit hello_exit(void) {
    struct time_stat *it, *n;
    list_for_each_entry_safe(it, n, &placed_list, list) {
        printk(KERN_INFO "Ітерація %d: %lld\n", it->i, it->time);
        list_del(&it->list);
        kfree(it);
    }
}

module_init(hello_init)
module_exit(hello_exit)
