
int greenLed  = 8;
int redLed    = 9;
int yellowLed = 10;
int interruptPin = 2;

void blink() {
  int x = 0;
  digitalWrite(yellowLed,HIGH);
  for (int i=1;i<1000;i++)x++;
  digitalWrite(yellowLed,LOW);
}

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  digitalWrite(greenLed, HIGH); 
}


void loop() {
  //digitalWrite(redLed,HIGH);
  delay(500);
  //digitalWrite(redLed,LOW); 
  delay(500);                
}
