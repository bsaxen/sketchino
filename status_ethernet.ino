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
  
   // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  else
  {
    Serial.println("Ethernet connection started");
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
  } else {
    Serial.println("connection failed");
  }
  
  delay(1000);
  
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  delay(1000);
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  delay(10000);
}
