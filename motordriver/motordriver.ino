/*
  Blink
*/

// ledPin refers to ESP32 GPIO 23
const int EN = 21;
const int IN1 = 18;
const int IN2 = 19;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(IN1, HIGH);   // turn the LED on (HIGH is the voltage level)                  // wait for a second
  digitalWrite(IN2, LOW);// turn the LED off by making the voltage LOW
  for(int i=0;i<250;i=i+5){
    analogWrite(EN,i);
    delay(100);
  }
  digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)                  // wait for a second
  digitalWrite(IN2, HIGH); 
    for(int i=0;i<250;i=i+5){
    analogWrite(EN,i);
    delay(100);
  }
               
}
