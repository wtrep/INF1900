#include "sonar.h"

Sonar::Sonar(uint8_t vitesse) : 
    PathCorrector(vitesse)
{
    // Interruption
    EICRA |= (1 << ISC20); // Any edge
}

Sonar::~Sonar()
{
    TCCR2B = 0; // Disable the counter
}

void Sonar::fetch()
{
    cli();
    PORTB |= (1 << PORTB4);
    _delay_us(SONAR_DELAY);
    PORTB &= ~(1 << PORTB4);

    listening = true;
    repondu = false;

    TCCR2B |= (1 << CS22); // Active le compteur, prescaler de 64
    EIMSK |= (1 << INT2); // Active les interruptions sur INT2
    sei(); // Active les interruptions
}

void Sonar::redressementDroit()
{
    _navigator.ajustementPWM(DEMARAGE, AVANT, OFF, AVANT);
    _delay_ms(DELAY_DEMARAGE);
    _navigator.ajustementPWM(HAUTE_INTENSITE, AVANT, OFF, AVANT);
}

void Sonar::redressementGauche()
{
    _navigator.ajustementPWM(OFF, AVANT, DEMARAGE, AVANT);
    _delay_ms(DELAY_DEMARAGE);
    _navigator.ajustementPWM(OFF, AVANT, HAUTE_INTENSITE, AVANT);
}

void Sonar::avancerDroit()
{
    _navigator.ajustementPWM(DEMARAGE, AVANT, DEMARAGE, AVANT);
    _delay_ms(DELAY_DEMARAGE);
    _navigator.ajustementPWM(_vitesse, AVANT, _vitesse, AVANT);
}