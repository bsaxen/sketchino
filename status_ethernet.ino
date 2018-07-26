#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 10, 0, 0, 177 };
//byte server[] = { 81,224,182,81 };
char server[] = "simuino.com";
EthernetClient client;

void setup()
{
  //Ethernet.begin(mac, ip);
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  
   // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  else
  {
    Serial.println("Ethernet connection started");
    digitalWrite(7,HIGH);
  }

  delay(1000);

}

void loop()
{
    
  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /bot.txt HTTP/1.0");
    client.println();
    digitalWrite(8,HIGH);
  } else {
    Serial.println("connection failed");
       digitalWrite(8,HIGH);
  }
  
  delay(1000);
  
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
    digitalWrite(8,HIGH);
  }
  
  delay(1000);
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  delay(10000);
}
