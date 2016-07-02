//=====================
// arduino-sniffer-test.ino
// 2016-07-02
//=====================

void onoff(int pin,int ll)
{
 int i;
 for(i=0;i<ll;i++)
 {
  digitalWrite(pin,HIGH);
  delay(100);
  digitalWrite(pin,LOW);
  //delay(1);  
 }
}

void setup() 
{
 int i;
 for(i=2;i<13;i++)pinMode(i,OUTPUT);
}

void loop() 
{
int i;
onoff(5,1);
onoff(6,1);

}
