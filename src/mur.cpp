#define F_CPU 8000000UL

#include "mur.h"

volatile uint8_t distance = 0;
volatile bool repondu;
volatile bool listening;

// Interrupt on all edges of INT2
ISR(INT2_vect)
{
    if (listening)
    {
        TCNT2 = 0; // Reinitialise la valeur du compteur
        TIMSK2 |= (1 << TOIE2); // Interrupt on overflow
        listening = false;
    }
    else if (!repondu) 
    {   
        cli(); // Stop interrupts
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        EIMSK &= ~(1 << INT2); // Interrupts on INT2 OFF
        distance = (TCNT2 * 8) / 58;
        repondu = true;
        sei();
    }
}

// Interrupt on Timer2 overflow
ISR(TIMER2_OVF_vect)
{
    if (!repondu)
    {
        cli();
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        EIMSK &= ~(1 << INT2); // Interrupts on INT2 OFF
        distance = 35; // Le maximum supporté par le compteur
        repondu = true;
        sei();
    }
}

Mur::Mur(uint8_t vitesse) :
    _suiveurLigne(SuiveurLigne(vitesse)), 
    _sonar(Sonar(vitesse)), 
    _etat(EtatMur::debutLigne)
{
}

void Mur::run()
{
    switch(_etat)
    {
        case (EtatMur::debutLigne):
        case (EtatMur::finLigne):
            suivreLigne();
            break;
        case (EtatMur::mur):
            suivreMur();
        case (EtatMur::virage):
            // fonction virage
    }
}

void Mur::suivreMur()
{
    _sonar.fetch();
    while(!repondu); // Attendre la réponse du sonar

    if (distance < 14 && distance > 1)
    {
        _sonar.redressementDroit();
        // Led
    }
    else if (distance > 16 && distance < 36)
    {
        _sonar.redressementGauche();
        // Led
    }
    else
    {
        // Led
    }
}

void Mur::suivreLigne()
{

}