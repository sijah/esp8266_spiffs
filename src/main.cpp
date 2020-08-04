#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char *ssid = "CABIN1";
const char *pass = "asdfghjkl";
ESP8266WebServer server(80);

void handle_root()
{
File f = LittleFS.open("/index.html","r");
  server.streamFile(f, "text/html");
  //file.close();
  //server.send(200,"text/html",f);


}

void handle_notfound()
{

  server.send(404, "text/html", "jango pettu");
}

void setup()

{
    Serial.begin(115200);
delay(100);
 if(LittleFS.begin())
 {
     Serial.print("littlefson");
 }
 else
 {
     Serial.print("littlefs no working");
 }
   WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.print(ssid);
  Serial.print("connected ip");
  Serial.println(WiFi.localIP());
   if (!MDNS.begin("esp8266"))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }
  // put your setup code here, to run once:
FSInfo fs_info;
    LittleFS.info(fs_info);
 
    Serial.println("File sistem info.");
 
    Serial.print("Total space:      ");
    Serial.print(fs_info.totalBytes);
    Serial.println("byte");
 
    Serial.print("Total space used: ");
    Serial.print(fs_info.usedBytes);
    Serial.println("byte");
 
    Serial.print("Block size:       ");
    Serial.print(fs_info.blockSize);
    Serial.println("byte");
 
    Serial.print("Page size:        ");
    Serial.print(fs_info.totalBytes);
    Serial.println("byte");
 
    Serial.print("Max open files:   ");
    Serial.println(fs_info.maxOpenFiles);
 
    Serial.print("Max path lenght:  ");
    Serial.println(fs_info.maxPathLength);
 
    Serial.println();
 
    // Open dir folder
    Dir dir = LittleFS.openDir("/");
    // Cycle all the content
    while (dir.next()) {
        // get filename
        Serial.print(dir.fileName());
        Serial.print(" - ");
        // If element have a size display It else write 0
        if(dir.fileSize()) {
            File f = dir.openFile("r");
            Serial.println(f.size());
            f.close();
        }else{
            Serial.println("0");
        }
    }
server.on("/",handle_root);
server.onNotFound(handle_notfound);

server.begin();



}


void loop()
{
   MDNS.update();
  server.handleClient();
}
