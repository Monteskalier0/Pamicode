#ifndef _ENCODEUR_H
#define _ENCODEUR_H
#include <Arduino.h>
#include "ESP32Encoder.h"
//All declarations shall be made in camelCase

class Encoder{
    public : 
    Encoder(int pinA, int pinB);//constructor

//méthodes virtuelles déclarées en inline
     void setCount(int count);
     int getCount();
     void clearCount();
     private : 
    ESP32Encoder *encoder;
};
#endif
