// Arduino UNO Sniffer
//=====================

char msg[160],stemp[8];
void  setup()
{
 int i;
 Serial.begin(9600);
 for(i=1;i<=13)pinMode(i,INPUT);
}

void loop()
{
 int i,x;
 strcpy(msg,"<");
 for (i=1;i<=13;i++)
 {
  x =digitalRead(i);
  sprintf(stemp,":%1d",x);
  strcat(msg,stemp);
 }
 for (i=0;i<=5;i++)
 {
  x =analogRead(i);
  sprintf(stemp,":%4d",x);
  strcat(msg,stemp);
 }
 strcat(msg,":>");
 Serial.println(msg);
}
