#include "ESP8266WiFi.h"
const char* MY_SSID = "Cisco06394";
const char* MY_PWD =  "ontani209";
const char WEBSITE[] = "192.168.1.102";


#include <DHT.h>
#define DHTPIN D2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED){
      delay(1000);
      Serial.print(".");
  }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("WIFI connected\n ");
  Serial.println("");

  dht.begin();
}
void loop() {
  WiFiClient client;

    float t = dht.readTemperature();

    char charVal[4];
    String stringVal = "";
    dtostrf(t, 4, 4, charVal);

    for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
    
   if (client.connect(WEBSITE, 4000)){
      Serial.println(stringVal);
      client.print("POST /api/temp?temp=" + stringVal);
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
     } else  Serial.println(client.connect(WEBSITE, 80));
     
  /*float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("temperature : ");
  Serial.println(t);
  Serial.print("humidity : ");
  Serial.println(h);*/
  delay(3000);
}
