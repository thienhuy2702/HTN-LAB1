#include <stdbool.h>
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

static bool output_init(const struct gpio_dt_spec *gpio, const char *name)
{
    if (!gpio_is_ready_dt(gpio))
    {
        printk("%s GPIO is not ready\n", name);
        return false;
    }

    int ret = gpio_pin_configure_dt(gpio, GPIO_OUTPUT_INACTIVE);
    if (ret < 0)
    {
        printk("Cannot configure %s: %d\n", name, ret);
        return false;
    }

    return true;
}

static bool output_set(const struct gpio_dt_spec *gpio, int value,
                       const char *name)
{
    int ret = gpio_pin_set_dt(gpio, value);
    if (ret < 0)
    {
        printk("Cannot set %s: %d\n", name, ret);
        return false;
    }

    return true;
}