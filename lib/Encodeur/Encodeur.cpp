#include "ENCODEUR.h"
#include <Arduino.h>
#include "ESP32Encoder.h"

Encoder::Encoder(int pinA, int pinB){
  encoder = new ESP32Encoder;
    // Config encodeur
    encoder->attachHalfQuad(pinA, pinB);
    encoder->clearCount();
    encoder->setCount(0);
}

void Encoder::setCount(int count){
    encoder->setCount(count);
}
int Encoder::getCount(){
    return encoder->getCount();
}
void Encoder::clearCount(){
    encoder->clearCount();
}
