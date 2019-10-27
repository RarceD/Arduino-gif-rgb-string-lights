#include <IRremote.h>
int RECV_PIN = 12;
int rojo = 10;
int azul = 9;
int verde = 6;
unsigned long ONOFF = 0xE0E016E9;

unsigned long rojoUP = 0xE0E004FB;
unsigned long rojoDOWN = 0xE0E0A25D;

unsigned long verdeUP = 0xE0E07C83;
unsigned long verdeDOWN = 0xE0E0E21D;

unsigned long azulUP = 0xE0E0629D;
unsigned long azulDOWN = 0xE0E012ED;

int valROJO = 100;
int valAZUL = 100;
int valVERDE = 100;

IRrecv irrecv(RECV_PIN);
decode_results results;
int recibido = 0;

void setup() {
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Comienzo la comunicación con el sensor
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(rojo, OUTPUT);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
boolean aux = false;
boolean permiso = false;
void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    irrecv.resume(); // Recibo basura
    if (results.value == ONOFF) { //solo al pulsar el boton de encendido el sistema de luces funciona
      analogWrite(rojo, 0);
      analogWrite(verde, 0);
      analogWrite(azul, 0);
      valROJO = 100;
      valAZUL = 100;
      valVERDE = 100;
    }
    if (results.value == rojoUP) {
      valROJO = valROJO + 50;
      analogWrite(rojo, valROJO);
      if (valROJO > 250) {
        analogWrite(rojo, 250);
        valROJO = 250;
      }
    } else if (results.value == rojoDOWN) {
      valROJO = valROJO - 50;
      analogWrite(rojo, valROJO);
      if (valROJO < 10) {
        analogWrite(rojo, 0);
        valROJO = 9;
      }
    }
    if (results.value == azulUP) {
      valAZUL = valAZUL + 50;
      analogWrite(azul, valAZUL);
      if (valAZUL > 250) {
        analogWrite(azul, 250);
        valAZUL = 250;
      }
    } else if (results.value == azulDOWN) { // por un código como este debiera ir a la carcel y encerrarme en la celda más profunda
      valAZUL = valAZUL - 50;
      analogWrite(azul, valAZUL);
      if (valAZUL < 10) {
        analogWrite(azul, 0);
        valAZUL = 9;
      }
    }
    if (results.value == verdeUP) {
      valVERDE = valVERDE + 50;
      analogWrite(verde, valVERDE);
      if (valVERDE > 250) {
        analogWrite(verde, 250);
        valVERDE = 250;
      }
    } else if (results.value == verdeDOWN) {
      valVERDE = valVERDE - 50;
      analogWrite(verde, valVERDE);
      if (valVERDE < 10) {
        analogWrite(verde, 0);
        valVERDE = 9;
      }
    }
  }
  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    recibido = Serial.read(); // Reads the data from the serial port
  }
  if (recibido == 'a') {
    recibido = 0;
    colores('a');
  } else if (recibido == 'b') {
    recibido = 0;
    colores('b');
  }  else if (recibido == 'c') {
    recibido = 0;
    colores('c');
  }  else if (recibido == 'd') {
    recibido = 0;
    colores('d');
   }  else if (recibido == 'e') {
    recibido = 0;
    colores('e');
  }  else if (recibido == 'f') {
    recibido = 0;
    colores('f');
  } else if (recibido == 'g') {
    recibido = 0;
    colores('g');
  } else if (recibido == 'h') {
    recibido = 0;
    colores('h');
  } else if (recibido == 'i') {
    recibido = 0;
    colores('i');
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

