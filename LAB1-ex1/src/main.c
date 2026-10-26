#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define LED3_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led3 =
    GPIO_DT_SPEC_GET(LED3_NODE, gpios);

static void thread_led_blinky(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    if (!gpio_is_ready_dt(&led3))
    {
        printk("LED3 GPIO is not ready\n");
        return;
    }

    if (gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE) < 0)
    {
        printk("Cannot configure LED3\n");
        return;
    }

    while (1)
    {
        gpio_pin_set_dt(&led3, 1); // LED3 sáng
        k_msleep(1000);

        gpio_pin_set_dt(&led3, 0); // LED3 tắt
        k_msleep(2000);
    }
}

K_THREAD_DEFINE(thread_led_blinky_id, 1024,
                thread_led_blinky,
                NULL, NULL, NULL,
                7, 0, 0);

int main(void)
{
    return 0;
}
