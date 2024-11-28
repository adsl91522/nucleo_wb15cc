### nucleo_wb15cc bring-up in Zephyr
This example explains how to bring up nucleo_wb15cc in Zephyr v3.5.0

-----
### 1. Install Zephyr SDK environment
- Install [toolchain](https://docs.zephyrproject.org/latest/develop/toolchains/zephyr_sdk.html)
```
unzip zephyr-sdk-0.16.0_windows-x86_64.7z
cd zephyr-sdk-0.16.0
setup.cmd
```
- Install west
```
python -m pip install west
```
- Zephyr v3.5.0
```
west init -m https://github.com/zephyrproject-rtos/zephyr --mr v3.5.0
west update
python -m pip install -r ./zephyr/scripts/requirements.txt
python -m pip install -r ./nrf/scripts/requirements.txt
python -m pip install -r ./bootloader/mcuboot/scripts/requirements.txt
```
-----
### 2. STM32_BLE_HCILayer
BLE HCILayer firmware.bin OTA update through STM32CubeProgrammer 
(Note: Zephyr only supports the following firmware)
(1) stm32wb1x_BLE_HCILayer_extended_fw.bin (0x0802D000)
(2) stm32wb1x_BLE_HCILayer_fw.bin (0x08032000)
For details, please refer to [Release Note](https://github.com/adsl91522/nucleo_wb15cc/blob/master/STM32WB15XX_Copro_Wireless_Binaries/STM32WB1x/Release_Notes.html)
- STM32CubeProgrammer -> connected nucleo_wb15cc
- Enter Firmware Upgrade Services -> choose stm32wb1x_BLE_HCILayer_fw.bin
- Start Address:0x08032000 -> Firmware upgrade
- dialog "Firmware Delete Success"
- dialog "Firmware Upgrade Success"
-----
### 3. Patch 
```
../patch/nucleo_wb15cc_zephyr-v3.5.0_e30194/module/hal/stm32/stm32wbxx.h.patch
../patch/nucleo_wb15cc_zephyr-v3.5.0_e30194/zephyr/zephyr.patch
../patch/nucleo_wb15cc_zephyr-v3.5.0_e30194/zephyr/zephyr_new_file.patch
```
-----
### 4. Build code 
```
west build -b nucleo_wb15cct 
west flash
```
-----
### 5. Device Console
Use BLE scanner results "STM32WB15CC"
```
*** Booting Zephyr OS build zephyr-v3.5.0 ***
[00:00:00.017,000] <inf> main:


[00:00:01.017,000] <inf> main: ===== NUCLEO-WB15CC DK =====
[00:00:01.017,000] <inf> main: Firmware version: 1.0.0
[00:00:01.017,000] <inf> main: Compiled on: Nov 28 2024 17:38:21
[00:00:01.017,000] <inf> main: ========================================
[00:00:01.036,000] <inf> bt_hci_core: Identity: 02:80:E1:00:00:00 (public)
[00:00:01.036,000] <inf> bt_hci_core: HCI: version 1.0b (0x00) revision 0xa07b, manufacturer 0x0030
[00:00:01.036,000] <inf> bt_hci_core: LMP: version 1.0b (0x00) subver 0x007b
[00:00:01.036,000] <inf> app_ble: Bluetooth initialized
[00:00:01.125,000] <inf> app_ble: BLE advertising start
```
