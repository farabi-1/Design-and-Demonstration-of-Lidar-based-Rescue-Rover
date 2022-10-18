#include <ESP8266WiFi.h>

#define SendKey 0  //Button to send data Flash BTN on NodeMCU

int port = 8888;  //Port number
WiFiServer server(port);

//Server connect to WiFi Network
const char *ssid = "UIU";  //Enter your wifi SSID
const char *password = "12345678";  //Enter your wifi Password

int count=0;
//=======================================================================
//                    Power on setup
//=======================================================================
void setup() 
{
  Serial.begin(115200);
  pinMode(SendKey,INPUT_PULLUP);  //Btn to send data
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
 
  // Wait for connection  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
  while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
//=======================================================================
//                    Loop
//=======================================================================

void loop() 
{
  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    while(client.connected()){
      /*if (Serial.available()) {
         Serial.println(Serial.read());
         client.println(Serial.read());
         delay(10);
         */
          if (Serial.available()) {
          size_t len = Serial.available();
          uint8_t sbuf[len];
          Serial.readBytes(sbuf, len);
          client.write(sbuf, len);
          Serial.write(sbuf,len);
          delay(0);
        }
         
        }
     /* for(int deg=360;deg>=1;deg--){
        Serial.println(deg,'\n');
        client.print(deg);
        client.write('\n');
        delay(50);
    }*/
    }
    
    client.stop();
        
  }

//=======================================================================
