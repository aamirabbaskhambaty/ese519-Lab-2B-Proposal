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
int counter = 0;
        int i = 0;
        int getcount[5] = {0};
        
        
        while (i < Total_Presses){
            uint32_t boot_status = register_read(QTPY_BOOT_PIN_REG);
            if(boot_status != 0){
                counter+=1;
            }else{
                if (counter != 0){
                    printf("%d\n", counter);
                    getcount[i] = counter;
                    i += 1;
                }
                counter = 0;
            }
            sleep_ms(100);
        }
```
4. Once the button presses are recorded we replay the sequence by correspondingly lighting up the led.
```
uint32_t counter_in;
        while (i < 5){
            scanf("%d", &counter_in);
            set_neopixel_color(0xffafaf);
            sleep_ms(500);
            set_neopixel_color(0);
            sleep_ms(counter_in*50);
            i = i+1;
            printf("Replayed\n");
        }
        printf("Done\n");
```
        
        
        
        
        
  
