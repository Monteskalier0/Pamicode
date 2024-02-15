#include "MOTEUR.h"
#include <Arduino.h>

Moteur::Moteur(uint32_t frequence, uint8_t channelPwm, int pinPwm, uint8_t resolution, int pinRotation, int mode, int pinEncoderA, int pinEncoderB)
    : Encoder(pinEncoderA,pinEncoderB)
{
    // Affection des paramètres aux variables membres, pour les rendre accessibles dans toute la classe
    m_frequence = frequence;
    m_channelPwm = channelPwm;
    m_pinPwm = pinPwm;
    m_resolution = resolution;
    m_pinRotation = pinRotation;
    m_mode = mode;

    ledcSetup(m_channelPwm, m_frequence, m_resolution);
    ledcAttachPin(m_pinPwm, m_channelPwm);

    pinMode(m_pinRotation, OUTPUT);
    pinMode(m_mode, OUTPUT);

    digitalWrite(m_mode, HIGH);
    digitalWrite(m_pinRotation, FORWARD);
}

void Moteur::forward(int dutyCycle, int ticks)
{
    digitalWrite(m_pinRotation, FORWARD);
    while(getCount() <= ticks)
    {
    ledcWrite(m_channelPwm, dutyCycle);
    Serial.printf("Valeur codeur %d\n", getCount());
    }
    stop();
}

void Moteur::backward(int dutyCycle, int ticks)
{
    digitalWrite(m_pinRotation, BACKWARD);
    while(getCount() <= ticks)
    {
    ledcWrite(m_channelPwm, dutyCycle);
    Serial.printf("Valeur codeur %d\n", getCount());
    }
    ledcWrite(m_channelPwm, 0);
    stop();
}

void Moteur::rawForward(int dutyCycle)
{
    digitalWrite(m_pinRotation, FORWARD);
    ledcWrite(m_channelPwm, dutyCycle);
}

void Moteur::rawBackward(int dutyCycle)
{
    digitalWrite(m_pinRotation, BACKWARD);
    ledcWrite(m_channelPwm, dutyCycle);
}


void Moteur::stop(void)
{
    ledcWrite(m_channelPwm, 0);
    Serial.printf("moteur arrêté\n");
}   

robot::robot(Moteur& moteurDroit, Moteur& moteurGauche):m_moteurDroit(moteurDroit), m_moteurGauche(moteurGauche)
{
}

void robot::forward(int dutyCycle, int ticks)
{
    m_moteurDroit.clearCount();
    m_moteurGauche.clearCount();
    
    while((m_moteurDroit.getCount()<= ticks) && (m_moteurGauche.getCount() <= ticks))
    {
    m_moteurDroit.rawForward(dutyCycle);
    m_moteurGauche.rawForward(dutyCycle);

    Serial.printf("codeur Gauche : %d, codeur Droit %d\n", m_moteurGauche.getCount(),m_moteurDroit.getCount());

}

    m_moteurDroit.stop();
    m_moteurGauche.stop();
}

void robot::backward(int dutyCycle, int ticks)
{
    m_moteurDroit.clearCount();
    m_moteurGauche.clearCount();
    
    while((m_moteurDroit.getCount()>= -ticks) && (m_moteurGauche.getCount() >= -ticks))
    {
    m_moteurDroit.rawBackward(dutyCycle);
    m_moteurGauche.rawBackward(dutyCycle);

    Serial.printf("codeur Gauche : %d, codeur Droit %d\n", m_moteurGauche.getCount(),m_moteurDroit.getCount());

}

    m_moteurDroit.stop();
    m_moteurGauche.stop();
}
