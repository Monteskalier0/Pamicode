#include <Arduino.h>
#include <ESP32Encoder.h>
#include <moteur.h>


// put function declarations here:
float DistanceDroite(void);
int64_t DistanceGauche(void);


char G = 'G';
char D = 'D';



int encda = 19;
int encdb = 17;
int encga = 33;
int encgb = 25;
//



float encoderMesureD = 0;
float encoderMesureG = 0;
float DistanceGauche2;
float perimettreroue = PI*60;     //formule 2*PI*R sauf qu'on prend D
volatile int encnumg = 0;
volatile int encnumd = 0;

ESP32Encoder EncoderGauche, EncoderDroit;

void setup() {
  // put your setup code here, to run once:
 

  Serial.begin(115200);
 



  EncoderDroit.attachHalfQuad(encda, encdb);
  EncoderGauche.attachHalfQuad(encga, encgb);


  moteur_init();
  
  EncoderDroit.setCount(0);
  EncoderGauche.setCount(0);

}

void loop() {
  // put your main code here, to run repeatedly:
writePWMD(100);
writePWMG(100);

 encoderMesureD = DistanceDroite();           //C'est surement la ou dans la fontion Distance droite qu'il y a un problème mais je vois pas lequel.
 encoderMesureG = DistanceGauche(); 

 Serial.println(encoderMesureD);
 Serial.println(encoderMesureG);
 
 //delay(100);

}

float DistanceDroite(void){
return(EncoderDroit.getCount());
}

int64_t DistanceGauche(void){
return(EncoderGauche.getCount());
}

