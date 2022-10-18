// Includes the Servo library
#include <Servo.h>. 
#include <SoftwareSerial.h>   //header file of software serial port

SoftwareSerial Serialx(2, 3); //define software serial port name as Serial1 and define pin2 as RX & pin3 as TX

Servo myServo;
int dist;                     //actual distance measurements of LiDAR
int strength;                 //signal strength of LiDAR
int check;                    //save check value
int i;
String dataf;
int uart[9];                   //save data measured by LiDAR
const int HEADER = 0x59;      //frame header of data package

void setup() {
  // put your setup code here, to run once:

 Serial.begin(115200);         //set bit rate of serial port connecting Arduino with computer
 Serialx.begin(115200);      //set bit rate of serial port connecting LiDAR with Arduino
 Serial.println("Radar Start");
 myServo.attach(12); // Defines on which pin is the servo motor attached
}

void loop() {
  if (Serialx.available())                //check if serial port has data input
  { for(int deg=0;deg<=180;deg++){  
     myServo.write(deg);
    if (Serialx.read() == HEADER)        //assess data package frame header 0x59
    {
      uart[0] = HEADER;
      if (Serialx.read() == HEADER)      //assess data package frame header 0x59
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)         //save data in array
        {
          uart[i] = Serialx.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))        //verify the received data as per protocol
        {
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          int distance =dist;
          int _degrees =deg;
          //Serial.print(distance);
          Serial.print(_degrees);
          Serial.print(",");
          //Serial.println(_degrees);        //output measure distance value of LiDAR
          Serial.println(distance);        //output measure distance value of LiDAR
          //dataf= String(deg)+String(",")+String(dist);
          //Serial.println(dataf);
          delay(60);
         }
        }
      }
    }
  }
}
