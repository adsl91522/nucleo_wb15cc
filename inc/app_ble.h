#ifndef APP_BLE_H
#define APP_BLE_H

enum ble_state{
    BLE_DEINIT,
    BLE_INIT,
    BLE_ADV_STOP,
    BLE_ADV_START,
};

void ble_bcn_clear(void);
int ble_scan_bcn_raw(uint8_t max, uint8_t** buffer, int8_t* rssi);
int ble_scan_start(uint32_t timeout);
int ble_adv_stop(void);
int ble_adv_start(uint32_t timeout);
int ble_deinit(void);
int ble_init(void);

#endif