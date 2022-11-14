// Funcionamiento de arduino eslavo
#include <Wire.h>

// Arduino esclavo(control motor paso a paso)
bool start_stop = false;
int value;
int estado = 0;
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
  Wire.onReceive(funt);
}
void loop() {
  
  Wire.onReceive(funt);
  Serial.println(estado);

  while(estado == 1){
    
    digitalWrite(Pulse, LOW);
    digitalWrite(Pulse, HIGH);
    delayMicroseconds(Velocity);  
  }

}
void funt(){
  if(Wire.available() == 1){
    estado = Wire.read();
  }
}


