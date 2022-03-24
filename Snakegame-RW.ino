
#include<Wire.h>
//Samusha Najjuuko
//Beshoy Soliman

const int VRx = A0; //pin for joystick x control
const int VRy = A1;  //pin for joystick y control
const int SW = 2;
int buzz = 6; // buzzer input pin
int X_joyControl; //Xjoystick controls
int Y_joyControl; //Yjoystick controls
bool vertical, horizontal; 
const int mpuAddress=0x68;  
int16_t GyX,GyY,GyZ;
char incomingByte;

void setup() {
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);
  pinMode(buzz,OUTPUT);
}

void loop() {
    X_joyControl = analogRead(VRx); //reading joystick input for x and y directions
    Y_joyControl = analogRead(VRy);
    
 //if's and else if's update and print to serial port x and y inputs from joystick inputs
if(horizontal == false){
    if(X_joyControl >= 900){
      Serial.println("d");
      horizontal = true;
      vertical = false;
    }
    else if(X_joyControl <= 100){
      Serial.println("a");
      horizontal = true;
      vertical = false;
    }
  }
  if(vertical == false){
    if(Y_joyControl >= 900){
      Serial.println("s");
      vertical = true;
      horizontal = false;
    }
    else if(Y_joyControl <= 100){
      Serial.println("w");
      vertical = true;
      horizontal = false;
    }
  }
  //Gyro setup
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x3B);  // starting  register
  Wire.endTransmission(false);
  Wire.requestFrom(mpuAddress,3*2,true);  // request a total of 6 registers
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
//if's and else if's update and print to serial port x and y inputs from Gyro inputs
   
   if(vertical == false){  
    if(GyX >= 10000){
      Serial.println("d");
      vertical = true;
      horizontal = false;
    }
    else if(GyX <= -10000){
      Serial.println("a");
      vertical = true;
      horizontal = false;
    }
  }
  if(horizontal == false){
    if(GyY >= 10000){
      Serial.println("s");
      horizontal = true;
      vertical = false;
    }
    else if(GyY <= -10000){
      Serial.println("w");
      horizontal = true;
      vertical = false;
    }
  }
  //buzzer
   delay(20);
   if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == 'f')
    {
      horizontal = false;
      vertical = false;
    }
    if(incomingByte == 'a'){
      for(int i=0;i<20;i++)
      {
        digitalWrite(buzz,HIGH);
        delay(1);//wait for 1ms
        digitalWrite(buzz,LOW);
        delay(1);//wait for 1ms
      }
    }
   }
}
