//========================================
// Benny Saxen
// Date: 2018-02-11
//========================================

#include <SPI.h>
#include <Ethernet.h>
#include <U8glib.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "spacecollapse.simuino.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

EthernetClient client;

//==================================================
// OLED I2C
//==================================================

//U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9);// SW SPI protocol(4 pins): SCK = 13, MOSI = 11, CS = 10, A0 = 9  
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); // Small display I2C protocol (2 pins)
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // Large display
char dl[16][16],dm[16][16],dr[16][16];
//=================================================
void NB_oledDraw() 
//=================================================
{
 u8g.firstPage();  
  do {
        draw();
  } while( u8g.nextPage() ); 
}
//=================================================
void draw()
//=================================================
{
  // Horizontal pixels: 0 - 120
  // Vertical pixels: 0 - 63
  u8g.setFont(u8g_font_6x10);
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  
  u8g.drawStr( 0, 10, dl[1]);
  u8g.drawStr( 0, 27, dl[2]);
  u8g.drawStr( 0, 45, dl[3]);
  u8g.drawStr( 0, 62, dl[4]);

  u8g.drawStr( 45, 10, dm[1]);
  u8g.drawStr( 99, 27, dm[2]);
  u8g.drawStr( 99, 45, dm[3]);
  u8g.drawStr( 45, 62, dm[4]);

  u8g.drawStr( 100, 10, dr[1]);
  u8g.drawStr( 100, 27, dr[2]);
  u8g.drawStr( 100, 45, dr[3]);
  u8g.drawStr( 100, 62, dr[4]);  

}

//=================================================
void clearOled()
//================================================= 
{
  int i;
  for(i=1;i<=4;i++)
  {
    strcpy(dl[i]," ");
    strcpy(dm[i]," ");
    strcpy(dr[i]," ");
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
    // OLED
//=================================================

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  clearOled();
  
  sprintf(dl[1],"%s","Space");
  sprintf(dm[1],"Collapse");

  NB_oledDraw();

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
 
}

void loop() {
  
  delay(2000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    //client.println("GET /scServer.php?op=2&label=astenas_nytomta_nixie2_0&param=value HTTP/1.1");
    client.println("GET /scServer.php?op=2&label=kil_kvv32_esp4_2&param=value HTTP/1.1");
    client.println("Host: spacecollapse.simuino.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
   delay(2000);
  char c;
  int i;
  int start = 0;
  char result[40];
  while (client.available()) {
    c = client.read();
    Serial.print(c);
    if(c=='[')
    {
      start = 1;
      i = 0;
    }
    if(c==']')
    {
      start = 0;
      result[i] = '\0';
      result[0] = ' ';
    }
    if(start == 1)
    {
      result[i] = c;
      i++;
    }
  }
  
  sprintf(dl[3],"%d",i);
  sprintf(dl[4],"%s",result);
  
  NB_oledDraw();

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
}
