### TODO:

- modify your sequencer to use the PIO as its primary I/O engine, including the ability to R/W any register 

### Explanation

#### .pio file modification
The goal of this task is to make the PIO as the primary tool to read inputs i.e. prressing of the boot button and then correspondingly light the neopixel led up based on the sequence of button presses. We basically use PIO to create the sequence we created in part 3 of this lab.
1. We first need to modify the .pio file in order to create a pio program to read the boot button presses. 
2. The .pio has been modifed to include a new pio segment to read the button presses. 
3. In the .pio file we create a .boot program.
4. A new .wrap target file has been created where we instruct in assembly to:
a. Read one byte of data from the specified pin(in this case pin 21).
b. Push the read byte to the RX FIFO.
c. Keep looping.
```
.wrap_target
 again:
 in pins, 1
 push block
 jmp again 
 nop           
.wrap

```
5. in the pio files the following C-SDK functions are added:
a. Create a boot prgram to initialize the pio.
b. initialize the boot pin gpio to the pio.
```
pio_gpio_init(pio, pin);

```
c. Set the pin directions as input, with the state machine instance and the number of consecutive pins to be initialized. To set as an input we set the last parameter to False.
```
 pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);
```
d. Initialize the remaining pio defaults 
```
pio_sm_config c = boot_program_get_default_config(offset);


    sm_config_set_in_pins(&c, pin);
   
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);
    
    
    sm_config_set_clkdiv(&c, 1/10000);
    

    

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
    
```
#### C file modification
1. Once the .PIO File has been modifed we go the .C file needs to be modifed from the previous lab.
2. The PIO instance for the GPIO (Boot Button) is declared along with the state machine instance. We assign the boot button to the same PIO as the WS2812, i.e. PIO0.
3. We also add the the boot program to the PIO.
```
PIO pio = pio0;
    int sm = 0;
    int sm1 = 1;
    uint offset = pio_add_program(pio, &ws2812_program);
    uint offset1 = pio_add_program(pio, &boot_program);

```
4. The GPIO pins are initialised and set as input.
```
pio_gpio_init(pio, QTPY_BOOT_PIN_NUM);
pio_sm_set_consecutive_pindirs(pio, sm1, QTPY_BOOT_PIN_NUM, 1, false);
```
5. Now the GPIO 21 i.e. the boot pin has been assigned to the PIO. 
6. We will now read the value of the RX FIFI which contains the boot pin status.
```
uint32_t pinval = pio_sm_get(pio, sm1);
```
Video:



https://user-images.githubusercontent.com/114267693/202834690-8cf2bcf2-17f0-4077-95a8-8a5b01780b79.mp4


