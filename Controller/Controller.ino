/*
  ESP-NOW Demo - Transmit
  esp-now-demo-xmit.ino
  Sends data to Responder
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

/*Conntect Joystick Y axis to analog pin 35 and X asix to analog pin 34
 * and button to digital pin 8
*/

int JoyStick_X = 34; // Analog Pin  X
int JoyStick_Y = 35; // // Analog Pin  Y
int JoyStick_button = 8; // IO Pin


// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x0C, 0xB8, 0x15, 0xF5, 0x9F, 0xD4};

// Define a data structure
typedef struct struct_message {
  int switc; //0- digital 1- analog
  int x ,y,command; 
} struct_message;

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
  
  //setting pin modes
  pinMode(JoyStick_X, INPUT);
  pinMode(JoyStick_Y, INPUT);
  pinMode(JoyStick_button, INPUT_PULLUP);
 
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

  // Create test data

  int x = analogRead(JoyStick_X); //  X
  int y = analogRead(JoyStick_Y); //  Y
  int button = digitalRead(JoyStick_button); // 

  // Format structured data
  myData.x = x;
  myData.y = y;
  myData.switc = button;
  myData.command =cmd();
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(10);
}

int cmd()
{
  // put your main code here, to run repeatedly:
  Serial.print("X: ");
  Serial.print(analogRead(34));
  Serial.print(" Y: ");
  Serial.print(analogRead(35));
  Serial.println();
  if ((abs(analogRead(34)-1740)<100) and (abs(analogRead(35)-1740)<100)){
      return 0;
    }
  if ((abs(analogRead(34)-1740)<100) and (abs(analogRead(35))<100)){
      return 1;
    }
  if ((abs(analogRead(34)-1740)<100) and (abs(analogRead(35)-4095)<100)){
      return 2;
    }
  if ((abs(analogRead(34))<100) and (abs(analogRead(35)-1740)<100)){
      return 3;
    }
  if ((abs(analogRead(34)-4095)<100) and (abs(analogRead(35)-1740)<100)){
     return 4;
    }
}
