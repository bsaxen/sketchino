int pir = 2;
int indLed = 13;

void setup() {
  Serial.begin(9600);
  pinMode(pir, INPUT);
  pinMode(indLed, OUTPUT);
}

int count = 0;
void loop() 
{
  count++;
  int pirState = digitalRead(pir);
  Serial.println(count);
  digitalWrite(indLed,pirState);
  delay(1000); 
  if(pirState == LOW)count = 0;     
}
