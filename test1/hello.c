#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include "worm.h"

MODULE_AUTHOR("Vlod <nopof0201info@gmail.com>");
MODULE_DESCRIPTION("World hello");
MODULE_LICENSE("GPL");

static uint iteration_number = 1;

module_param(iteration_number, uint, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(iteration_number, " Кількість повторень");

static int __init hello_init(void) {
    if (iteration_number > 10) {
        pr_emerg("Алярм!\n"); //памілка
        BUG_ON(true);
        return -EINVAL;
    }

    if (iteration_number == 0 || (iteration_number >= 5 && iteration_number <= 10)) //попередження
        pr_warn("Ахтунг! Перевір значення параметра\n");

    for (int i = 0; i < iteration_number; i++) {
        print_worm(i);
    }

    return 0;
}

static void __exit hello_exit(void) {
}

module_init(hello_init)

module_exit(hello_exit)
