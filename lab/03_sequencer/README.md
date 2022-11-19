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
-->lab_03_sequencer is divided into three subsections. In the first section, we are recording a sequence of boot presses on the QT Py RP2040 device and replaying it.

-->In the second section, we are recording the sequence of boot presses and saving it on the laptop. We are then playing it through the laptop.

-->In the third section, we are using macros to record a sequence, atore it on the laptop, and play it through the laptop.

**Section One**</br>
To record a seuence of boot presses on the QT Py RP2040 device and re-play accordingly, we have measured the time between every 2 consecutive boot presses for a fixed number of presses.</br>
The value taken by the boot pin register on a boot press is `0x00000000`. A counter is continuously increamented between two boot pin presses. The counter value is stored in an array and after the recording is done for all the boot presses, this array is used to replay the recorded sequences.</br>
The Neopixel LED blinks with delay equal to the counter value between two presses. 
This entire recording is looped for replaying multiple times. 


**Section Two**</br>
This section comprises of recording a boot press sequence, saving it on the laptop, and replaying it from the laptop. For doing so, `pySerial` library is used to access the RP2040 through the COM port.</br>

The C code is used to count the time between two boot presses, and the variable `counter` is printed on the console during the recording. A python script is used then to access the COM port to whcih RP2040 is connected to using the pySerial library.</br>

The value printed on the console is read and saved in a file on the laptop by the Python script. After the recording is over for all the boot presses, the python script reads the delay (counter) values from the text file on the laptop and writes it to the console which is input to the RP2040 and replayed. 


**Section Three**</br>
In this section, we have used macros to record and save a sequence of boot presses on the laptop as well as to play it from the laptop. It is similar to the previous part except we use macros to instruct to record and re-play.

A `counter` variable is used which measures the time between two consecutive boot presses. 

An input `play_mode` is taken from the user based on whether the user wants to record a new sequence or play an already recorded sequence. The python script uses pySerial library to access the COM port of QT Py RP2040. 

There are two `play_modes`: record `'r'` and play `'p'`. The user can input `'r'` to record a sequence of boot presses and save it to the laptop using the python script. Then on an input of `'p'`, this recorded sequence is read from the file saved on the laptop and wrote to the console by the script. 

The Neopixel LED blinks accordingly.

https://user-images.githubusercontent.com/114099174/202823392-33ffd5cd-09bd-4296-97e6-fbfd5b09fb27.mp4

The above video demonstrates the recording and playing using a macro.
        
  
