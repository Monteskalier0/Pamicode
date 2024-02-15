#include <Arduino.h>
#include <math.h>
#include <Moteur.h>

Moteur moteurDroit(20000,//frequence
                   0,//channel de la PWM
                   14,//pin de la PWM
                   8,//resolution
                   12,//pin de rotation
                   13,//mode
                   17,//encodeur pin A 
                   19//encodeur pin B
                   );

Moteur moteurGauche(20000,//frequence
                    1,//channel de la PWM
                    26,//pin de la PWM
                    8,//resolution
                    27,//pin de rotation
                    13,//mode
                    33,//encodeur pin A 
                    25//encodeur pin B
                    );

robot pami(moteurDroit, moteurGauche);

int valD, valG;


void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // valD = encodeurDroit.getCount();
  // valG = encodeurGauche.getCount();
  // Serial.printf("Valeur codeur Gauche %d  Valeur Codeur Droit %d\n", valG, valD);

  pami.forward(250, 10000);
  delay(2000);
}
