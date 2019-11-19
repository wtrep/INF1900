
#include "couloir.h"
/*
void actionCouloir(){
    while (suivreLigne());

    ajustementPWM(VITESSE, 0, VITESSE, 0);
    
    while (!(PINC & 0b00111000))
    {
        if (PINC & 0b01000000) {
            suiveurLigne::redressementDroit(VITESSE);
        }   
        else if (PINC & 0b00000100){
            suiveurLigne::redressementGauche(VITESSE);
        }
    }
    while (suivreLigne());
    suiveurLigne::tournerGauche(VITESSE);
}
*/
    Couloir::Couloir()
    {
        const uint8_t VITESSE = 88; 
        _suiveurLigne = SuiveurLigne(VITESSE);
        _suiveurCouloir = SuiveurCouloir(VITESSE);
        DDRC = 0x00; //DDRC en entree
    };

    void Couloir::run(){
        while (_suiveurLigne.suivreLigne());

        _suiveurLigne.ajustementPWM(_suiveurLigne.getVitesse(), 0, _suiveurLigne.getVitesse(), 0);

        while (!(PINC & ((1<<GAUCHE) | (1<<MILIEU) | (1<<DROITE))))
        {
            if (PINC & (1<<EXTREME_GAUCHE)) {
                _suiveurLigne.redressementDroit();
            }   
            else if (PINC & 0b00000100){
                _suiveurLigne.redressementGauche();
            }
        }
        while (_suiveurLigne.suivreLigne());
        _suiveurLigne.tournerGauche();
    };