#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "C:\Users\12153\pico\pico-sdk\src\rp2_common\hardware_gpio\include\hardware\gpio.h"
#include "C:\Users\12153\pico\pico-sdk\src\boards\include\boards\adafruit_qtpy_rp2040.h"
#include "registers.h"

#define gpio_out_pinn 23
#define gpio_out_pinn2 22


#define IS_RGBW true
#define NUM_PIXELS 150
#define PICO_DEFAULT_WS2812_POWER_PIN 11

#define QTPY_BOOT_PIN_NUM 21

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif

void set_neopixel_color(uint32_t color_num){
    //
    uint32_t r_num = color_num >> 16;
    uint32_t g_num = color_num << 16;
    g_num = g_num >> 24;
    uint32_t b_num = color_num << 24;
    b_num = b_num >> 24;
    uint32_t color_final = ((r_num << 8) |
                            (g_num << 16)|
                            (b_num));
    pio_sm_put_blocking(pio0, 0, color_final << 8u);
}


int main() {
   
    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    int sm1 = 1;
    uint offset = pio_add_program(pio, &ws2812_program);
    uint offset1 = pio_add_program(pio, &boot_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    boot_program_init(pio, sm1, offset1, QTPY_BOOT_PIN_NUM);
    
    const uint POWER_PIN_NAME = PICO_DEFAULT_WS2812_POWER_PIN;
    gpio_init(POWER_PIN_NAME);
    gpio_set_dir(POWER_PIN_NAME, GPIO_OUT);
    gpio_put(POWER_PIN_NAME, 1);

    pio_gpio_init(pio, QTPY_BOOT_PIN_NUM);
    pio_sm_set_consecutive_pindirs(pio, sm1, QTPY_BOOT_PIN_NUM, 1, false);

    stdio_init_all();
    
    int getcount[5] = {0};
    int i = 0;
    while(!stdio_usb_connected());
    while(1){
        
        
        int counter = 0;
        int boot_presses = 0;
        while(boot_presses < 5){
        uint32_t pinval = pio_sm_get(pio, sm1);
        if(pinval != 0x00000000){
        counter = counter + 1;


        }
        else{
            
            getcount[i] = counter;
            sleep_ms(500);
            counter = 0;
            boot_presses = boot_presses+1;
            i=i+1;
        }
        
        }
        sleep_ms(1000);
        for(i=0;i<5;i++){
          set_neopixel_color(0xffafaf);
          sleep_ms(500);
          set_neopixel_color(0);
          sleep_ms(getcount[i]/10000);
          
        }



        sleep_ms(100);
        }
    }

