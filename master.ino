
int xPin = A1;
int yPin = A0;
int zPin = A2;

int xPosition = 0;
int yPosition = 0;
int zPosition = 0;
byte velDer, velIzq, velInf;

void setup() {
  // inicializar las comunicaciones en serie a 9600 bps:
  Serial.begin(9600); 
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);
}

void loop() {
  xPosition = analogRead(xPin) - 509;
  yPosition = 501 - analogRead(yPin);
  zPosition = analogRead(zPin);
  
  if(xPosition>=0) {
    velIzq = map(abs(yPosition), 0, 501, 0, 100);
    velDer = map(abs(yPosition), 0, 501, 0, 100) - map(xPosition, 0, 514, 0, velIzq);
  }
  if(xPosition<0) {
    velDer = map(abs(yPosition), 0, 501, 0, 100);
    velIzq = map(abs(yPosition), 0, 501, 0, 100) - map(abs(xPosition), 0, 509, 0, velDer);
  }
  velInf = map(zPosition, 0, 1023, 0, 100);

  byte outByte[4] = {255, velDer, velIzq, velInf};
  Serial.write(outByte,4);
  delay(10); // añadir un poco de retraso entre lecturas
}

