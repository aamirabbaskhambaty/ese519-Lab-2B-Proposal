### TODO:

Use the capabilities of your sequencer to implement the ADPS9960 protocol and control the sensor.

### Explanation 
1. The logic behind the sequencer implemnented in part 3 and 4 is extended to read the APDS9969  via the i2c bus using PIO.
2. We need to first get the raw values from the APDS9969 Registers for proximity and colour values i.e. RGBC.
3. Referring the APDS9969 datasheet the way we access the values (Read or Write) is by first sending a command byte to the slave at adreess 0x39, followed by the register from which we want to read or write followed by the data.

![Screenshot 2022-11-18 152748](https://user-images.githubusercontent.com/114267693/202796907-eccbeaef-b48b-4612-8a43-386ac9344850.png)

4. In order to initialise the sensor, the power, proixmity and colour enabling bits need to be set at register 0x80.
5. In the main while we first check if the values of the proximity and colour registers have changed. This is done by accessing the status register at 0x93. The bits corresponding to the status register for Proximity and Colour are bit no. 1 and bit no. 0 respectively.

![Screenshot 2022-11-18 153948](https://user-images.githubusercontent.com/114267693/202798670-b086d270-a4d1-4f05-920f-babaed5a859e.png)

6. If the status of these bits changes we read the Colour data (0x94 to 0x9B) and Proximity(0x9C) values and display the output in the console. 

![Screenshot 2022-11-18 154803](https://user-images.githubusercontent.com/114267693/202799710-808f16df-aedc-4591-9085-bd978fa28238.png)
![image](https://user-images.githubusercontent.com/114267693/202799826-1bbe31e4-e395-43d1-9cd2-6e9f297dde9b.png)
7. The final Output we achieve is as follows:
![WhatsApp Image 2022-11-18 at 3 18 57 PM](https://user-images.githubusercontent.com/114267693/202800216-24bd1b1b-14c2-4e6f-870b-2eb24a4e7d7c.jpeg)


