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

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
}

// M1 = left motor, ENA,IN1,IN2
//M2 = right motor, enB,IN3,IN4

//functino for forward
void M1DF(){ // motor 1 digital forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,200);
}

void M2DF(){ // motor 2 digital forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB,200);
}

void M1DB(){ // motor 1 digital backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA,200);
}

void M2DB(){ // motor 2 digital backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB,200);
}

void DFORWARD(){
  M1DF();
  M2DF();
}

void DBACKWARD(){
  M1DB();
  M2DB();
}

void DLEFT(){
  M1DB();
  M2DF();
}

void DRIGHT(){
  M1DF();
  M2DB();
}

// the loop function runs over and over again forever
void loop() {
  DFORWARD();
  delay(5000);
  DBACKWARD();
  delay(5000);
  DRIGHT();
  delay(5000);
  DLEFT();
  delay(5000);
               
}
