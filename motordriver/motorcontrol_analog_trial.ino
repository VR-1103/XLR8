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
//ESP Interfacing Pins
const int ESIN = 36 // for getting input from analog joystick
int val=0;// TO TELL MOTOR DIRECTION
int speedlvl=8;
int spd = map(speedlvl, 1, 10, 100, 250);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ESIN, INPUT);
  
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

void DFORWARD(int spd){
  M1DF(spd);
  M2DF(spd);
}

void DBACKWARD(int spd){
  M1DB(spd);
  M2DB(spd);
}

void DLEFT(){
  M1DB(75);
  M2DF(75);
}

void DRIGHT(){
  M1DF(75);
  M2DB(75);
}

void STOP(){
  M1DF(0);
  M2DF(0);
}

// the loop function runs over and over again forever
void loop() {
    val = cmd()
    switch(val) {
      case 0:  // stops the motor when the button is not pushed anymore
        STOP();
        break;
      case 1:
        DFORWARD(spd);
        break;
      case 2:
        DBACKWARD(spd);
        break;
      case 3:
        DLEFT();
        break;
      case 4:
        DRIGHT();
        break;
    }
}
int cmd()
{
  // put your main code here, to run repeatedly:
//  Serial.print("X: ");
//  Serial.print(analogRead(34));
//  Serial.print(" Y: ");
//  Serial.print(analogRead(35));
//  Serial.println();
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
