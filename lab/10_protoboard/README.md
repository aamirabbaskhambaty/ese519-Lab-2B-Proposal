### TODO:

Add support for your custom circuit board to your sequencer, and give a demo.
### Explanation
1. The protoboard that we designed is a game that tests the agility of the user. 
2. In the protoboard there are 3 LEDs each with a corresponding push button and a buzzer. 
3. We will first briefly go through the initial game and then talk about the modified version to add support.

#### Part A: Protoboard 
4. The objective of this game is for the user to press the button of the corresponding LED which glows randomly at the time the buzzer is activated which is also done randomly.
5. In the button.c File we declare the three push buttons as INPUTS and the 3LEDs and Buzzer as Outputs.
```
    gpio_set_dir(gpio_pins[BUZZER_PIN], GPIO_OUT);
    gpio_set_dir(gpio_pins[LED_PIN_1], GPIO_OUT);
    gpio_set_dir(gpio_pins[LED_PIN_2], GPIO_OUT);
    gpio_set_dir(gpio_pins[LED_PIN_3], GPIO_OUT); 
    gpio_set_dir(gpio_pins[SW_PIN_1],  GPIO_IN);
    gpio_set_dir(gpio_pins[SW_PIN_2],  GPIO_IN);
    gpio_set_dir(gpio_pins[SW_PIN_3],  GPIO_IN);

```
6. The buzzer and the 3 Leds get activated randomly.
```
int led_gpio_val = rand() % 3; 
        int buzzer_decision = rand() % 2; 

        gpio_put(gpio_pins[(led_gpio_val + 1)], 1);

        gpio_put(gpio_pins[(BUZZER_PIN)], buzzer_decision);

```
7.  We store the input values by storing them into an array and using the following functions:
```
ins[0] = gpio_get(gpio_pins[SW_PIN_1]);
        //sleep_ms(250);
        ins[1] = gpio_get(gpio_pins[SW_PIN_2]);
        //sleep_ms(250);
        ins[2] = gpio_get(gpio_pins[SW_PIN_3]);
```
8. The code will then check if the correct button is pressed and if that is true we print "Its a Hit" Else we print its a Fail.
```
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

```
9. A no cheating condition is also added which prevents pressing two buttons simultaneously.

#### Part B: Protoboard with Sequencer Support
1. In the second part we have added support to our board for the sequencer.
2. A python script has been created which creates a recording.txt file.
3. We also modify the inital C code into a new code i.e. record_play_macro.c to add support for the sequencer.
4. The python script will read the input mode  from the console, If an r is entered we create a .txt file and store the counter values of the sequencer in this .txt file from the serial console.
5. If input mode is P then the python script will open .txt file, write the counter values tp the serial console.
6. The RP2040 will then read the values from the serial console and replay the sequence of the LEDs.
```
if (play_mode == 'p') {
            
            int counter_in= 0;
           
            i = 0;
            while (i < 5){
                
                scanf("%d", &counter_in);
                
                set_neopixel_color(0xffafaf);
                sleep_ms(500);
                set_neopixel_color(0);
                sleep_ms((int)(counter_in)*Scale);
                i = i+1;
                printf("Replayed\n");
            }
```
7. If the input mode is G then the user can play the game as descirbed below. We create an external void function in record_play_macro.c to call the function of the game, this function is an external function defined in the file button_game.c
```
extern void play_button_game(); 
```
8. If G is entered then 
```
 if (play_mode == 'G')
            {
                play_button_game();
            }
```
Demo of the prootboard  in the game mode:

https://user-images.githubusercontent.com/114267693/202828258-e797c31c-6c2d-406a-97fb-2350c847ed9f.mp4

