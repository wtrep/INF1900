#ifndef SONAR_H
#define SONAR_H

#include <util/delay.h>
#include <avr/interrupt.h>
#include "pathCorrector.h"

// Variables globales pour les interruptions déclarées dans mur.cpp
extern volatile uint8_t distance;
extern volatile bool repondu;
extern volatile bool listening;

class Sonar : public PathCorrector 
{
public:
    Sonar(uint8_t vitesse);
    ~Sonar();
    
    void fetch();
    void redressementDroit();
    void redressementGauche();
    void avancerDroit();

private:
    const uint8_t DEMARAGE = 254;
    const uint8_t BASSE_INTENSITE = 32;
    const uint8_t AVANT = 0;
    const uint8_t ARRIERE = 1;
    const uint8_t OFF = 0;
};

#endif