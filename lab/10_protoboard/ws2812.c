/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <boards/adafruit_qtpy_rp2040.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "registers.h"

#define IS_RGBW true
#define NUM_PIXELS 150
#define QTPY_BOOT_PIN 21

#define SLEEP_PRECISION_MS      100
#define TIME_FOR_PRESS_S        5
#define LOOP_COUNT             (TIME_FOR_PRESS_S * 1000)/SLEEP_PRECISION_MS

int buttonRecord[LOOP_COUNT];

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 11
#endif


static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}


int main() {
    //set_sys_clock_48();
	int gpio = PICO_DEFAULT_WS2812_POWER_PIN;
	gpio_init(gpio);
	gpio_set_dir(gpio, GPIO_OUT);
	gpio_set_outover(gpio, GPIO_OVERRIDE_HIGH);
    
    printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);

    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    stdio_init_all();


    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    volatile uint32_t QTPY_BOOT_PIN_REG = IO_BANK0_BASE + 0x0A8;

    while(1)
    {
            printf("Press 's' to start Pressing in 3 seconds \n");

            //sleep_ms(100000);

            char in = getchar_timeout_us(1000);

            //sleep_ms(3000);

            if(in == 's')
            {
                int i = 0; 

                printf("START PRESSING BOOT \n");
                
                while(i < LOOP_COUNT)
                {
                    buttonRecord[i] = gpio_get(QTPY_BOOT_PIN);

                    i++;

                    sleep_ms(SLEEP_PRECISION_MS);
                }

                printf("Thanks for input. Blinking LED now \n");
                sleep_ms(1000);

                i = 0;


                while(i < LOOP_COUNT)
                {

                    
                    if(buttonRecord[i] == 1)
                    {
                        put_pixel(0xffafaf);
                    }

                    else
                    {
                        put_pixel(0);
                    }
                    

                    i++;

                    sleep_ms(SLEEP_PRECISION_MS);
                }

                put_pixel(0);
            }

            sleep_ms(1000);

    }
}
