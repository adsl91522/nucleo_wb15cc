# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(NUCLEO_WB15CC)

zephyr_include_directories(
  inc
)

target_sources(app PRIVATE
    src/main.c
    src/app_gpio.c
    src/app_ble.c
)

# zephyr_code_relocate(FILES src/main.c LOCATION SRAM2)
# zephyr_code_relocate(FILES src/app_gpio.c LOCATION SRAM2)
# zephyr_code_relocate(FILES src/app_ble.c LOCATION SRAM2)
