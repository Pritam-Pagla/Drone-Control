#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include<WebSocketsServer.h>

#include "index_NodeMCU_Test1.h";

int pos_num;

int16_t throttle_Val = 0;
int16_t yaw_Val = 0;
int16_t pitch_Val = 0; 
int16_t roll_Val = 0;

uint8_t num; 
WStype_t type; 
uint8_t *payload; 
size_t length;

#define LED 2
#define ServoPin 14   //D5 is GPIO14

//WiFi Connection configuration
const char *ssid = "PriCopter";
const char *password = "01234567";

WebSocketsServer websocket = WebSocketsServer(81);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

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
  delay(100);
  Serial.begin(115200);

  pinMode(LED,OUTPUT);
  myservo.attach(ServoPin); // attaches the servo on GIO2 to the servo object
  
  //Setup the NodeMCU as an AP
  WiFi.softAP(ssid, password);    //Use NodeMCU as an access point

  //If connection successful show IP address in serial monitor
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  //Initialize Webserver
  server.on("/",handleRoot);
  
  server.begin();  
  websocket.begin();
}

//================================================
//     LOOP
//================================================
void loop() {
 server.handleClient();
 websocket.loop();
 websocket.onEvent(WebSocketEvent);
 Serial.print("Throttle:  "); Serial.print(throttle_Val);
 Serial.print("   Yaw:  "); Serial.print(yaw_Val);
 Serial.print("   Pitch:  "); Serial.print(pitch_Val);
 Serial.print("   Roll:  "); Serial.println(roll_Val);
}

void WebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length){
  if (type == WStype_TEXT){
    if(payload[0] == 't'){
      throttle_Val = (int16_t)strtol((const char*) &payload[1], NULL, 10);
    }
    else if(payload[0] == 'y'){
      yaw_Val = (int16_t)strtol((const char*) &payload[1], NULL, 10);
    }
    else if(payload[0] =='p'){
      pitch_Val = (int16_t)strtol((const char*) &payload[1], NULL, 10);
    }
    else if(payload[0] == 'r'){
      roll_Val = (int16_t)strtol((const char*) &payload[1], NULL, 10);
    }
  }
}
//================================================
