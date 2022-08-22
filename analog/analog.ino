void setup()
{
        
  // put your setup code here, to run once:
  pinMode(34, INPUT);
  pinMode(35, INPUT);

  Serial.begin(9600);
}

void loop(){
  Serial.println();
  Serial.print(cmd());
  delay(250);
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
