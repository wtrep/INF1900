#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <avr/io.h>
#include <util/delay.h>

#define MILIEU PINC4
#define GAUCHE PINC3
#define EXTREME_GAUCHE PINC2
#define DROITE PINC5
#define EXTREME_DROITE PINC6

enum DIRECTION{
    AVANT = 0,
    ARRIERE = 1
};

class Navigator {
    public : 
        Navigator(uint8_t vitesse);

        void initPWM();
        void ajustementPWM (uint8_t puissanceDroit, DIRECTION directionDroit, uint8_t puissanceGauche, DIRECTION directionGauche);
        void stopPWM();

        uint8_t getVitesse();

    protected:
        uint8_t _vitesse;

        const uint8_t HAUTE_INTENSITE = 90;
        const uint8_t BASSE_INTENSITE = 32;
};

#endif // NAVIGATOR_H