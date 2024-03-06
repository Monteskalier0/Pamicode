#include <Arduino.h>
#include <ESP32Encoder.h>




//Chef c'est toi qui a tout fait


// put function declarations here:
float DistanceDroite(void);
int64_t DistanceGauche(void);


char G = 'G';
char D = 'D';

int bin = 27;
int bpwm = 26;

int ain = 12;
int apwm = 14; 

int encda = 19;
int encdb = 17;

int encga = 26;
int encgb = 27;
int mode = 13;

int freq = 25000;
int pwmchannelb = 0;
int pwmchannela = 1;
int resolution = 8;

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
 

  pinMode(mode,OUTPUT);
   Serial.print("on \n");
  digitalWrite(mode,HIGH);

  EncoderDroit.attachHalfQuad(encda, encdb);
  EncoderGauche.attachHalfQuad(encga, encgb);

  pinMode(bin,OUTPUT);
  pinMode(ain,OUTPUT);
  ledcSetup(pwmchannelb,freq,resolution);
  ledcSetup(pwmchannela,freq,resolution);
  ledcAttachPin(apwm,pwmchannelb);
  ledcAttachPin(bpwm,pwmchannela);
  digitalWrite(bin,0);
  digitalWrite(ain,0);
  ledcWrite(pwmchannela,0);
  ledcWrite(pwmchannelb,0);
  EncoderDroit.setCount(0);
  EncoderGauche.setCount(0);
}

void loop() {
  // put your main code here, to run repeatedly:



 //Serial.println(encoderMesureD);
 Serial.printf("G : %d, D : %d \n", EncoderGauche.getCount(), EncoderDroit.getCount());

 delay(100);

}

float DistanceDroite(void){
return(EncoderDroit.getCount());
}

int64_t DistanceGauche(void){
return(EncoderGauche.getCount());
}
