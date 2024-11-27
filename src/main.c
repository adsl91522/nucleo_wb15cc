#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "main.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	LOG_INF("\r\n\r\n");
	k_msleep(1000);

	LOG_INF("===== NUCLEO-WB15CC DK =====");
    LOG_INF("Firmware version: %d.%d.%d", 
				CONFIG_APP_MAJOR_VERSION,
				CONFIG_APP_MINOR_VERSION,
				CONFIG_APP_BUILD_VERSION);
	LOG_INF("Compiled on: %s %s", __DATE__, __TIME__);
    LOG_INF("========================================");

	gpio_init();
	ble_init();

	ble_adv_start(UINT32_MAX);

	return 0;
}
