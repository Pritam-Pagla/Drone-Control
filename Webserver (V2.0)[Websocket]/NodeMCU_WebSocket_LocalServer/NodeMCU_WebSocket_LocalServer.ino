// ============ By Pritam Pagla ============ //
// The Only Websocket Program is attached within master branch

// NodeMCU SIDE

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<WebSocketsServer.h>

#include "index_NodeMCU_Test1.h";   // Complete Webpage


int16_t throttle_Val = 0;
int16_t yaw_Val = 0;
int16_t pitch_Val = 0; 
int16_t roll_Val = 0;

uint8_t num; 
WStype_t type; 
uint8_t *payload; 
size_t length;

//WiFi Connection configuration
const char *ssid = "MATIRP";       // Can choose these anything one wants
const char *password = "@password";

WebSocketsServer Twebsocket = WebSocketsServer(9001);     
WebSocketsServer Ywebsocket = WebSocketsServer(9002);
WebSocketsServer Rwebsocket = WebSocketsServer(9003);
WebSocketsServer Pwebsocket = WebSocketsServer(9004);

ESP8266WebServer server(80);


//================================================


void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

//================================================
//            Setup
//================================================
 
void setup() {
Serial.begin(115200);
 delay(100);
  
  //Setup the NodeMCU as an AP
  WiFi.begin(ssid, password);   //Use NodeMCU as an access point

  //If connection successful show IP address in serial monitor
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  //Initialize Webserver
  server.on("/",handleRoot);
  
  server.begin();  
  Twebsocket.begin();
  Ywebsocket.begin();
  Rwebsocket.begin();
  Pwebsocket.begin();

}
 
void loop() {

 server.handleClient();
 Twebsocket.loop();
 Ywebsocket.loop();
 Rwebsocket.loop();
 Pwebsocket.loop();
 
 Twebsocket.onEvent(ThrottleEvent);
 Ywebsocket.onEvent(YawEvent);
 Rwebsocket.onEvent(RollEvent);
 Pwebsocket.onEvent(PitchEvent);
 
 Serial.print("Throttle:  "); Serial.print(throttle_Val);
 Serial.print("   Yaw:  "); Serial.print(yaw_Val);
 Serial.print("   Pitch:  "); Serial.print(pitch_Val);
 Serial.print("   Roll:  "); Serial.print(roll_Val);
 Serial.println();
 
}

void ThrottleEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length){
  if (type == WStype_TEXT){
      throttle_Val = (int16_t)strtol((const char*) &payload[0], NULL, 10);
  }
}

void YawEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length){
  if (type == WStype_TEXT){
      yaw_Val = (int16_t)strtol((const char*) &payload[0], NULL, 10);
  }
}

void RollEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length){
  if (type == WStype_TEXT){
      roll_Val = (int16_t)strtol((const char*) &payload[0], NULL, 10);
  }
}

void PitchEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length){
  if (type == WStype_TEXT){
      pitch_Val = (int16_t)strtol((const char*) &payload[0], NULL, 10);
  }
}
