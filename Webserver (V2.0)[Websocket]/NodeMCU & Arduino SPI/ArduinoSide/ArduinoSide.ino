// ============ By Pritam Pagla ============ //
// The Only Websocket Program is attached within master branch

// ARDUINO SIDE 


#include <SoftwareSerial.h>
#include <ArduinoJson.h>     // Preferably use ArduinoJson 5.x, as StaticJsonBuffer object is not defined in further versions

SoftwareSerial s(5,6);    // Initializing an instance of softwareSerial Library

void setup() {
  // Initialize Serial port
  s.begin(19200);
Serial.begin(19200);
  while (!Serial) continue;
}
 
void loop() {

 StaticJsonBuffer<100> jsonBuffer;
 JsonObject& root = jsonBuffer.parseObject(s);
  
 if (root == JsonObject::invalid())
    return;

 int  throttle_in = root["throttle"];
 int yaw_in = root["yaw"];
 int roll_in = root["roll"];
 int pitch_in = root["pitch"];
    
Serial.print("  Throttle: "); Serial.print(throttle_in);
Serial.print("  Yaw: "); Serial.print(yaw_in);
Serial.print("  Roll: "); Serial.print(roll_in);
Serial.print("  Pitch: "); Serial.println(pitch_in);
 
}
