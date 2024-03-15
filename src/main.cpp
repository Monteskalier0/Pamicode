#include <Arduino.h>
#include <math.h>
#include "Encodeur.h"
#include <Moteur.h>
#include <Moteur2.h>

// All declaration shall be made in camelCase
/*
Moteur moteurDroit(20000,//frequence
                   0,//channel de la PWM
                   4,//pin de la PWM
                   8,//resolution
                   12,//pin de rotation
                   13,//mode
                   25,//encodeur pin A
                   33//encodeur pin B
                   );

Moteur moteurGauche(20000,//frequence
                    1,//channel de la PWM
                    26,//pin de la PWM
                    8,//resolution
                    27,//pin de rotation
                    13,//mode
                    17,//encodeur pin A
                    19//encodeur pin B
                    );
*/

// robot pami(moteurDroit, moteurGauche);

Encoder encodeurDroit(33, 25);
Encoder encodeurGauche(17, 19);
void avance_robot(int vitesse, float distance);
void rotation_robot(int vitesse, int degre);
int valD, valG;


int compensationFsec(int commande);

void setup()
{

  Serial.begin(115200);
  encodeurDroit.clearCount();
  encodeurDroit.setCount(0);

  encodeurGauche.clearCount();
  encodeurGauche.setCount(0);

  moteur_init();

  delay(1000);

  rotation_robot(80, 90.00);
  delay(2000);
  avance_robot(250, 250.00);
  delay(1000);
  rotation_robot(80, -90.00);
  delay(2000);

}
void loop()
{
  valD = -encodeurDroit.getCount();
  valG = encodeurGauche.getCount();
  Serial.printf("Valeur codeur Gauche %d  Valeur Codeur Droit %d\n", valG, valD);
}

void avance_robot(int vitesse, float distance)
{
  int i = 0;
  int erreurP;
  float coefP = 0.47;
  distance = ((float)distance * 47.74648);
  encodeurDroit.setCount(0);
  encodeurGauche.setCount(0);

  while ((valD <= (int)distance) & (valG <= (int)distance))
  {

    valD = encodeurDroit.getCount();
    valG = encodeurGauche.getCount();
    erreurP = valD - valG;

    if (i <= vitesse)
    {
      i++;
      delay(5);
      // erreurP=0;
    }
    float Kp;
    float correctionP = Kp * erreurP;


    if (erreurP < 0)
    {
      moteur_avance_D(i - ((float)erreurP * coefP));
      moteur_avance_G(i + ((float)erreurP * coefP));
    }
    else
    {
      moteur_avance_G(i + ((float)erreurP * coefP));
      moteur_avance_D(i - ((float)erreurP * coefP));
    }
  }

  moteur_stop_D();
  moteur_stop_G();
}

void rotation_robot(int vitesse, int angle)
{
  float perimetre = PI * 10.60 * 47.74648;
  float rotation = 0;
  vitesse = vitesse + 60;
  encodeurDroit.setCount(0);
  encodeurGauche.setCount(0);
  valD = 0;
  valG = 0;

  if (angle <= 0)
  {
    angle = -angle;
    rotation = (int)((angle / 360.00) * perimetre);

    while ((valG <= rotation) && (valD >= -rotation))
    {
      valD = encodeurDroit.getCount();
      valG = encodeurGauche.getCount();
      moteur_avance_G(-vitesse);
      moteur_avance_D(vitesse);
    }
    moteur_stop_D();
    moteur_stop_G();
  }
  else
  {

    rotation = (int)((angle / 360.00) * perimetre);
    while ((valD <= rotation) & (valG >= (-rotation)))
    {
      valD = encodeurDroit.getCount();
      valG = encodeurGauche.getCount();

      moteur_avance_G(vitesse);
      moteur_avance_D(-vitesse);
    }

    moteur_stop_D();
    moteur_stop_G();
  }
}


int compensationFsec(int commande)
{
  if(commande==0){
    return 0;
  }
  
  if (commande > 0)
  {
    commande = commande + 60;
  }

  if (commande < 0){
    commande = commande - 60;
  }

  return commande;
}
