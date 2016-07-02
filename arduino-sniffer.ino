//=====================
// arduino-sniffer.ino
// 2016-07-02
//=====================

char msg[160],stemp[8];

int pinStatus(int pin)
{
  unsigned long time0,time1,time2,delta=0,duration=0;
  digitalWrite(13,HIGH);
  int i,res=0,res1=0,res2=0,ret = 0;
  time0 = millis();
  for(i=0;i<4000;i++)
  {
    res2 = res1;
    res1 = digitalRead(pin);
    if(res1 > res2) // rising
    {
     // delta = delta + millis() - time1;
     // time1 = millis();
      res++;
    }
    delay(1);
  }
  res = 4000/res;
  //time2 = millis();
  //duration = time2-time0;
//  if(res == 20000)
//    ret = 1;
//    else
//    {
//    ret = delta; // frequency
//    }
  digitalWrite(13,LOW);
  
  return(res);
}

void  setup()
{
 int i;
 Serial.begin(9600);
 pinMode(13,OUTPUT);
 for(i=2;i<13;i++)pinMode(i,INPUT_PULLUP);
}
int st[14];
void loop()
{
   int i;
 //digitalWrite(13,HIGH);
 for(i=2;i<=12;i++)st[i] = pinStatus(i);

 //word x=0,y=0;
 strcpy(msg,"<");
 // pin 0 - 7
 //x = PIND & 0xff; 
 //y = PINB & 0x3f;
 //y = y << 6;
 //Serial.println(PINB);
 //sprintf(stemp,":%x %x",x,y);
 for(i=2;i<=12;i++)
 {
  sprintf(stemp," %d ",st[i]);
  strcat(msg,stemp);
 }
 
 //digitalWrite(13,LOW);
 //delay(1);
 //digitalWrite(13,HIGH);
 Serial.println(msg);
 //digitalWrite(13,LOW);
}
