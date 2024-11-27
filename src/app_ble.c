#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/settings/settings.h>

#include "main.h"

LOG_MODULE_REGISTER(app_ble, LOG_LEVEL_INF);

static struct k_work ble_adv_stop_work;

static struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID128_ALL,
                    0x84, 0xaa, 0x60, 0x74, 0x52, 0x8a, 0x8b, 0x86,
                    0xd3, 0x4c, 0xb7, 0x1d, 0x1d, 0xdc, 0x53, 0x8d),
};

static enum ble_state ble_status = BLE_DEINIT; 

static void ble_adv_stop_work_function(struct k_work *item);
static void ble_adv_stop_timer_handler(struct k_timer* timer);

K_TIMER_DEFINE(ble_adv_stop_timer, ble_adv_stop_timer_handler, NULL);

static void ble_adv_stop_work_function(struct k_work *item)
{
	ble_adv_stop();
}

static void ble_adv_stop_timer_handler(struct k_timer* timer)
{
    k_work_submit(&ble_adv_stop_work);
}

static void bt_ready(int err)
{
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return;
	}

    settings_subsys_init();
    settings_load();

	ble_status = BLE_INIT;

	LOG_INF("Bluetooth initialized");
}

int ble_adv_stop(void)
{
    int ret = 0;

    ret = bt_le_adv_stop();
    if (ret != 0) {
		LOG_ERR("bt le adv stop error: %d", ret);
		return ret;
	}

    ble_status = BLE_ADV_STOP;
	
    LOG_INF("BLE advertising stop");

    return ret;
}

int ble_adv_start(uint32_t timeout)
{
    int ret = 0;

    ret = bt_le_adv_start(BT_LE_ADV_NCONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (ret != 0) {
		LOG_ERR("bt le adv start error: %d", ret);
		return ret;
	}
    
    k_timer_start(&ble_adv_stop_timer, K_MSEC(timeout), K_NO_WAIT);

    ble_status = BLE_ADV_START;

    LOG_INF("BLE advertising start");

    return ret;    
}

int ble_deinit(void)
{
	int ret = 0;

    ret = bt_disable();
    if (ret != 0) {
		LOG_ERR("bt disable error: %d", ret);
		return ret;
	}

	ble_status = BLE_DEINIT;

    LOG_INF("ble deinit");

    return ret;
}

int ble_init(void)
{
    int ret = 0;

    ret = bt_enable(bt_ready);
	if (ret != 0) {
		LOG_ERR("bt enable error: %d", ret);
		return ret;
	}

	while(ble_status != BLE_INIT) {
		k_msleep(100);
	}

	k_work_init(&ble_adv_stop_work, ble_adv_stop_work_function);

    return ret;
}
