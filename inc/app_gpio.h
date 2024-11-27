#ifndef APP_GPIO_H
#define APP_GPIO_H

typedef enum {
    LED0,
    BUTTON0
} gpio_key;

int gpio_read(gpio_key gpio);
int gpio_set(gpio_key gpio, bool status);
int gpio_init(void);

#endif