#include <Arduino.h>
#include "moteur.h"
//#include <CRAC_utility.h>

//int mode = 13;

int mode = 13;
int bin = 27;
int bpwm = 26;

int ain = 12;
int apwm = 4; 

int freq = 20000;
int pwmchannelb = 1;
int pwmchannela = 0;
int resolution = 8;

void moteur_init(void){

  pinMode(mode,OUTPUT);
  // Serial.print("on \n");
  digitalWrite(mode,HIGH);
  pinMode(bin,OUTPUT);
  pinMode(ain,OUTPUT);
  ledcSetup(pwmchannelb,freq,resolution);
  ledcSetup(pwmchannela,freq,resolution);
  ledcAttachPin(apwm,pwmchannela);
  ledcAttachPin(bpwm,pwmchannelb);
}



//----------------------------------------------------------------------autres fonctions
/****************************************************************************************/
/* NOM : setupPWM                                                                       */
/* ARGUMENT : Pins de sortie et channel des PWM                                         */
/* RETOUR : rien                                                                        */
/* DESCRIPTIF : permet de setup les canaux de PWM et de les faire sortir sur les pins   */
/****************************************************************************************/


void moteur_avance_D(int PWM){
    if(PWM<0){
      PWM=-PWM;
      digitalWrite(bin, 0);
      }
    else digitalWrite(bin, 1);
  
    ledcWrite(pwmchannela,PWM);

}

void moteur_avance_G(int PWM){
    if(PWM<0){
    PWM=-PWM;
    digitalWrite(ain, 0);
    }
    else digitalWrite(ain, 1);
    ledcWrite(pwmchannelb,PWM);
}

void moteur_stop_D(void)
{
    ledcWrite(pwmchannela,0);
}

void moteur_stop_G(void)
{
    ledcWrite(pwmchannelb,0);
}