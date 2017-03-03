void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
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
