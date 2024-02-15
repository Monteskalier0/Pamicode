#ifndef _MOTEUR_H
#define _MOTEUR_H
#include <Arduino.h>
#include "ENCODEUR.h"

#define BACKWARD 0x1
#define FORWARD 0x0

class Moteur : public Encoder
{
    public : 
    Moteur(uint32_t frequence, uint8_t channelPwm, int pinPwm, uint8_t resolution, int pinRotation,int mode, int pinEncoderA, int pinEncoderB);
    void forward(int dutyCycle, int ticks);//méthode pour avancer en fonction du dutyCycle et du nombre de ticks des encodeurs
    void backward(int dutyCycle, int ticks);//méthode pour reculer en fonction du dutyCycle et du nombre de ticks des encodeurs
    void rawForward(int dutyCycle);//méthode pour avancer en fonction du dutyCycle
    void rawBackward(int dutyCycle);//méthode pour reculer en fonction du dutyCycle

    void stop(void);

    // //getters pour récupérer les valeurs des les variables membres sans qu'on puisse les modifier
    // uint32_t getFrequence() const { return m_frequence; }
    // uint8_t getChannelPwm() const { return m_channelPwm; }
    // int getPinPwm() const { return m_pinPwm; }
    // uint8_t getResolution() const { return m_resolution; }
    // int getPinRotation() const { return m_pinRotation; }
    // int getMode() const { return m_mode; }


    private :
    uint32_t m_frequence;
    uint8_t m_channelPwm;
    int m_pinPwm;
    uint8_t m_resolution;
    int m_pinRotation;
    int m_mode;
};

class robot{
    public : 
    robot(Moteur& moteurDroit, Moteur& moteurGauche);//on met un & pour faire référence à des objets déjà existants
    void forward(int dutyCycle, int ticks);

    private : 
    /*
    déclatation de membres de la classe robot à partir d'une réference de la classe Moteur
    "m_moteurDroit est une référence à moteurDroit, je peux alors contrôleur moteurDroit par le biais de m_moteurDroit, qui lui appartient à la classe robot"
    */
    Moteur& m_moteurDroit;
    Moteur& m_moteurGauche;

};
#endif