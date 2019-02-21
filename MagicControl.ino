#include <TimerOne.h>
/*
 * Use Serial data to control pin 13 on the Arduino
 * The Timer one library is used and is implemente to generate a delay of 10s        
 *      timeSetter(); is initilized for a delay of 10s    
 *      limit=10, gives a delay of 1min and 17 s, ie 77s (practical value)
 *      ie limit=243 give a delay of about 30 min=1800s
 * 

 * Base on the 'data' read ,do the following
 *  if 'a' -> power on
 *  if 'b' -> power off
 *  if 'c' -> power off after a delay of 30min 
 *  if 'd' -> power off after a delay of 30*2 min
 *  if 'e' -> power off after a delay of 30*3 min
 *  if 'f' -> power off after a delay of 30*6 min
    
 *        
 */



#define PINOUT 13 // pin 13 on arduino
volatile unsigned long blinkCount = 0;// to keep track of the loop counts
volatile unsigned long limit = 0; // variable to limit/ reset the loop

void setup(){
   
    pinMode(PINOUT, OUTPUT);     
    Serial.begin(9600); 
}
 
void loop()
{     
    String data = ""; // data to be read stored in this variable
    if(Serial.available() > 0){
        while(Serial.available()){
            char inChar = (char)Serial.read(); //read the input
            data += inChar;        //make a string of the characters coming on serial
        } 
        if(data=="a") {   
            digitalWrite( 13,HIGH );
        }  
        else if(data=="b"){   
            blinkCount=0;      // reset the loop counts to zero
            Timer1.detachInterrupt();
            digitalWrite( PINOUT,LOW );
        }

        else if(data=="c") {    
            limit =234;
            timeSetter();
        }
        else if(data="d"){
            limit =468;
            timeSetter();
         }
        else if(data="e"){
            limit =702;      
            timeSetter();
         }        
        else if(data="f") {
          limit =1404;
         timeSetter();
         }                        
         data="";
      
    }

   
}
 
/*  ISR Timer Routine
 *  
 *  increment blink count every 10 seconds
 *  if limit reached,detach interrupt and reset count after making 13 pin low
  
*/ 
void timerIsr()
{
    blinkCount = blinkCount + 1;
    Serial.println(blinkCount);
    if(blinkCount==limit){    // if limit reached, make pin low and reset
       digitalWrite( PINOUT,LOW );
       Timer1.detachInterrupt();
       blinkCount=0;
    }
}

/*
 * Function to make the delay,
 * Make 13 pin high
 * loop throught limit no of times 10 sec 
 */
void timeSetter(){
    digitalWrite( PINOUT,HIGH );
    for(int i=0;i<limit;i++){
        Timer1.initialize(10000000); // Initialize Timer1 for 10seconds
        Timer1.attachInterrupt( timerIsr ); //  service routine 
    }
}


