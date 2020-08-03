#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char *ssid = "CABIN1";
const char *pass = "asdfghjkl";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.print(ssid);
  Serial.print("connected ip");
  Serial.println(WiFi.localIP());
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}