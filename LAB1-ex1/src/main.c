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

// Ex1
static const struct gpio_dt_spec led3 =
    GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static void thread_led_blinky(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    if (!output_init(&led3, "LED3"))
    {
        return;
    }

    while (1)
    {
        if (!output_set(&led3, 1, "LED3"))
        {
            return;
        }
        k_msleep(1000);

        if (!output_set(&led3, 0, "LED3"))
        {
            return;
        }
        k_msleep(2000);
    }
}

K_THREAD_DEFINE(thread_led_blinky_id, 1024, thread_led_blinky,
                NULL, NULL, NULL, 7, 0, 0);

int main(void)
{
    return 0;
}