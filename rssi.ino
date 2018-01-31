
#include <ESP8266WiFi.h>

// Wi-Fi Settings
const char* ssid = "A"; 
const char* password = "12345678"; 

WiFiClient client;

int led1 = 5;
int led2 = 4;
int led3 = 14;
int led4 = 12;
int led5 = 13;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
      digitalWrite(led1,HIGH);
      delay(300);
      digitalWrite(led1,LOW);
      delay(300);
      digitalWrite(led2,HIGH);
      delay(300);
      digitalWrite(led2,LOW);
      delay(300);
      digitalWrite(led3,HIGH);
      delay(300);
      digitalWrite(led3,LOW);
      delay(300);
      digitalWrite(led4,HIGH);
      delay(300);
      digitalWrite(led4,LOW);
      delay(300);
      digitalWrite(led5,HIGH);
      delay(300);
      digitalWrite(led5,LOW);
}

void ledOn(int led)
{
   digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(led4,LOW);
   digitalWrite(led5,LOW);

   if(led == 1) digitalWrite(led1,HIGH);
   if(led == 2) digitalWrite(led2,HIGH);
   if(led == 3) digitalWrite(led3,HIGH);
   if(led == 4) digitalWrite(led4,HIGH);
   if(led == 5) digitalWrite(led5,HIGH);

   if(led == 0) 
   {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,HIGH);
   }
}

void loop() {

    long rssi = WiFi.RSSI();
    
    Serial.print("RSSI: ");
    Serial.println(rssi); 

    if(rssi > -30) 
    {
      ledOn(0);
    }
    if(rssi <= -30 && rssi > -67) // Amazing
    {
          ledOn(1);
    }
    if(rssi <= -67 && rssi > -70) // Very Good
    {
          ledOn(2);
    }
    if(rssi <= -70 && rssi > -80)  // Ok
    {
          ledOn(3);
    }
    if(rssi <= -80 && rssi > -90)  // not good
    {
          ledOn(4);
    }
    if(rssi <= -90)  // Unusable
    {
          ledOn(5);
    }


  delay(100);
}
