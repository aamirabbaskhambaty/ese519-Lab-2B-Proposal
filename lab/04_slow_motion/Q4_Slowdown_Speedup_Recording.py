import serial, os


COM_NAME = 'COM5'
BAUDRATE = 115200
TIMEOUT = 5 


getcount = []

counter = ''


ser = serial.Serial(COM_NAME, BAUDRATE, timeout=TIMEOUT)

if os.path.exists("recording.txt"):
    os.remove("recording.txt")


while True:
    
        if os.path.exists("recording.txt"):
            os.remove("recording.txt")
        
        while (counter != b'\r\n'):
            
            if ser.is_open:
                
                counter = ser.readline()
                
                getcount.append(counter)
                
                print(counter)
        
                file_name = open("recording.txt", "a");
                final_str = counter.decode("utf-8")
                if final_str != "":
                    file_name.write(counter.decode("utf-8"))
        
        
        file_name.close() 

        print("Start")
        play_mode = input("Enter play_mode:")
        if play_mode == 'p' or play_mode == 's' or play_mode == 'f': 
        
         file_name = open("recording.txt", "r")
        
       
        flag = 0
        i = 0
        
        
        file_val_arr = [x for x in file_name]
        
        input_val = bytes(play_mode, 'utf-8')
        ser.write(input_val)
                
        counter = ser.readline()
        
        
        while (counter != b'Done replaying all occurences\r\n'):
            print(counter)
            
            if (flag == 0 or counter == b'replayed\r\n'):
                
                file_val = bytes(file_val_arr[i], 'utf-8')
                
                print(file_val)
               
                ser.write(file_val)
                
                i += 2
                
                if i > len(file_val_arr):
                    break
                
                flag = 1
        
            
            counter = ser.readline()
        
        
        file_name.close()


ser.close()