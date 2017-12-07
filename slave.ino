#include <Servo.h>

Servo motIzq, motDer, motInf;
int i;

int vel[4] = {0,0,0,0};  // velocidades
int inval[4];  // valores entrantes

void setup() {
  motIzq.attach(9);  // motor pin 9
  motDer.attach(11);  // motor pin 11
  motInf.attach(6);  // motor pin 6
  Serial.begin(9600);  // serial a 9600 baud
}

void loop() {
  while (Serial.available()<4) {}     // Esperar 4 bytes
  for(int n=0; n<4; n++){
    inval[n] = Serial.read();         // Leer los 4 bytes y ponerlos en un arreglo
  }
  if (inval[0] == 255) {               //
    for (i=1; i<3; i++) {              //
      vel[i] = map(inval[i], 0, 100, 1000, 2000);
    }
    vel[3] = map(inval[3], 0, 100, 1000, 2000);
  }
  motDer.writeMicroseconds(vel[1]);
  motIzq.writeMicroseconds(vel[2]);
  motInf.writeMicroseconds(vel[3]);
}
