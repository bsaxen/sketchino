int ledPin      = 12;
int shadowPin   = 13;
int sensorPin   = A0;
int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(shadowPin, OUTPUT);
}


void loop() {
  sensorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH); 
  digitalWrite(shadowPin, HIGH);  
  delay(10);                     
  digitalWrite(ledPin, LOW); 
  digitalWrite(shadowPin, LOW);   
  delay(sensorValue*10);                 
}
