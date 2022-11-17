/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include <boards/adafruit_qtpy_rp2040.h>


#include "hardware/clocks.h"

#include "registers.h"


#define QTPY_BOOT_PIN_NUM 21
#define QTPY_GPIO_PIN_NUM 0

int main() {
    stdio_init_all();
    gpio_init(QTPY_GPIO_PIN_NUM);
    gpio_set_dir(QTPY_GPIO_PIN_NUM, GPIO_IN);

    //stdio_init_all();
    volatile uint32_t QTPY_GPIO_PIN_REG = IO_BANK0_BASE + 0x004;
   /* while (true) {
	    printf("Hello, USB!\n");
        sleep_ms(1000);
    }*/
   // return 0;
   while (!stdio_usb_connected());
   while(1){
        
        uint32_t value;
        printf("enter value to be masked");
        
        scanf("%x", &value);
        printf("\n");
        printf("Value you entered is:");
        printf("0x%08x\n", value);
        uint32_t gpio_status = register_read(QTPY_GPIO_PIN_REG);
        printf("\n");
        printf("Previous Value:");
        printf("0x%08x\n", gpio_status);
        register_write((QTPY_GPIO_PIN_REG), (register_read(QTPY_GPIO_PIN_REG)|value));
        uint32_t new_status = register_read(QTPY_GPIO_PIN_REG);
        printf("\n");
        printf("New Register Value:");
        printf("0x%08x\n", new_status);
        printf("\n");
        sleep_ms(1000);
    }
}

