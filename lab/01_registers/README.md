### TODO:

Toggle the Qt Py's Neopixel LED when the BOOT button is pressed, using only direct register reads to access the boot button status. You may use the SDK to initialize the board and the pins, and the WS2812 example code to toggle the Neopixel.


### Description
1. In order to read directly from the register on pressing the boot button, we first assign the offset adress to the IO base bank to point to the address of the bootn button register.
```
 volatile uint32_t QTPY_GPIO_PIN_REG = IO_BANK0_BASE + 0x004;
```
2. In the main while loop we read the register status and assign it to a variable known as button status
```
uint32_t button_status = register_read(QTPY_BOOT_PIN_REG);
````
3. If the button status is 0 then the LED is set to glow up
Else the led remians off.

![blink_on_boot](https://user-images.githubusercontent.com/114099174/200090063-4bb468eb-cbae-46fa-bdc5-82a3193f4ce8.gif)
