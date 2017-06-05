//=========================
// Robot motor drive basen on circuit
// L298HN and one ultrasound sensor SRF02 (Serial Com alternative)
// 2017-06-05
//=========================

/*
Sample code for test the SRF02 with the I2C mode based on Arduino UNO!
Command for reference:http://robot-electronics.co.uk/htm/srf02techI2C.htm
Connection:
SRF02       Arduino
5v Vcc    -> 5V
SDA       -> A4
SCL       -> A5
Mode      -> no connection
0v Ground -> GND
*/

#include <Wire.h>

int enable_drive = 0;

int A_enable = 3;
int A_pin_1  = 4;
int A_pin_2  = 5;

int B_enable = 7;
int B_pin_1  = 8;
int B_pin_2  = 9;

void changeAddress(byte oldAddress, byte newAddress)
{
  oldAddress = oldAddress >> 1;
  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA0));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xAA));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA5));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(newAddress);
  Wire.endTransmission();
}

void drive_turn_right()
{
  digitalWrite(A_enable,HIGH);
  digitalWrite(A_pin_1, HIGH);  
  digitalWrite(A_pin_2, LOW); 

  digitalWrite(B_enable,HIGH);
  digitalWrite(B_pin_1, HIGH);  
  digitalWrite(B_pin_2, LOW); 
}

void drive_turn_left()
{
  digitalWrite(A_enable,HIGH);
  digitalWrite(A_pin_1, LOW);  
  digitalWrite(A_pin_2, HIGH); 

  digitalWrite(B_enable,HIGH);
  digitalWrite(B_pin_1, LOW);  
  digitalWrite(B_pin_2, HIGH); 
}

void drive_forward()
{
  digitalWrite(A_enable,HIGH);
  digitalWrite(A_pin_1, HIGH);  
  digitalWrite(A_pin_2, LOW); 

  digitalWrite(B_enable,HIGH);
  digitalWrite(B_pin_1, LOW);  
  digitalWrite(B_pin_2, HIGH); 
}


void drive_backward()
{
  digitalWrite(A_enable,HIGH);
  digitalWrite(A_pin_1, LOW);  
  digitalWrite(A_pin_2, HIGH); 

  digitalWrite(B_enable,HIGH);
  digitalWrite(B_pin_1, HIGH);  
  digitalWrite(B_pin_2, LOW); 
}

void drive_stop()
{
  digitalWrite(A_enable,LOW);
  digitalWrite(A_pin_1, LOW);  
  digitalWrite(A_pin_2, LOW); 

  digitalWrite(B_enable,LOW);
  digitalWrite(B_pin_1, LOW);  
  digitalWrite(B_pin_2, LOW); 
}

#define rangeByte (0x02)
const byte cmdByte = 0x00;
byte highByte = 0x00;               // Stores high byte from ranging
byte lowByte = 0x00;                // Stored low byte from ranging

void setup()
{
  Wire.begin();                // join i2c bus (address optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps

  // Motor A
  pinMode(A_enable,OUTPUT);  // enable
  pinMode(A_pin_1,OUTPUT);   // pin 1
  pinMode(A_pin_2,OUTPUT);   // pin 2

  //Motor B
  pinMode(B_enable,OUTPUT);  // enable
  pinMode(B_pin_1,OUTPUT);   // pin 1
  pinMode(B_pin_2,OUTPUT);   // pin 2

  //changeAddress(0xE2, 0xE0);
  delay(1000);
}


int readSensor(byte adr, byte dd)
{
  int reading = 0;
  Serial.print(adr,HEX);Serial.print(" ");
  adr = adr>>1;
  //Serial.print(adr,HEX);Serial.print(" "); 
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(adr); // transmit to device #112 (0x70)
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(dd);      // command sensor to measure in "centimeters" (0x51)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(adr); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  //Wire.requestFrom(adr, 2);    // request 2 bytes from slave device #112
  if (Wire.requestFrom(adr, 2) != 2)
    {
          Serial.print("error1!");
    }
    else
    {
          Serial.print("reading1...");
          highByte = Wire.read();  // Get high byte
          lowByte = Wire.read(); 
          reading = (highByte << 8) + lowByte;
          Serial.print(reading);   // print the reading
          Serial.print("cm");  
    }
  return reading;
}

int front_meas = 0;
int rear_meas = 0;

void loop()
{
  front_meas = readSensor(0xE0,0x51);
  delay(100);
  rear_meas  = readSensor(0xE2,0x51);
  delay(100);

  if(enable_drive == 1)
  {
    if(front_meas < 20 && rear_meas > 50) 
    {
      drive_backward();
    }
  
    if(front_meas > 19) 
    {
      drive_forward();
    }
  
    if(front_meas < 20 && rear_meas < 20) 
    {
      drive_turn_right();
    }
  }
  
  
  Serial.println(" ");
}

