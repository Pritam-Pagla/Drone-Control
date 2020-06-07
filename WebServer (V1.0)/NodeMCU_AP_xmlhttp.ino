#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#include "index_xmlhttp.h";

int pos_num;
int throttle_Val, yaw_Val, pitch_Val, roll_Val;
#define LED 2
#define ServoPin 14   //D5 is GPIO14

//WiFi Connection configuration
const char *ssid = "PriCopter";
const char *password = "01234567";


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

ESP8266WebServer server(80);


//================================================
void handleThrottle(){
  String ThrottlePOS = server.arg("throttleVal");
  throttle_Val = ThrottlePOS.toInt();
  server.send(200, "text/plane","");
 }
 
void handleYaw(){
  String YawPOS = server.arg("yawVal");
  yaw_Val = YawPOS.toInt();
  server.send(200, "text/plane","");
 }
 
void handlePitch(){
  String PitchPOS = server.arg("pitchVal");
  pitch_Val = PitchPOS.toInt();
  server.send(200, "text/plane","");
 }
 
void handleRoll(){
  String RollPOS = server.arg("rollVal");
  roll_Val = RollPOS.toInt();
  server.send(200, "text/plane","");
 }


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
  server.on("/throttle",handleThrottle);
  server.on("/yaw",handleYaw);
  server.on("/pitch",handlePitch);
  server.on("/roll",handleRoll);
  
  server.begin();  
}

//================================================
//     LOOP
//================================================
void loop() {
 server.handleClient();
 Serial.print("Throttle:  "); Serial.print(throttle_Val);
 Serial.print("   Yaw:  "); Serial.print(yaw_Val);
 Serial.print("   Pitch:  "); Serial.print(pitch_Val);
 Serial.print("   Roll:  "); Serial.println(roll_Val);
 
 
 
}
//================================================
