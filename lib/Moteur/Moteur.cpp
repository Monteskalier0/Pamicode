#include "Moteur.h"
#include <Arduino.h>

Moteur::Moteur(uint32_t frequence, uint8_t channelPwm, int pinPwm, uint8_t resolution, int pinRotation, int mode, int pinEncoderA, int pinEncoderB)
    : Encoder(pinEncoderA, pinEncoderB)
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
    while (getCount() <= ticks)
    {
        ledcWrite(m_channelPwm, dutyCycle);
        Serial.printf("Valeur codeur %d\n", getCount());
    }
    stop();
}

void Moteur::backward(int dutyCycle, int ticks)
{
    digitalWrite(m_pinRotation, BACKWARD);
    while (getCount() <= ticks)
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

robot::robot(Moteur &moteurDroit, Moteur &moteurGauche) : m_moteurDroit(moteurDroit), m_moteurGauche(moteurGauche)
{
}

void robot::forward(int dutyCycle, float distance)
{
    m_ticks = distance * 47.74648;

    m_moteurDroit.clearCount();
    m_moteurGauche.clearCount();

    do
    {

        // calcul des erreurs de position moyenne :
        m_erreurPosition = m_ticks - (m_moteurGauche.getCount() + m_moteurDroit.getCount()) / 2; // erreur de position moyenne des deux roues

        // correction proportionnelle
        m_correctionPosition = m_kp * m_erreurPosition;

        // commande des moteurs :
        m_commandeMotDroit = m_correctionPosition;
        m_commandeMotGauche = m_correctionPosition;

        // compensation des frottements secs :
        m_commandeMotGauche = compensationFsecMotGauche(m_commandeMotGauche);
        m_commandeMotDroit = compensationFsecMotDroit(m_commandeMotDroit);

        // saturation numérique :
        m_commandeMotDroit = saturationNumerique(m_commandeMotDroit);
        m_commandeMotGauche = saturationNumerique(m_commandeMotGauche);
        // commande des moteurs :

        if (i < 120)
        {
            m_vBase = i;
            i++;
            delay(2.5);
        }

        m_moteurDroit.rawForward(m_vBase + m_commandeMotDroit);
        m_moteurGauche.rawForward(m_vBase + m_commandeMotGauche);

        // debug :
        Serial.printf("codeur Gauche : %d, codeur Droit %d\n", m_moteurGauche.getCount(), m_moteurDroit.getCount());

    } while (m_erreurPosition > 0);

    m_moteurDroit.stop();
    m_moteurGauche.stop();
}

void robot::turn(int dutyCycle, float angle)
{
    m_perimetre = PI * 10.60 * 47.74648;
    m_ticks = (int)((angle / 360.0) * m_perimetre);
    i=0;
    m_moteurDroit.clearCount();
    m_moteurGauche.clearCount();

        if (angle > 180)
        {
            do{

            // erreur de la distance que les roues ont a parcourir
            m_erreurRotation = -m_ticks - (m_moteurGauche.getCount() - m_moteurDroit.getCount())/2;
            Serial.printf("erreur rotation : %d\n", m_erreurRotation);

            // correction proportionnelle
            m_correctionRotation = m_kp * m_erreurRotation;

            // commande des moteurs
            m_commandeMotDroit = m_correctionRotation;
            m_commandeMotGauche = m_correctionRotation;

            // compensation des frottements secs
            m_commandeMotGauche = compensationFsecMotGauche(m_commandeMotGauche);
            m_commandeMotDroit = compensationFsecMotDroit(m_commandeMotDroit);

            // saturation numérique
            m_commandeMotDroit = saturationNumerique(m_commandeMotDroit);
            m_commandeMotGauche = saturationNumerique(m_commandeMotGauche);

            // commande des moteurs
            if (i < 120)
            {
                m_vBase = i;
                i++;
                delay(2.5);
            }

            m_moteurDroit.rawForward(m_vBase + m_commandeMotDroit);
            m_moteurGauche.rawBackward(m_vBase + m_commandeMotGauche);

            // Serial.printf("codeur Gauche : %d, codeur Droit %d, erreur : %d\n", m_moteurGauche.getCount(), m_moteurDroit.getCount(),m_erreurRotation);
        }while(1);
        }

        

    } 

int robot::compensationFsecMotDroit(int commande)
{
    if (commande > 0)
    {
        commande = commande + 50;
    }

    if (commande < 0)
    {
        commande = commande - 50;
    }

    return commande;
}

int robot::compensationFsecMotGauche(int commande)
{
    if (commande > 0)
    {
        commande = commande + 75;
    }

    if (commande < 0)
    {
        commande = commande - 75;
    }

    return commande;
}

int robot::saturationNumerique(int commande)
{
    if (commande >= 120)
    {
        commande = 120;
    }

    if (commande <= -120)
    {
        commande = -120;
    }
    return commande;
}