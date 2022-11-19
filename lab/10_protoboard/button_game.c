#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <boards/adafruit_qtpy_rp2040.h>
#include "pico/stdlib.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
//#include "ws2812.pio.h"

#define BUZZER_PIN  0 //20
#define LED_PIN_1   1 //25
#define LED_PIN_2   2 //24
#define LED_PIN_3   3 //26
#define SW_PIN_1    4 //27
#define SW_PIN_2    5 //28
#define SW_PIN_3    6 //29

#define NUM_GPIOS   7

int gpio_pins[] = {20, 25, 24, 26, 27, 28, 29};

int play_button_game()
{
    stdio_init_all();

    int i = 0; 
    
    //
    // Initialise all GPIOs
    //
    for(i = 0; i < NUM_GPIOS; i++)
    {
        gpio_init(gpio_pins[i]);
    }

    gpio_set_dir(gpio_pins[BUZZER_PIN], GPIO_OUT);
    gpio_set_dir(gpio_pins[LED_PIN_1], GPIO_OUT);
    gpio_set_dir(gpio_pins[LED_PIN_2], GPIO_OUT);
    gpio_set_dir(gpio_pins[LED_PIN_3], GPIO_OUT); 
    gpio_set_dir(gpio_pins[SW_PIN_1],  GPIO_IN);
    gpio_set_dir(gpio_pins[SW_PIN_2],  GPIO_IN);
    gpio_set_dir(gpio_pins[SW_PIN_3],  GPIO_IN);

    while(1)
    {
        char x = getchar_timeout_ms(); 


        if(x == 'N')
        {
            return;
        }
        
        int led_gpio_val = rand() % 3; 
        int buzzer_decision = rand() % 2; 

        gpio_put(gpio_pins[(led_gpio_val + 1)], 1);

        gpio_put(gpio_pins[(BUZZER_PIN)], buzzer_decision);

        bool ins[3];

        ins[0] = gpio_get(gpio_pins[SW_PIN_1]);
        //sleep_ms(250);
        ins[1] = gpio_get(gpio_pins[SW_PIN_2]);
        //sleep_ms(250);
        ins[2] = gpio_get(gpio_pins[SW_PIN_3]);
       // sleep_ms(250);

        if((ins[0] == 0 && ins[1] == 0) || (ins[1] == 0 && ins[2] == 0) || (ins[2] == 0 && ins[0] == 0)) 
        {
            printf("NO CHEATING \n");
            continue;
        }

        if(buzzer_decision)
        {
            if(ins[led_gpio_val] == 0)
            {
                printf("It's a hit! \n");
            }

            else
            {
                printf("FAIL! \n");
            }
        }

        sleep_ms(250);

        gpio_put(gpio_pins[(led_gpio_val + 1)], 0);

    }
return 0;
}