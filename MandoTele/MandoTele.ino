/*
   Rubén Arce 10/07/2018

   Control de tira de 5m de leds RGB a través de infrarrojos

*/

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

void setup() {
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Comienzo la comunicación con el sensor
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(rojo, OUTPUT);
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
}

