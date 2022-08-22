#include "WiFi.h"                             // including the Wifi library
#include "ESPAsyncWebServer.h"                  // including the Web server library

/*
 * Here we declare the ssid (the name of the hotspot created by ESP32) and it's password.
 * Make sure to set the ssid as something unique for your team.
 */
const char* ssid = "esp32-wifi@Knightmares";
const char* password = "12345678";

AsyncWebServer server(80); 
/*
  Blink
*/

// ledPin refers to ESP32 GPIO 23
const int ENA = 21;
const int IN1 = 18;
const int IN2 = 19;
const int ENB = 25;
const int IN3 = 26;
const int IN4 = 27;
int spd=200;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.softAP(ssid, password);                // creates a WiFi hotspot on ESP32
  
  /*
   * After this we can start adding some code to control the ESP32.
   * We can make requests to the server through a webpage and make it perform different tasks.
   */
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin(); 
}

// M1 = left motor, ENA,IN1,IN2
//M2 = right motor, enB,IN3,IN4

//functino for forward
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

void DFORWARD(){
  M1DF(spd);
  M2DF(spd);
}

void DBACKWARD(){
  M1DB(spd);
  M2DB(spd);
}

void DLEFT(){
  M1DB(spd);
  M2DF(spd);
}

void DRIGHT(){
  M1DF(spd);
  M2DB(spd);
}

void STOP(){
  M1DF(0);
  M2DF(0);
}

// the loop function runs over and over again forever
void loop() {        // starts the web server
  server.handleClient();
  command = server.arg("State");
  if (command=="F") DFORWARD();
  else if (command == "B") DBACKWARD();
  else if (command == "L") DRIGHT(); //L makes DRIGHT happen because of some error
  else if (command == "R") DLEFT(); //Similar to above
  else if (command == "0") STOP();

  if (command<11 && command>0) spd=map(command, 1, 10, 100, 250);
  
}
void HTTP_handleRoot(void) {

if(server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
