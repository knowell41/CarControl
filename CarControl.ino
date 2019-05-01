

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

#ifndef APSSID
#define APSSID "Sync1234"
#define APPSK  "raimei12"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
int n;
int m;
String result1;
String result2;
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Acknowledge";  // a reply string to send back
String msg = "";
int stat = 0;
int delay_c = 0;
boolean conn = true;
int i = 0;
ESP8266WebServer server(80);


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);
  Udp.begin(localUdpPort);
}

void loop() {
  receive_packet(); 
}


void receive_packet()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    Serial.print(len);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      
    }
    msg += incomingPacket;
    split(msg);
    Serial.println("sp1: " + result1);
    Serial.println("sp2: " + result2);
    
    
    Serial.println(msg);
    if (msg.substring(0,1) == "F")
    {
      i++;
      msg = "";
      Serial.println("FORWARD " + String(i));
      
      forward(result1.toInt(), result2.toInt());
    }
    if (msg == "r")
    {
      i++;
      msg = "";
      Serial.println("REVERSE " + String(i));
      reverse(result1.toInt(), result2.toInt());
    }
    
    if (msg == "stop")
    {
      i++;
      msg = "";
      Serial.println("STOP " + String(i));
      stop_();
    }
  }
}

void forward(int sp0, int sp1) {
  analogWrite(D0, sp0);
  analogWrite(D1, LOW);
  analogWrite(D2, LOW);
  analogWrite(D3, sp1);
}

void reverse(int sp0, int sp1) {
  digitalWrite(D0, LOW);
  digitalWrite(D1, sp0);
  digitalWrite(D2, sp1);
  digitalWrite(D3, LOW);
}

void stop_(){
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
}


String split(String msg) {
  Serial.println("len: " + String(msg.length()));
  for (int x=0; x<msg.length(); x++) {
    String strtest = msg.substring(x, x+1);
    if(strtest == "!") {
      n = x;
    }
    if(strtest == "@") {
      m = x;
    }
    
  }
  result1 = msg.substring(n+1,m);
  result2 = msg.substring(m+1, msg.length());
  Serial.println("result 1: " + result1);
  Serial.println("result 2: " + result2);
  n = 0;
  m = 0;  
  
}
