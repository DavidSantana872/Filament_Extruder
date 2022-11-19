// Funcionamiento de arduino eslavo
#include <Wire.h>

// Arduino esclavo(control motor paso a paso)
int status = 0;
int Dir =  2;
int Pulse =  3;
int Velocity = 65;
// min velocity 65 and max velocity whatever you want 
void setup() {

  Serial.begin(9600);
  pinMode(Dir, OUTPUT);
  pinMode(Pulse, OUTPUT);
  digitalWrite(Dir, HIGH);
  Wire.begin(1);
  Wire.onReceive(read_status);
}
void loop() {
  
  Wire.onReceive(read_status);
  
  while(status == 1){
    digitalWrite(Pulse, LOW);
    digitalWrite(Pulse, HIGH);
    delayMicroseconds(Velocity);  
  }

}
void read_status(){
  if(Wire.available() == 1){
    status = Wire.read();
  }
}


