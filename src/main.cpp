#include <Arduino.h>
#include <math.h>
#include "Encodeur.h"
#include <Moteur.h>

Moteur moteurGauche(20000, // frequence
                   0,     // channel de la PWM
                   4,    // pin de la PWM
                   8,     // resolution
                   12,    // pin de rotation
                   13,    // mode
                   17,    // encodeur pin A
                   19     // encodeur pin B
);

Moteur moteurDroit(20000, // frequence
                    1,     // channel de la PWM
                    26,    // pin de la PWM
                    8,     // resolution
                    27,    // pin de rotation
                    13,    // mode
                    33,    // encodeur pin A
                    25     // encodeur pin B
);

robot pami(moteurDroit, moteurGauche);

int valD, valG;

void setup()
{

  Serial.begin(115200);

}

void loop()
{

// pami.forward(150,50);
// delay(1000);
pami.turn(200, 250);
// delay(1000);
// pami.forward(150,50);
// delay(1000);
// pami.turn(90, 150);
// delay(1000);
// pami.forward(150,50);
// delay(1000);
// pami.turn(90, 150);
// delay(1000);
// pami.forward(150,50);
delay(5000);
}
