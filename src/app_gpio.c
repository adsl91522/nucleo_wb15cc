#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "main.h"

LOG_MODULE_REGISTER(app_gpio, LOG_LEVEL_INF);

static const struct gpio_dt_spec gpio_led_0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec gpio_button_0 = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

static struct gpio_callback gpio_button_cb;

static void gpio_button_cb_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	// LOG_INF("gpio_button_cb_handler");
	gpio_pin_toggle_dt(&gpio_led_0);
}

int gpio_read(gpio_key gpio)
{
	int ret = 0;
	
	switch (gpio)
	{
	case LED0:
		ret = gpio_pin_get_dt(&gpio_led_0);
		break;
	case BUTTON0:
		ret = gpio_pin_get_dt(&gpio_button_0);
		break;
	default:
		break;
	}
	
	return ret;
}

int gpio_set(gpio_key gpio, bool status)
{
	int ret = 0;

	switch (gpio)
	{
	case LED0:
		ret = gpio_pin_set_dt(&gpio_led_0, status);
		break;
	default:
		break;
	}

	return ret;
}

int gpio_init(void)
{
    int ret = 0;
	
	ret = gpio_pin_configure_dt(&gpio_led_0, (GPIO_INPUT | GPIO_OUTPUT));
	if (ret < 0) {
		LOG_ERR("gpio pin configure dt gpio_button_0 error %d", ret);
		return ret;
	}

	ret = gpio_pin_configure_dt(&gpio_button_0, (GPIO_INPUT));
	if (ret < 0) {
		LOG_ERR("gpio pin configure dt gpio_button_0 error %d", ret);
		return ret;
	}

	gpio_set(LED0, 1);

	ret = gpio_pin_interrupt_configure_dt(&gpio_button_0, GPIO_INT_EDGE_RISING);
	if (ret < 0) {
		LOG_ERR("gpio pin interrupt configure dt gpio_button_0 error: %d", ret);
		return ret;
	}
	
	gpio_init_callback(&gpio_button_cb, gpio_button_cb_handler, BIT(gpio_button_0.pin));
    gpio_add_callback(gpio_button_0.port, &gpio_button_cb);

	return ret;
}
