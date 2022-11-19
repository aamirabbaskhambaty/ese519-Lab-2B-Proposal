### TODO:

- modify the PIO/DMA logic analyzer example to record a timestamped trace of an RP2040-ADPS9960 exchange while the BOOT button is pressed
- with a partner, connect a second Qt Py to the Stemma Qt bus of an ADPS9960 that's attached to a first Qt Py running the Lab 1 Python code
- record a trace of this exchange


### Explanation
1. In order to get familiar with the Logic Analyzer example we first run the example as it is.
2. The code is then modified to read the i2c Traffic.
3. The Pin instances are changed to read the data from the SDA lines from the sensor. The i2c pin on the QTPY Board is 22 and hence the pin instance is set to 22.
The boot button macro is also defined. The number of captuirng samples is also set to 50000. Since we want to read data from the SDA (22) and SCL(23), the pin count is set to 2
```
#define BOOT_PIN_NUM 21

const uint CAPTURE_PIN_BASE = 22;
const uint CAPTURE_PIN_COUNT = 2;
const uint CAPTURE_N_SAMPLES = 50000;
```

4. In the code in the print buffer function the number of incrementing of samples have been modified to  samples+25 in order to capture the i2c signal more effectively. In the logic analyser example the samples were being incremented by 1, which made it unsuitabe for the i2c traffic since the waveforms were very long and undistinguishable.
```
void print_capture_buf(const uint32_t *buf, uint pin_base, uint pin_count, uint32_t n_samples)
{
    // Display the capture buffer in text form, like this:
    // 00: __--__--__--__--__--__--
    // 01: ____----____----____----
    printf("Capture:\n");
    // Each FIFO record may be only partially filled with bits, depending on
    // whether pin_count is a factor of 32.
    uint record_size_bits = bits_packed_per_word(pin_count);
    for (int pin = 0; pin < pin_count; ++pin)
    {   int prev = 0;
        printf("%02d: ", pin + pin_base);
        for (int sample = 0; sample < n_samples; sample+=25)
        {
            uint bit_index = pin + sample * pin_count;
            uint word_index = bit_index / record_size_bits;
            // Data is left-justified in each FIFO entry, hence the (32 - record_size_bits) offset
            uint word_mask = 1u << (bit_index % record_size_bits + 32 - record_size_bits);
            // printf("%d",prev);

           // if(prev!=buf[word_index] & word_mask==0){
            printf(buf[word_index] & word_mask ? "-" : "_");
           // printf("%d",buf[word_index] & word_mask);
          //  prev = buf[word_index] & word_mask;
           // printf("%d",prev);
           // }
        }

    }
```
5. The example has also been tweaked in order to display the i2c traffic if the boot button is being pressed. If the boot button is pressed the logic analyzer is armed, and the print buffer function is called.

```
if (!gpio_get(BOOT_PIN_NUM))
        {
            
            logic_analyser_arm(pio, sm, dma_chan, capture_buf, buf_size_words, CAPTURE_PIN_BASE, true);



            dma_channel_wait_for_finish_blocking(dma_chan);
          
            print_capture_buf(capture_buf, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, CAPTURE_N_SAMPLES);
            printf("\n");
        }
        else
        {
            continue;
        }
        sleep_ms(500);
    }
```
Output capture of i2c traffic
![Screenshot 2022-11-18 212718](https://user-images.githubusercontent.com/114267693/202830122-5b3bf491-8b3b-44b6-a90f-2bd375fb6e0f.png)

