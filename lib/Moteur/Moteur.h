#ifndef _MOTEUR_H
#define _MOTEUR_H
#include <Arduino.h>
#include "Encodeur.h"
#include <math.h>

#define FORWARD 0x1
#define BACKWARD 0x0

class Moteur : public Encoder
{
public:
    Moteur(uint32_t frequence, uint8_t channelPwm, int pinPwm, uint8_t resolution, int pinRotation, int mode, int pinEncoderA, int pinEncoderB);

    void forward(int dutyCycle, int ticks);  // méthode pour avancer en fonction du dutyCycle et du nombre de ticks des encodeurs
    void backward(int dutyCycle, int ticks); // méthode pour reculer en fonction du dutyCycle et du nombre de ticks des encodeurs
    void rawForward(int dutyCycle);          // méthode pour avancer en fonction du dutyCycle
    void rawBackward(int dutyCycle);         // méthode pour reculer en fonction du dutyCycle
    void stop(void);                         // arrête le moteur

    float distance(void); // distance parcourue en mm

    // //getters pour récupérer les valeurs des les variables membres sans qu'on puisse les modifier
    // uint32_t getFrequence() const { return m_frequence; }
    // uint8_t getChannelPwm() const { return m_channelPwm; }
    // int getPinPwm() const { return m_pinPwm; }
    // uint8_t getResolution() const { return m_resolution; }
    // int getPinRotation() const { return m_pinRotation; }
    // int getMode() const { return m_mode; }

private:
    uint32_t m_frequence;
    uint8_t m_channelPwm;
    int m_pinPwm;
    uint8_t m_resolution;
    int m_pinRotation;
    int m_mode;
};

class robot
{
public:

int valD, valG;


    float m_perimetre = PI * 10.60 * 47.74648;//PI*DIAMETRE_ROBOT*(TICKS_PAR_TOUR*PERIMETRE_ROUE)

    float m_distance;//distance à parcourir en cm
    float m_ticks;//nombre de ticks à parcourir
    float m_vBase = 127; // vitesse de base



    float m_erreurPosition,//erreur de position moyenne des deux roues
    m_erreurRotation,//erreur de l'angle de rotation moyenne des deux roues
    m_erreurPositionPrecedente,//erreur de position précédente
    m_correctionPosition,//correction de position (proportionnelle dérivée)
    m_correctionRotation,//correction de rotation (proportionnelle dérivée)
    m_kp=0.47,//coefficient proportionnel asservissement position
    m_kd=0;//coefficient dérivé asservissement position
    int i;//compteur
    int m_commandeMotGauche,//commande moteur gauche
    m_commandeMotDroit;//commande moteur droit



    robot(Moteur &moteurDroit, Moteur &moteurGauche); // on met un & pour faire référence à des objets déjà existants
    void forward(int dutyCycle, float distance);
    void backward(int dutyCycle, int ticks);
    void turn(int dutyCycle, float angle);


    int compensationFsecMotDroit(int commande);
    int compensationFsecMotGauche(int commande);
    int saturationNumerique(int commande);

private:
    /*
    déclatation de membres de la classe robot à partir d'une réference de la classe Moteur
    "m_moteurDroit est une référence à moteurDroit, je peux alors contrôleur moteurDroit par le biais de m_moteurDroit, qui lui appartient à la classe robot"
    */
    Moteur &m_moteurDroit;
    Moteur &m_moteurGauche;
};
#endif