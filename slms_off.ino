#include<ESP8266WiFi.h>
WiFiClient client;
const char* MY_SSID = "xxxxx";
const char* MY_PWD = "yyyy";
const char* TS_SERVER = "api.thingspeak.com";
String TS_API_KEY ="xxxxx";
void setup(){
  Serial.begin(115200);
  WiFi.begin(MY_SSID,MY_PWD);
    while(WiFi.status()!=WL_CONNECTED){//thingspeak
    Serial.print(".");
    delay(500);
}
    Serial.print("Connected To ");
    Serial.println(MY_SSID);
  pinMode(A0,INPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  digitalWrite(D0,HIGH);
  digitalWrite(D1,HIGH);
}
void multi(int d,int c, int b, int a){
  digitalWrite(D8,a);
  digitalWrite(D7,b);
  digitalWrite(D6,c);
  digitalWrite(D5,a);
  //jesus
}
void loop(){
  int dat;
  multi(LOW,LOW,LOW,LOW);
  dat = analogRead(A0);
  multi(LOW,LOW,LOW,HIGH);
  dat = analogRead(A0);
  Serial.print("LDR value1: ");
  Serial.println(dat);
  Serial.print("LDR value2: ");
  Serial.println(dat);
  if(dat<700){
    digitalWrite(D0,LOW);
    digitalWrite(D1,LOW);
  }else{
    digitalWrite(D0,HIGH);
    digitalWrite(D1,HIGH);
  }
  if(client.connect(TS_SERVER, 80)){
    String data = TS_API_KEY;
    data += "&field1=";
    data += String(dat);
    data +="\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: " + TS_API_KEY + "\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(data.length());
     client.print("\n\n");
     client.print(data);
     delay(1000);

  }
  client.stop();
  delay(1600);
}
