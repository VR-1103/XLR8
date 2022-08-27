/*
  Blink
*/
// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"                  // including the Web server library

const char* ssid = "esp32-wifi@Knightmares";
const char* password = "3.1415926535";

AsyncWebServer server(80);
 
// Define a data structure
typedef struct struct_message {
  int x,y,cmd;
  int spid;
} struct_message;

 
// Create a structured object
struct_message myData;
 
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
//  Serial.print("Data received: ");
//  Serial.println(len);
//  Serial.print("X Value: ");
//  Serial.println(myData.x);
//  Serial.print("Y Value: ");
//  Serial.println(myData.y);
//  Serial.print("digital Value: ");
//  Serial.println(myData.cmd);
//  Serial.println();
}
 
// ledPin refers to ESP32 GPIO 23
const int ENA = 21;
const int IN1 = 18;
const int IN2 = 19;
const int ENB = 25;
const int IN3 = 26;
const int IN4 = 27;
int spdlvl=3;
int spd = map(spdlvl,1,5,100,250);
//ESP Interfacing Pins
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
//  Serial.begin(1200);

  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  WiFi.softAP(ssid, password);                // creates a WiFi hotspot on ESP32

  server.on("/F", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    
    M1DF(spd);
    M2DF(spd);
    request->send_P(200, "text/plain", "");   
  });

  server.on("/B", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we recieve a "turn-off" request from the webpage
    
    M1DB(spd);
    M2DB(spd);
    request->send_P(200, "text/plain", "");
  });

  server.on("/R", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we recieve a "turn-off" request from the webpage
    
    M1DF(100);
    M2DB(100);
    request->send_P(200, "text/plain", "");
  });

  server.on("/L", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we recieve a "turn-off" request from the webpage
    
    M1DB(100);
    M2DF(100);
    request->send_P(200, "text/plain", "");
  });
  server.on("/S", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    M1DF(0);
    M2DF(0);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(1, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/2", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(2, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/3", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(3, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/4", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(4, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/5", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(5, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/6", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(6, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/7", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(7, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/8", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(8, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/9", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(9, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/10", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(10, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });

  server.begin(); 
}

// M1 = left motor, ENA,IN1,IN2
//M2 = right motor, enB,IN3,IN4

void M1DF(int spd){ // motor 1 digital forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,spd);
}

void M2DF(int spd){ // motor 2 digital forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB,spd);
}

void M1DB(int spd){ // motor 1 digital backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA,spd);
}

void M2DB(int spd){ // motor 2 digital backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB,spd);
}


// the loop function runs over and over again forever
void loop() {
    esp_now_register_recv_cb(OnDataRecv);
    //Serial.println(myData.x);
    int val = myData.cmd;
    spdlvl=myData.spid;
    spd = map(spdlvl,1,5,100,250);
    Serial.println(val);
    if(val==0){
      M1DF(0);
      M2DF(0);
    }
    else if(val==1){
      M1DF(spd);
      M2DF(spd);
    }
    else if(val==2){
      spd = constrain(int(spd*1.25),0,250);
      M1DF(spd);
      M2DF(0);
    }
    else if(val==3){
      M1DF(constrain(int(spd*3/5),100,250));
      M2DB(constrain(int(spd*3/5),100,250));
    }
    else if(val==4){
      spd = constrain(int(spd*1.25),0,250);
      M1DB(spd);
      M2DF(0);
    }
    else if(val==5){
      M1DB(spd);
      M2DB(spd);
    }
    else if(val==6){
      spd = constrain(int(spd*1.25),0,250);
      M1DF(0);
      M2DB(spd);
    }
    else if(val==7){
      M1DB(constrain(int(spd*3/5),100,250));
      M2DF(constrain(int(spd*3/5),100,250));
    }
    else if(val==8){
      spd = constrain(int(spd*1.25),0,250);
      M1DF(0);
      M2DF(spd);
    }
}
