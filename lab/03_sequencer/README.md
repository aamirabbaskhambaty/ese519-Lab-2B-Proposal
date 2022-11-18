### TODO:

Create a 'sequencer' that allows you to record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. You should be able to:
- record at a least a few seconds of button input to your RP2040 (in RAM)
- replay a recorded sequence on your NeoPixel
- loop a recording
- save a recording to your laptop (the Python Serial library is one way to do this)
- play a recording from your laptop
- record 'macros' (a sequence of console commands) based on keystrokes in your serial console
- hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
- include multiple I/O sources in a recording, and remap among the following:
    - inputs: BOOT button, console commands, register read/write commands
    - outputs: neopixel color, neopixel brightness, data over serial, register read/write commands

### Explanation:
1. The goal of this lab is to record the boot button presses 5 times, and correspondingly light the neopixel led with the same time sequence as the button presses.
2. We first record the button presses using the register read button. 
3. If the button is pressed we increment a varibale known as counter, else the value of this counter is stored at the "i"th position of an array known as get count. i loops from 0 to total number of button presses to be recorded, ie 5.
```
uint32_t button_status = register_read(QTPY_BOOT_PIN_REG);

        printf("0x%08x\n", button_status);
        
        int counter = 0;
        int num_boot_press = 0;
        while(num_boot_press < 5){
        uint32_t button_status = register_read(QTPY_BOOT_PIN_REG);
        if(button_status != 0x00000000){
        counter = counter + 1;


        }
        else{
            
            getcount[i] = counter;
            sleep_ms(500);
            counter = 0;
            num_boot_press = num_boot_press+1;
            i=i+1;
        }
        
        }
```
4. Once the button presses are recorded we replay the sequence by correspondingly lighting up the led. The delay between two LED blink is dependent on the sleep value which is dictated by the counter value stored in the getcount array.
```
for(i=0;i<5;i++){
          set_neopixel_color(0xffafaf);
          sleep_ms(500);
          set_neopixel_color(0);
          sleep_ms(getcount[i]/2000);
          
        }
```

In order to play the sequence using the python script we make a modification in the C code. 
        
        
        
        
        
  
