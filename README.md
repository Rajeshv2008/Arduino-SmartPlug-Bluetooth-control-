# Arduino-SmartPlug-Bluetooth-control-
Arduino based smartplug with bluetooth control and timer functionality

 Use Serial data to control pin 13 on the Arduino
 This can be extend to drive a relay module and control AC power operated devices
 The data is received on the HC-05 module
 
Character control mapping
  if character  'a' -> power on
  if character  'b' -> power off
  if character  'c' -> power off after a delay of 30min 
  if character  'd' -> power off after a delay of 30*2 min
  if character  'e' -> power off after a delay of 30*3 min
  if character  'f' -> power off after a delay of 30*6 min
  
 The Timer one library is used and is implemented to generate a delay of 10s        
      timeSetter() function is initilized for a delay of 10s    
      with limit=10, gives a delay of 1min and 17 s, ie 77s (practical value)
      for eg. limit=243 give a delay of about 30 min=1800s
 

