/*
   Rubén Arce 21/07/2018

   Control de tira de 5m de leds RGB a través de app de móvil

*/
int rojo =10;
int azul = 9;
int verde = 6;
int recibido = 0;

void setup() {
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
void loop() {
  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    recibido = Serial.read(); // Reads the data from the serial port
  }
  if (recibido == 'a') {
    Serial.println("ROJO"); // Send back, to the phone, the String "LED: ON"
    recibido = 0;
    colores('a');
  } else if (recibido == 'b') {
    recibido = 0;
    colores('b');
    Serial.println("VERDE");
  }  else if (recibido == 'c') {
    recibido = 0;
    colores('c');
    Serial.println("AZUL");//////////////////////////////////
  }  else if (recibido == 'd') {
    recibido = 0;
    colores('d');
    Serial.println("AMARILLO");
  }  else if (recibido == 'e') {
    recibido = 0;
    colores('e');
    Serial.println("APAGADO");
  }  else if (recibido == 'f') {
    recibido = 0;
    colores('f');
    Serial.println("Naranja");
  } else if (recibido == 'g') {
    recibido = 0;
    colores('g');
    Serial.println("rosa");
  } else if (recibido == 'h') {
    recibido = 0;
    colores('h');
    Serial.println("blanco");
  } else if (recibido == 'i') {
    recibido = 0;
    colores('i');
    Serial.println("azul claro");
  }
}
void colores (char color) {
  switch (color) {
    case 'a': //rojo
      analogWrite(rojo, 250);
      analogWrite(verde, 0);
      analogWrite(azul, 0);
      break;
    case 'b':
      analogWrite(rojo, 0);
      analogWrite(verde, 250);
      analogWrite(azul, 0);
      break;
    case 'c':
      analogWrite(rojo, 0);
      analogWrite(verde, 0);
      analogWrite(azul, 250);
      break;
    case 'd': //amarillo
      analogWrite(rojo, 250);
      analogWrite(verde, 250);
      analogWrite(azul, 0);
      break;
    case 'e': //apagado
      analogWrite(rojo, 0);
      analogWrite(verde, 0);
      analogWrite(azul, 0);
      break;
    case 'f': //naranja
      analogWrite(rojo, 250);
      analogWrite(verde, 140);
      analogWrite(azul, 0);
      break;
    case 'g': //rosa
      analogWrite(rojo, 250);
      analogWrite(verde, 0);
      analogWrite(azul, 220);
      break;
    case 'h': //blanco
      analogWrite(rojo, 250);
      analogWrite(verde, 250);
      analogWrite(azul, 250);
      break;
    case 'i': //azul claro
      analogWrite(rojo, 0);
      analogWrite(verde, 220);
      analogWrite(azul, 250);
      break;

  }

}

