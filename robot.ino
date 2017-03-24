//=========================
// Robot motor drive basen on circuit
// L298HN
// 2017-03-24
//=========================

int A_enable = 3;
int A_pin_1  = 4;
int A_pin_2  = 5;

int B_enable = 7;
int B_pin_1  = 8;
int B_pin_2  = 9;

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

void setup() {
  // Motor A
  pinMode(A_enable,OUTPUT);  // enable
  pinMode(A_pin_1,OUTPUT);   // pin 1
  pinMode(A_pin_2,OUTPUT);   // pin 2

  //Motor B
  pinMode(B_enable,OUTPUT);  // enable
  pinMode(B_pin_1,OUTPUT);   // pin 1
  pinMode(B_pin_2,OUTPUT);   // pin 2
}

void loop() {
  drive_forward();
  delay(3000);
  drive_stop(); 
  delay(2000);
  drive_backward();
  delay(3000);
  drive_stop(); 
  delay(2000);
}
