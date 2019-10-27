/*
   Rubén Arce 21/07/2018

   Regalo Erica Navidades 2018

*/
#include <IRremote.h>
int rojo = 6;
int azul = 10;
int verde = 5;
int recibido = 0;
int RECV_PIN = 11;

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

void setup() {
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
boolean aux = false;
boolean permiso = false;
void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    if (results.value == ONOFF) { //solo al pulsar el boton de encendido el sistema de luces funciona
      if (aux == false) {
        aux = true;
        permiso = true;
        //Serial.println ("encendido");
      } else {
        aux = false;
        permiso = false;
        analogWrite(rojo, 0);
        analogWrite(verde, 0);
        analogWrite(azul, 0);
        //Serial.println ("apagado");
        valROJO = 100;
        valAZUL = 100;
        valVERDE = 100;
      }
      delay(1500);
    }
    if (permiso == true) {
      if (results.value == rojoUP) {
        valROJO = valROJO + 40;
        analogWrite(rojo, valROJO);
        if (valROJO > 250) {
          analogWrite(rojo, 250);
          valROJO = 250;
        }
      } else if (results.value == rojoDOWN) {
        valROJO = valROJO - 40;
        analogWrite(rojo, valROJO);
        if (valROJO < 10) {
          analogWrite(rojo, 0);
          valROJO = 9;
        }
      }
      if (results.value == azulUP) {
        valAZUL = valAZUL + 40;
        analogWrite(azul, valAZUL);
        if (valAZUL > 250) {
          analogWrite(azul, 250);
          valAZUL = 250;
        }
      } else if (results.value == azulDOWN) { // por un código como este debiera ir a la carcel y encerrarme en la celda más profunda
        valAZUL = valAZUL - 40;
        analogWrite(azul, valAZUL);
        if (valAZUL < 10) {
          analogWrite(azul, 0);
          valAZUL = 9;
        }
      }
      if (results.value == verdeUP) {
        valVERDE = valVERDE + 40;
        analogWrite(verde, valVERDE);
        if (valVERDE > 250) {
          analogWrite(verde, 250);
          valVERDE = 250;
        }
      } else if (results.value == verdeDOWN) {
        valVERDE = valVERDE - 40;
        analogWrite(verde, valVERDE);
        if (valVERDE < 10) {
          analogWrite(verde, 0);
          valVERDE = 9;
        }
      }
    }
    delay(800);
  }
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
    case 'b'://verde
      analogWrite(rojo, 0);
      analogWrite(verde, 250);
      analogWrite(azul, 0);
      break;
    case 'c'://azul
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
      analogWrite(rojo, 255);
      analogWrite(verde, 117);
      analogWrite(azul, 17);
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
